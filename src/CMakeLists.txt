file(GLOB_RECURSE SRC_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/*.h
#    ${CMAKE_CURRENT_SOURCE_DIR}/Model/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Layers/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/Model/Keyframes/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/Model/ShapeItems/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/LayerContainers/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/LayerContainers/AnimationNodes/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/NodeRenderSystem/NodeProperties/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/NodeRenderSystem/ValueProviders/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/Utility/Primitives/*.cpp
#    ${CMAKE_CURRENT_SOURCE_DIR}/Utility/Interpolatable/*.cpp
)

message(STATUS    ${SRC_FILES})
add_library(eao
    ${SRC_FILES}
)

target_link_libraries(eao PRIVATE Qt6::Core Qt6::Widgets)
target_include_directories(eao PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
