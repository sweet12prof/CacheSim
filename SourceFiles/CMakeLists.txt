add_library(
    sources
    main.cpp
)

add_executable(output main.cpp)

target_link_libraries(output PUBLIC Cache_Headers)