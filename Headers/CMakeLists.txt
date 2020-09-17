add_library(
    Cache_Headers
    CacheConfig/Cache.hpp
    CacheConfig/Cache.cpp
)

target_include_directories(Cache_Headers PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/CacheConfig") 