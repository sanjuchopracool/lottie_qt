find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(app
    AnimationWidget.h
    AnimationWidget.cpp
    main.cpp
    timeline_widget.h
    timeline_widget.cpp
    timelinewidget.ui
)

target_link_libraries(app PRIVATE Qt6::Widgets eao)

