use crate::osm;
use crate::utils;
use crate::setters_getters_gen;

use std::ffi::CString;
use std::ffi::c_void;

pub fn override_shape_point()
{
    unsafe {
        // Create a new OSM node, we use it later to load/modify/store a specific shape point
        let node : *mut c_void = osm::osmnode_new(1);

        // Load the way nodes from a file
        let mut way_nodes : *mut c_void = std::ptr::null_mut();
        let mut way_count: u64 = 0;
        let way_nodes_path = "/path/to/way_nodes.bin";
        let way_nodes_file_name = CString::new(way_nodes_path).expect("Failed to create CString");
        osm::osmwaynode_import(way_nodes_file_name.as_ptr(), &mut way_nodes, &mut way_count);
        println!("Imported {} way nodes from {}", way_count, way_nodes_path);

        // set one specific shape point
        let interesting_way_node_index = 2406;
        osm::osmwaynode_get_node(way_nodes, interesting_way_node_index, node);
        let (encoded_lat, encoded_lon) = utils::encode_lat_lon(51.51243256895147, 4.168995059785983);
        setters_getters_gen::osmnode_set_lat7_(node, 0, encoded_lat);
        setters_getters_gen::osmnode_set_lng7_(node, 0, encoded_lon);
        osm::osmwaynode_set_node(way_nodes, interesting_way_node_index, node);
        
        // Write to output file that will be loaded by Valhalla
        osm::write_osmwaynodes_to_file(way_nodes, way_count, "/tmp/way_nodes_modified.bin");
    }
}