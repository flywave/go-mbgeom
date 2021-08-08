package geojson

import (
	"io/ioutil"
	"os"
	"testing"
)

func TestGeoJSON(t *testing.T) {
	f, _ := os.Open("../data/countries.geojson")
	bytes, _ := ioutil.ReadAll(f)

	json := Parse(string(bytes))

	if json == nil && !json.IsFeatureCollection() {
		t.FailNow()
	}
}
