# Minimum required CMake version
cmake_minimum_required(VERSION 3.12)
cmake_policy(VERSION 3.12)

project(PraalineCoreTests)

# Dependencies
enable_testing()
find_package(GTest MODULE REQUIRED)
if (NOT TARGET Praaline::Core)
	find_package(PraalineCore CONFIG REQUIRED)
endif()

add_executable(PraalineCoreTests tests_source.cpp)
target_link_libraries(PraalineCoreTests
	PRIVATE
		Praaline::Core
		GTest::Main
)

add_test(NAME PraalineCore.UnitTests
	COMMAND PraalineCoreTests
)
