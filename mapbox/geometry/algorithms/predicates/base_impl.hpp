//
#pragma once
#include <mapbox/geometry.hpp>
#include <mapbox/geometry/algorithms/detail/boost_adapters.hpp>
#include <mapbox/geometry/algorithms/detail/predicate_dispatcher.hpp>

namespace mapbox {
namespace geometry {
namespace algorithms {

namespace detail {

template <typename CoordinateType>
struct is_implemented<mapbox::geometry::point<CoordinateType>>
{
    static constexpr bool value = true;
};

template <typename CoordinateType>
struct is_implemented<mapbox::geometry::line_string<CoordinateType>>
{
    static constexpr bool value = true;
};

template <typename CoordinateType>
struct is_implemented<mapbox::geometry::polygon<CoordinateType>>
{
    static constexpr bool value = true;
};

template <typename CoordinateType>
struct is_implemented<mapbox::geometry::multi_point<CoordinateType>>
{
    static constexpr bool value = true;
};
}
}
}
}
