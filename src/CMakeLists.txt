add_library(pony
  pony.cpp pony.h)
target_link_libraries(pony PRIVATE ponies)

add_library(pratchett
  pratchett.cpp pratchett.h)
target_link_libraries(pratchett PRIVATE pratchett_res)

add_executable(pratchett-pony main.cpp)
target_link_libraries(pratchett-pony pony pratchett)
