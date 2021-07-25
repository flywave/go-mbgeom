package vtile

type GeomType uint32

const (
	UNKNOWN    GeomType = 0
	POINT      GeomType = 1
	LINESTRING GeomType = 2
	POLYGON    GeomType = 3
)

var (
	GeomTypeStrs = []string{"unknown", "point", "linestring", "polygon"}
)

type PropertyValueType uint32

const (
	StringValue PropertyValueType = 1
	FloatValue  PropertyValueType = 2
	DoubleValue PropertyValueType = 3
	IntValue    PropertyValueType = 4
	UIntValue   PropertyValueType = 5
	SIntValue   PropertyValueType = 6
	BoolValue   PropertyValueType = 7
)
