package wagyu

/*
#include "wagyu_c_api.h"
#cgo CFLAGS: -I ./ -I ./external/
#cgo linux LDFLAGS: -L ./lib  -Wl,--start-group -ldl -lm -Wl,--end-group
#cgo darwin LDFLAGS: -L ./lib  -lm
*/
import "C"
