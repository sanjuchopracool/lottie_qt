set (HEADER_FILES_ALL
    composition/animation_container.h
    composition/animation_nodes/animation_node.h
    composition/animation_nodes/animation_node_factory.h
    composition/animation_nodes/compound_trim_path.h
    composition/animation_nodes/ellipse_node.h
    composition/animation_nodes/fill_node.h
    composition/animation_nodes/group_node.h
    composition/animation_nodes/path_algorithm.h
    composition/animation_nodes/path_node.h
    composition/animation_nodes/polystar_node.h
    composition/animation_nodes/rectangle_node.h
    composition/animation_nodes/repeater_node.h
    composition/animation_nodes/shape_node.h
    composition/animation_nodes/shape_path_node.h
    composition/animation_nodes/shape_transformation_node.h
    composition/animation_nodes/stroke_node.h
    composition/animation_nodes/transformation_node.h
    composition/animation_nodes/trim_node.h
    composition/base_composition_layer.h
    composition/composition_layer_factory.h
    composition/interfaces/painting_element.h
    composition/interfaces/trim_element.h
    composition/null_composition_layer.h
    composition/shape_composition_layer.h
    composition/solid_composition_layer.h
    lottielib.h
    model/composition.h
    model/keyframes/keyframe.h
    model/layers/layer.h
    model/layers/layer_factory.h
    model/layers/shape_layer.h
    model/layers/solid_layer.h
    model/property_system/constant_property.h
    model/property_system/keyframe_property.h
    model/property_system/property.h
    model/property_system/property_factory.h
    model/property_system/property_update_listener.h
    model/property_system/update_listener.h
    model/shape_items/ellipse.h
    model/shape_items/fill.h
    model/shape_items/group.h
    model/shape_items/merge.h
    model/shape_items/polystar.h
    model/shape_items/rectangle.h
    model/shape_items/repeater.h
    model/shape_items/shape.h
    model/shape_items/shape_factory.h
    model/shape_items/shape_item.h
    model/shape_items/shape_transformation.h
    model/shape_items/stroke.h
    model/shape_items/trim.h
    parser/lottie/composition_parser.h
    parser/lottie/property_parser.h
    profiler.h
    third_party/minitrace/minitrace.h
    utility/interpolatable/interpolatable.h
    utility/primitives/bezier_path.h
    utility/primitives/curve_vertex.h
    utility/primitives/dash_element.h
    utility/primitives/keypath_searchable.h
    utility/primitives/path_element.h
    utility/primitives/transformation.h
    utility/primitives/utility.h
    utility/value_provider/keyframe_value_provider.h
    utility/value_provider/single_value_provider.h
)

set (SRC_FILES_ALL
    composition/animation_container.cpp
    composition/animation_nodes/animation_node_factory.cpp
    composition/animation_nodes/compound_trim_path.cpp
    composition/animation_nodes/ellipse_node.cpp
    composition/animation_nodes/fill_node.cpp
    composition/animation_nodes/group_node.cpp
    composition/animation_nodes/path_algorithm.cpp
    composition/animation_nodes/polystar_node.cpp
    composition/animation_nodes/rectangle_node.cpp
    composition/animation_nodes/repeater_node.cpp
    composition/animation_nodes/shape_node.cpp
    composition/animation_nodes/shape_path_node.cpp
    composition/animation_nodes/shape_transformation_node.cpp
    composition/animation_nodes/stroke_node.cpp
    composition/animation_nodes/transformation_node.cpp
    composition/animation_nodes/trim_node.cpp
    composition/base_composition_layer.cpp
    composition/composition_layer_factory.cpp
    composition/null_composition_layer.cpp
    composition/shape_composition_layer.cpp
    composition/solid_composition_layer.cpp
    model/composition.cpp
    model/layers/layer.cpp
    model/layers/layer_factory.cpp
    model/layers/shape_layer.cpp
    model/layers/solid_layer.cpp
    model/shape_items/ellipse.cpp
    model/shape_items/fill.cpp
    model/shape_items/group.cpp
    model/shape_items/merge.cpp
    model/shape_items/polystar.cpp
    model/shape_items/rectangle.cpp
    model/shape_items/repeater.cpp
    model/shape_items/shape.cpp
    model/shape_items/shape_factory.cpp
    model/shape_items/shape_item.cpp
    model/shape_items/shape_transformation.cpp
    model/shape_items/stroke.cpp
    model/shape_items/trim.cpp
    parser/lottie/composition_parser.cpp
    third_party/minitrace/minitrace.c
    utility/primitives/bezier_path.cpp
    utility/primitives/curve_vertex.cpp
    utility/primitives/dash_element.cpp
    utility/primitives/path_element.cpp
    utility/primitives/transformation.cpp
)

set (DIRECTORY_PREFIX "${CMAKE_CURRENT_SOURCE_DIR}/")
message(STATUS    ${DIRECTORY_PREFIX})
list(TRANSFORM HEADER_FILES_ALL PREPEND ${DIRECTORY_PREFIX})
list(TRANSFORM SRC_FILES_ALL PREPEND ${DIRECTORY_PREFIX})

message(STATUS    ${HEADER_FILES_ALL})
message(STATUS    ${SRC_FILES_ALL})
add_library(eao
    ${HEADER_FILES_ALL}
    ${SRC_FILES_ALL}
)

target_link_libraries(eao PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(eao PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

