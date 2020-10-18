include(CMakeFindDependencyMacro)
find_dependency(Qt5 REQUIRED COMPONENTS Core Sql Xml)
include("${CMAKE_CURRENT_LIST_DIR/PraalineCoreTargets.cmake")
