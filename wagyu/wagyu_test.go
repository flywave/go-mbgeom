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

	solution := geojson.NewEmptyMultiPolygon()

	ctx.AddRing(ring, PolygonTypeSubject)

	f := ctx.Execute(ClipTypeUnion, solution, FillTypePositive, FillTypePositive)

	if !f {
		t.FailNow()
	}

	if solution.Count() != 1 {
		t.FailNow()
	}

	raw := solution.Data()

	if raw[0][0][2][1] != 1 {
		t.FailNow()
	}
}
