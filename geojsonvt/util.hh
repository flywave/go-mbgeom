#pragma once

#include <map>
#include <mapbox/geojsonvt/tile.hpp>
#include <mapbox/geojsonvt/types.hpp>
#include <mapbox/geometry.hpp>
#include <sstream>

namespace mapbox {
namespace geojsonvt {

std::string loadFile(const std::string &filename);
mapbox::feature::feature_collection<int16_t>
parseJSONTile(const std::string &data);
std::map<std::string, mapbox::feature::feature_collection<int16_t>>
parseJSONTiles(const std::string &data);

} // namespace geojsonvt
} // namespace mapbox