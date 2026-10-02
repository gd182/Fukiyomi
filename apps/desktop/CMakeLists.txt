find_package(Qt6 REQUIRED COMPONENTS Quick)
qt_standard_project_setup(REQUIRES 6.8)

qt_add_executable(fukiyomi main.cpp)

qt_add_qml_module(fukiyomi
    URI FukiyomiApp
    QML_FILES Main.qml
)

target_link_libraries(fukiyomi PRIVATE fukiyomi_core fukiyomi_sources Qt6::Quick)