cmake_minimum_required(VERSION 3.12)
project(pratchett-pony)

set(CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Setup the pony resources
include("cmrc/CMakeRC.cmake")
file(GLOB PONY_FILES ponysay/ponies/*)
cmrc_add_resource_library(ponies  WHENCE ponysay/ponies ${PONY_FILES})
cmrc_add_resource_library(pratchett_res  WHENCE pratchett pratchett/pqf)

add_subdirectory(src)
