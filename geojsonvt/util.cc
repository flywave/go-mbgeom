#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wpragmas"
#pragma GCC diagnostic ignored "-Wsign-conversion"
#pragma GCC diagnostic ignored "-Wsign-compare"
#pragma GCC diagnostic ignored "-Wconversion"
#pragma GCC diagnostic ignored "-Wold-style-cast"
#pragma GCC diagnostic ignored "-Wpadded"
#pragma GCC diagnostic ignored "-Wfloat-equal"

#include <mapbox/geojsonvt/tile.hpp>
#include <mapbox/geojsonvt/types.hpp>
#include <mapbox/geometry.hpp>
#include <mapbox/geometry_io.hpp>
#include <mapbox/variant_io.hpp>
#include <rapidjson/document.h>
#include <rapidjson/error/en.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#pragma GCC diagnostic pop

#include <fstream>
#include <map>
#include <sstream>

#include "util.hh"

namespace mapbox {
namespace geojsonvt {

std::string loadFile(const std::string &filename) {
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in) {
    std::ostringstream contents;
    contents << in.rdbuf();
    in.close();
    return contents.str();
  }
  throw std::runtime_error("Error opening file");
}

mapbox::feature::feature_collection<int16_t> parseJSONTile(
    const rapidjson::GenericValue<rapidjson::UTF8<>, rapidjson::CrtAllocator>
        &tile) {
  mapbox::feature::feature_collection<int16_t> features;
  // EXPECT_TRUE(tile.IsArray());
  for (rapidjson::SizeType k = 0; k < tile.Size(); ++k) {
    const auto &feature = tile[k];

    mapbox::feature::feature<short> feat{mapbox::geometry::point<short>()};

    if (feature.HasMember("tags") && feature["tags"].IsObject()) {
      const auto &tags = feature["tags"];
      for (auto jt = tags.MemberBegin(); jt != tags.MemberEnd(); jt++) {
        const std::string tagKey{jt->name.GetString(),
                                 jt->name.GetStringLength()};
        switch (jt->value.GetType()) {
        case rapidjson::kNullType:
          feat.properties.emplace(tagKey, mapbox::feature::null_value);
          break;
        case rapidjson::kFalseType:
          feat.properties.emplace(tagKey, false);
          break;
        case rapidjson::kTrueType:
          feat.properties.emplace(tagKey, true);
          break;
        case rapidjson::kStringType:
          feat.properties.emplace(
              tagKey,
              std::string{jt->value.GetString(), jt->value.GetStringLength()});
          break;
        case rapidjson::kNumberType:
          if (jt->value.IsUint64()) {
            feat.properties.emplace(tagKey,
                                    std::uint64_t(jt->value.GetUint64()));
          } else if (jt->value.IsInt64()) {
            feat.properties.emplace(tagKey, std::int64_t(jt->value.GetInt64()));
          } else {
            feat.properties.emplace(tagKey, jt->value.GetDouble());
          }
          break;
        }
      }
    }

    if (feature.HasMember("id")) {
      //  EXPECT_TRUE(feature["id"].IsString() || feature["id"].IsNumber());
      if (feature["id"].IsString()) {
        feat.id = {std::string{feature["id"].GetString(),
                               feature["id"].GetStringLength()}};
      } else {
        feat.id = {std::uint64_t{feature["id"].GetUint64()}};
      }
    }

    if (feature.HasMember("type") && feature.HasMember("geometry")) {
      const auto &geometry = feature["geometry"];
      const auto &type = feature["type"];
      // EXPECT_TRUE(type.IsInt());
      //  EXPECT_TRUE(geometry.IsArray());
      uint16_t geomType = type.GetInt();
      // point geometry
      if (geomType == 1) {
        for (rapidjson::SizeType j = 0; j < geometry.Size(); ++j) {
          const auto &pt = geometry[j];
          // EXPECT_TRUE(pt.IsArray());
          // EXPECT_TRUE(pt.Size() >= 2);
          //  EXPECT_TRUE(pt[0].IsNumber());
          //  EXPECT_TRUE(pt[1].IsNumber());
          feat.geometry = mapbox::geometry::point<int16_t>(
              static_cast<int16_t>(pt[0].GetInt()),
              static_cast<int16_t>(pt[1].GetInt()));
        }
        // linestring geometry
      } else if (geomType == 2) {
        mapbox::geometry::multi_line_string<int16_t> multi_line;
        const bool is_multi = geometry.Size() > 1;
        for (rapidjson::SizeType j = 0; j < geometry.Size(); ++j) {
          const auto &part = geometry[j];
          // EXPECT_TRUE(part.IsArray());
          mapbox::geometry::line_string<int16_t> line_string;
          for (rapidjson::SizeType i = 0; i < part.Size(); ++i) {
            const auto &pt = part[i];
            // EXPECT_TRUE(pt.IsArray());
            // EXPECT_TRUE(pt.Size() >= 2);
            // EXPECT_TRUE(pt[0].IsNumber());
            // EXPECT_TRUE(pt[1].IsNumber());
            line_string.emplace_back(static_cast<int16_t>(pt[0].GetInt()),
                                     static_cast<int16_t>(pt[1].GetInt()));
          }
          if (!is_multi) {
            feat.geometry = line_string;
            break;
          } else {
            multi_line.emplace_back(line_string);
          }
        }
        if (is_multi)
          feat.geometry = multi_line;
        // polygon geometry
      } else if (geomType == 3) {
        mapbox::geometry::polygon<int16_t> poly;
        for (rapidjson::SizeType j = 0; j < geometry.Size(); ++j) {
          const auto &ring = geometry[j];
          // EXPECT_TRUE(ring.IsArray());
          mapbox::geometry::linear_ring<int16_t> linear_ring;
          for (rapidjson::SizeType i = 0; i < ring.Size(); ++i) {
            const auto &pt = ring[i];
            // EXPECT_TRUE(pt.IsArray());
            // EXPECT_TRUE(pt.Size() >= 2);
            // EXPECT_TRUE(pt[0].IsNumber());
            // EXPECT_TRUE(pt[1].IsNumber());
            linear_ring.emplace_back(static_cast<int16_t>(pt[0].GetInt()),
                                     static_cast<int16_t>(pt[1].GetInt()));
          }
          poly.emplace_back(linear_ring);
        }
        feat.geometry = poly;
      }
    }

    features.emplace_back(feat);
  }

  return features;
}

mapbox::feature::feature_collection<int16_t>
parseJSONTile(const std::string &data) {
  rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> d;
  d.Parse<0>(data.c_str());

  if (d.HasParseError()) {
    std::stringstream message;
    message << "JSON error at " << d.GetErrorOffset() << " - "
            << rapidjson::GetParseError_En(d.GetParseError());
    throw std::runtime_error(message.str());
  }
  return parseJSONTile(d);
}

std::map<std::string, mapbox::feature::feature_collection<int16_t>>
parseJSONTiles(const std::string &data) {
  std::map<std::string, mapbox::feature::feature_collection<int16_t>> result;
  rapidjson::GenericDocument<rapidjson::UTF8<>, rapidjson::CrtAllocator> d;
  d.Parse<0>(data.c_str());

  if (d.HasParseError()) {
    std::stringstream message;
    message << "JSON error at " << d.GetErrorOffset() << " - "
            << rapidjson::GetParseError_En(d.GetParseError());
    throw std::runtime_error(message.str());
  }
  // EXPECT_TRUE(d.IsObject());
  for (auto it = d.MemberBegin(); it != d.MemberEnd(); it++) {
    const std::string key{it->name.GetString(), it->name.GetStringLength()};
    const auto &tile = it->value;

    result.emplace(key, parseJSONTile(tile));
  }

  return result;
}

} // namespace geojsonvt
} // namespace mapbox