#include "geojsonvt_c_api.h"
#include "geom_c_api_impl.hh"
#include "util.hh"

#include <mapbox/geojson.hpp>
#include <mapbox/geojsonvt.hpp>
#include <mapbox/geojsonvt/clip.hpp>
#include <mapbox/geojsonvt/convert.hpp>
#include <mapbox/geojsonvt/simplify.hpp>
#include <mapbox/geojsonvt_impl.hpp>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>


#include <mapbox/geojson_impl.hpp>


int main(int argc, char **argv) {
  std::string jsondata = mapbox::geojsonvt::loadFile("../data/countries.geojson");
  auto feats = mapbox::geojson::parse(jsondata);
  mapbox::geojsonvt::Options opt;
  auto vt = mapbox::geojsonvt::GeoJSONVT(feats, opt);

  auto tile = vt.getTile(0, 0, 0);

  auto json = mapbox::geojson::stringify(tile.source_features);

  std::cout << json << std::endl;
}