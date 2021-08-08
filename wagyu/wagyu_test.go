package wagyu

import (
	"testing"

	"github.com/flywave/go-mbgeom/geojson"
)

func TestClipRing(t *testing.T) {
	ring := geojson.NewLinearRing([][2]float64{
		{0, 0},
		{1, 0},
		{1, 1},
		{0, 1},
		{0, 0},
	})

	ctx := NewContext()

	if ctx != nil && ring != nil {
	}
}
