#pragma once

#include <mapbox/geojson.hpp>
#include <mapbox/geojson/rapidjson.hpp>

#include <rapidjson/document.h>
#include <rapidjson/writer.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/error/en.h>

#include <sstream>

namespace mapbox {
namespace geojson {

template <>
rapidjson_value convert<mapbox::geometry::geometry<int16_t>>(const mapbox::geometry::geometry<int16_t>&, rapidjson_allocator&);

template <>
rapidjson_value convert<mapbox::feature::feature<int16_t>>(const mapbox::feature::feature<int16_t>&, rapidjson_allocator&);

template <>
rapidjson_value convert<mapbox::feature::feature_collection<int16_t>>(const mapbox::feature::feature_collection<int16_t>&, rapidjson_allocator&);

struct to_type_16 {
public:
    const char * operator()(const empty&) {
        abort();
    }

    const char * operator()(const mapbox::geometry::point<int16_t>&) {
        return "Point";
    }

    const char * operator()(const mapbox::geometry::line_string<int16_t>&) {
        return "LineString";
    }

    const char * operator()(const mapbox::geometry::polygon<int16_t>&) {
        return "Polygon";
    }

    const char * operator()(const mapbox::geometry::multi_point<int16_t>&) {
        return "MultiPoint";
    }

    const char * operator()(const mapbox::geometry::multi_line_string<int16_t>&) {
        return "MultiLineString";
    }

    const char * operator()(const mapbox::geometry::multi_polygon<int16_t>&) {
        return "MultiPolygon";
    }

    const char * operator()(const mapbox::geometry::geometry_collection<int16_t>&) {
        return "GeometryCollection";
    }
};

struct to_value_16 {
    rapidjson_allocator& allocator;

    rapidjson_value operator()(null_value_t) {
        rapidjson_value result;
        result.SetNull();
        return result;
    }

    rapidjson_value operator()(bool t) {
        rapidjson_value result;
        result.SetBool(t);
        return result;
    }

    rapidjson_value operator()(int64_t t) {
        rapidjson_value result;
        result.SetInt64(t);
        return result;
    }

    rapidjson_value operator()(uint64_t t) {
        rapidjson_value result;
        result.SetUint64(t);
        return result;
    }

    rapidjson_value operator()(double t) {
        rapidjson_value result;
        result.SetDouble(t);
        return result;
    }

    rapidjson_value operator()(const std::string& t) {
        rapidjson_value result;
        result.SetString(t.data(), rapidjson::SizeType(t.size()), allocator);
        return result;
    }

    rapidjson_value operator()(const  std::shared_ptr<std::vector<value> > array) {
        rapidjson_value result;
        result.SetArray();
        for (const auto& item : *array) {
            result.PushBack(value::visit(item, *this), allocator);
        }
        return result;
    }

    rapidjson_value operator()(const std::shared_ptr<std::unordered_map<std::string, value>> map) {
        rapidjson_value result;
        result.SetObject();
        for (const auto& property : *map) {
            result.AddMember(
                rapidjson::GenericStringRef<char> {
                    property.first.data(),
                    rapidjson::SizeType(property.first.size())
                },
                value::visit(property.second, *this),
                allocator);
        }
        return result;
    }

    rapidjson_value operator()(const std::unordered_map<std::string, value> &map) {
        rapidjson_value result;
        result.SetObject();
        for (const auto& property : map) {
            result.AddMember(
                rapidjson::GenericStringRef<char> {
                    property.first.data(),
                    rapidjson::SizeType(property.first.size())
                },
                value::visit(property.second, *this),
                allocator);
        }
        return result;
    }
};

struct to_coordinates_or_geometries_16 {
    rapidjson_allocator& allocator;

    // Handles line_string, polygon, multi_point, multi_line_string, multi_polygon, and geometry_collection.
    template <class E>
    rapidjson_value operator()(const std::vector<E>& vector) {
        rapidjson_value result;
        result.SetArray();
        for (std::size_t i = 0; i < vector.size(); ++i) {
            result.PushBack(operator()(vector[i]), allocator);
        }
        return result;
    }

    rapidjson_value operator()(const mapbox::geometry::point<int16_t>& element) {
        rapidjson_value result;
        result.SetArray();
        result.PushBack(element.x, allocator);
        result.PushBack(element.y, allocator);
        return result;
    }

    rapidjson_value operator()(const empty&) {
        abort();
    }

    rapidjson_value operator()(const mapbox::geometry::geometry<int16_t>& element) {
        return convert(element, allocator);
    }
};

template <>
rapidjson_value convert<mapbox::geometry::geometry<int16_t>>(const mapbox::geometry::geometry<int16_t>& element, rapidjson_allocator& allocator) {
    if (element.is<empty>())
        return rapidjson_value(rapidjson::kNullType);

    rapidjson_value result(rapidjson::kObjectType);

    result.AddMember(
        "type",
        rapidjson::GenericStringRef<char> { mapbox::geometry::geometry<int16_t>::visit(element, to_type_16()) },
        allocator);

    result.AddMember(
        rapidjson::GenericStringRef<char> { element.is<mapbox::geometry::geometry_collection<int16_t>>() ? "geometries" : "coordinates" },
        mapbox::geometry::geometry<int16_t>::visit(element, to_coordinates_or_geometries_16 { allocator }),
        allocator);

    return result;
}

template <>
rapidjson_value convert<mapbox::feature::feature<int16_t>>(const mapbox::feature::feature<int16_t>& element, rapidjson_allocator& allocator) {
    rapidjson_value result(rapidjson::kObjectType);
    result.AddMember("type", "Feature", allocator);

    if (!element.id.is<null_value_t>()) {
        result.AddMember("id", mapbox::feature::identifier::visit(element.id, to_value_16 { allocator }), allocator);
    }

    result.AddMember("geometry", convert(element.geometry, allocator), allocator);
    result.AddMember("properties", to_value_16 { allocator }(element.properties), allocator);

    return result;
}

template <>
rapidjson_value convert<mapbox::feature::feature_collection<int16_t>>(const mapbox::feature::feature_collection<int16_t>& collection, rapidjson_allocator& allocator) {
    rapidjson_value result(rapidjson::kObjectType);
    result.AddMember("type", "FeatureCollection", allocator);

    rapidjson_value features(rapidjson::kArrayType);
    for (const auto& element : collection) {
        features.PushBack(convert(element, allocator), allocator);
    }
    result.AddMember("features", features, allocator);

    return result;
}

template <class T>
std::string stringifyvt(const T& t) {
    rapidjson_allocator allocator;
    rapidjson::StringBuffer buffer;
    rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
    convert(t, allocator).Accept(writer);
    return buffer.GetString();
}

} // namespace geojson
} // namespace mapbox
