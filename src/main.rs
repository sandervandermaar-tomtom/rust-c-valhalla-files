mod setters_getters_gen;
mod utils;
mod osm;
mod set_shapepoint;

use std::ffi::CString;
use std::ffi::c_void;

fn main() {
    set_shapepoint::override_shape_point();
}
