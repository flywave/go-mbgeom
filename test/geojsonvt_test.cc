#include "geojsonvt_c_api.h"
#include "geom_c_api_impl.hh"
#include "util.hh"

#include <mapbox/geojson.hpp>
#include <mapbox/geojson_impl.hpp>
#include <mapbox/geojsonvt.hpp>
#include <mapbox/geojsonvt/clip.hpp>
#include <mapbox/geojsonvt/convert.hpp>
#include <mapbox/geojsonvt/simplify.hpp>

#include <algorithm>
#include <string>
#include <vector>

int main(int argc, char **argv) {
  const auto geojson = mapbox::geojson::parse(
      mapbox::geojsonvt::loadFile("data/linestring.json"));

  struct _geojsonvt_tile_options_t opts {
    tolerance : 0, extent : 8192, buffer : 1024,
        lineMetrics : false,
                      maxZoom : 20,
                      indexMaxZoom : 0,
                      indexMaxPoints : 10000
  };

  auto cgeojson = new _mapbox_geojson_t{geojson};

  auto cgeojsonvt = geojsonvt_new(cgeojson, opts);

  struct TileCoordinate {
    uint8_t z;
    uint32_t x;
    uint32_t y;
  };

  std::vector<TileCoordinate> tileCoordinates{
      {0, 0, 0},           {1, 0, 0},           {2, 0, 1},
      {3, 1, 3},           {4, 2, 6},           {5, 5, 12},
      {6, 10, 24},         {7, 20, 49},         {8, 40, 98},
      {9, 81, 197},        {10, 163, 395},      {11, 327, 791},
      {12, 655, 1583},     {13, 1310, 3166},    {14, 2620, 6332},
      {15, 5241, 12664},   {16, 10482, 25329},  {17, 20964, 50660},
      {18, 41929, 101320}, {19, 83859, 202640}, {20, 167719, 405281},
  };

  for (const auto tileCoordinate : tileCoordinates) {
    auto tile = geojsonvt_get_tile(cgeojsonvt, tileCoordinate.z,
                                   tileCoordinate.x, tileCoordinate.y);
  }

  delete cgeojson;
  geojsonvt_free(cgeojsonvt);
}