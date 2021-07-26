#include "composite.hh"
#include "feature_builder.hh"
#include "zxy_math.hh"

#include <vtzero/builder.hpp>
#include <vtzero/property_value.hpp>
#include <vtzero/vector_tile.hpp>

#include <mapbox/geometry/box.hpp>
#include <mapbox/geometry/for_each_point.hpp>
#include <mapbox/geometry/point.hpp>

#include <algorithm>
#include <utility>

namespace vtile {

static constexpr std::uint32_t MVT_VERSION_1 = 1U;

namespace {

template <typename FeatureBuilder> struct build_feature_from_v1 {
  explicit build_feature_from_v1(FeatureBuilder &builder) : builder_(builder) {}

  bool operator()(vtzero::feature const &feature) {
    try {
      builder_.apply(feature);
    } catch (vtzero::geometry_exception const &ex) {
      std::cerr << "Skipping feature with malformed geometry (v1): "
                << ex.what() << std::endl;
    }
    return true;
  }
  FeatureBuilder &builder_;
};

template <typename FeatureBuilder> struct build_feature_from_v2 {
  explicit build_feature_from_v2(FeatureBuilder &builder) : builder_(builder) {}

  bool operator()(vtzero::feature const &feature) {
    builder_.apply(feature);
    return true;
  }
  FeatureBuilder &builder_;
};

} // namespace

struct composite_worker {

  composite_worker(std::unique_ptr<baton_type> &&baton_data)
      : baton_data_{std::move(baton_data)},
        output_buffer_{std::make_unique<std::string>()} {}

  void execute() {
    try {
      vtzero::tile_builder builder;
      std::vector<vtzero::data_view> names;

      int const buffer_size = baton_data_->buffer_size;
      std::uint32_t const target_z = baton_data_->z;
      std::uint32_t const target_x = baton_data_->x;
      std::uint32_t const target_y = baton_data_->y;

      std::vector<std::unique_ptr<std::vector<char>>> buffer_cache;

      for (auto const &tile_obj : baton_data_->tiles) {
        if (vtile::within_target(*tile_obj, target_z, target_x, target_y)) {
          vtzero::data_view tile_view{};
          tile_view = tile_obj->data;

          std::uint32_t zoom_factor = 1U << (target_z - tile_obj->z);
          std::vector<std::string> include_layers = tile_obj->layers;
          vtzero::vector_tile tile{tile_view};
          while (auto layer = tile.next_layer()) {
            vtzero::data_view const name = layer.name();
            std::uint32_t const version = layer.version();
            if (std::find(std::begin(names), std::end(names), name) ==
                std::end(names)) {
              std::string sname(name);
              if (include_layers.empty() ||
                  std::find(std::begin(include_layers),
                            std::end(include_layers),
                            sname) != std::end(include_layers)) {
                names.push_back(name);
                std::uint32_t extent = layer.extent();
                if (zoom_factor == 1) {
                  builder.add_existing_layer(layer);
                } else {
                  using coordinate_type = std::int64_t;
                  using feature_builder_type =
                      vtile::overzoomed_feature_builder<coordinate_type>;
                  vtzero::layer_builder layer_builder{builder, name, version,
                                                      extent};
                  vtzero::property_mapper mapper{layer, layer_builder};
                  std::uint32_t dx = 0;
                  std::uint32_t dy = 0;
                  std::tie(dx, dy) = vtile::displacement(
                      tile_obj->z, extent, target_z, target_x, target_y);
                  mapbox::geometry::box<coordinate_type> bbox{
                      {-buffer_size, -buffer_size},
                      {static_cast<int>(extent) + buffer_size,
                       static_cast<int>(extent) + buffer_size}};
                  feature_builder_type f_builder{
                      layer_builder, mapper, bbox, dx, dy, zoom_factor};
                  if (version == MVT_VERSION_1) {
                    layer.for_each_feature(
                        build_feature_from_v1<feature_builder_type>(f_builder));
                  } else {
                    layer.for_each_feature(
                        build_feature_from_v2<feature_builder_type>(f_builder));
                  }
                }
              }
            }
          }
        } else {
          std::ostringstream os;
          os << "Invalid tile composite request: SOURCE(" << tile_obj->z << ","
             << tile_obj->x << "," << tile_obj->y << ")"
             << " TARGET(" << target_z << "," << target_x << "," << target_y
             << ")";
          set_error(os.str());
          return;
        }
      }
      std::string &tile_buffer = *output_buffer_;
      builder.serialize(tile_buffer);
    } catch (std::exception const &e) {
      set_error(e.what());
    }
  }

  void set_error(const std::string &err) {
    error_message_.reset();
    error_message_ = std::make_unique<std::string>(err);
  }

  const std::string *get_result() {
    if (output_buffer_) {
      return output_buffer_.get();
    }
    return nullptr;
  }

  std::unique_ptr<baton_type> const baton_data_;
  std::unique_ptr<std::string> output_buffer_;
  std::unique_ptr<std::string> error_message_;
};

std::string composite(std::unique_ptr<baton_type> baton_data, bool *error) {
  composite_worker work(std::move(baton_data));
  work.execute();
  if (work.error_message_) {
    *error = true;
    return *work.error_message_;
  }
  return *work.get_result();
}
} // namespace vtile