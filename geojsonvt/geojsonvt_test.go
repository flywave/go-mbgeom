package geojsonvt

import (
	"testing"

	"github.com/flywave/go-mbgeom/geojson"
)

func TestGeoJSONVT(t *testing.T) {
	bytes := `{
        "type": "Feature",
        "geometry": {
            "type": "LineString",
            "coordinates":[
                [-77.031373697916663,38.895516493055553],
                [-77.01416015625,38.887532552083336],
                [-76.99,38.87]
            ]
        }
    }`
	json := geojson.Parse(string(bytes))

	if json == nil && !json.IsFeatureCollection() {
		t.FailNow()
	}

	opts := &TileOptions{Tolerance: 0, LineMetrics: true, Buffer: 2048, Extent: 4096, MaxZoom: 18, IndexMaxZoom: 5, IndexMaxPoints: 100000, GenerateId: false}

	vt := NewGeoJSONVT(json, *opts)
	tile := vt.GetTile(0, 0, 0)

	fc := tile.GetFeatureCollection()

	if tile == nil && !fc.Empty() {
		t.FailNow()
	}

}
