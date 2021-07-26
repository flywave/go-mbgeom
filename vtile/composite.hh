#pragma once

#include <algorithm>
#include <string>
#include <memory>
#include <vector>

#include <vtzero/types.hpp>

namespace vtile {

struct tile_object {
  tile_object(uint32_t z0, uint32_t x0, uint32_t y0,
              const char *data, size_t size, std::vector<std::string> layers0)
      : z{z0}, x{x0}, y{y0}, data{data, size}, layers{std::move(layers0)} {}

  ~tile_object() noexcept {}

  tile_object(tile_object const &) = delete;
  tile_object &operator=(tile_object const &) = delete;

  tile_object(tile_object &&) = delete;
  tile_object &operator=(tile_object &&) = delete;

  uint32_t z;
  uint32_t x;
  uint32_t y;
  vtzero::data_view data;
  std::vector<std::string> layers;
};

struct baton_type {
  explicit baton_type(std::size_t num_tiles) { tiles.reserve(num_tiles); }

  ~baton_type() = default;

  baton_type(baton_type const &) = delete;
  baton_type &operator=(baton_type const &) = delete;

  baton_type(baton_type &&) = delete;
  baton_type &operator=(baton_type &&) = delete;

  std::vector<std::unique_ptr<tile_object>> tiles{};
  uint32_t z{};
  uint32_t x{};
  uint32_t y{};
  int buffer_size = 0;
};

std::string composite(std::unique_ptr<baton_type> baton_data, bool *error);

} // namespace vtile