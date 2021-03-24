# Minimum required CMake version
cmake_minimum_required(VERSION 3.12)
cmake_policy(VERSION 3.12)

# Add project code 
add_subdirectory(src)

# Add unit tests
# enable_testing()
# add_subdirectory(test)