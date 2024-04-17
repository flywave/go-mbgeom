package geojsonvt

import (
	"io/ioutil"
	"os"
	"testing"

	"github.com/flywave/go-mbgeom/geojson"
)

func TestGeoJSONVT(t *testing.T) {
	f, _ := os.Open("../data/countries.geojson")
	bytes, _ := ioutil.ReadAll(f)

	json := geojson.Parse(string(bytes))

	if json == nil && !json.IsFeatureCollection() {
		t.FailNow()
	}

	opts := &TileOptions{Tolerance: 0, LineMetrics: true, Buffer: 2048, Extent: 4096, MaxZoom: 4, IndexMaxZoom: 5, IndexMaxPoints: 100000, GenerateId: false}

	vt := NewGeoJSONVT(json, *opts)
	tile := vt.GetTile(0, 0, 0)

	fc := tile.GetSourceFeatureCollection()

	if tile == nil && !fc.Empty() {
		t.FailNow()
	}

	jsonvt := fc.Stringify()

	if jsonvt == "" {
		t.FailNow()
	}
}

func TestGeoJSONVTParserStringify(t *testing.T) {
	f, _ := os.Open("../data/us-states-tiles.json")
	bytes, _ := ioutil.ReadAll(f)

	jsonvt := ParseFeatureCollections(string(bytes))

	data := StringifyFeatureCollections(jsonvt)

	if data == "" && jsonvt != nil {
		t.FailNow()
	}
}
