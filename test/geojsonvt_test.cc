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
#include <string>
#include <vector>
#include<iostream>

int main(int argc, char **argv) {
  std::string jsondata = mapbox::geojsonvt::loadFile("data/us-states-tiles.json");
  std::map<std::string, mapbox::feature::feature_collection<int16_t>> feats =
      mapbox::geojsonvt::parseJSONTiles(jsondata);
  auto json = mapbox::geojson::stringifyvt(feats);

  std::cout << json <<std::endl;
}