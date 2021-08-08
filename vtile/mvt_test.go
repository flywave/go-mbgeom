package vtile

import (
	"io/ioutil"
	"os"
	"testing"
)

func TestMVT(t *testing.T) {
	f, _ := os.Open("../data/3194.mvt")
	bytes, _ := ioutil.ReadAll(f)

	tile := NewTile(bytes)

	if tile.Empty() {
		t.FailNow()
	}
}
