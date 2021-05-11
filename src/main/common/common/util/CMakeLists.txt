add_subdirectory(test)

add_library(
        common_util_lib SHARED
        file_util.cpp
        hash_util.cpp
        string_util.cpp
        time_util.cpp
)

install(TARGETS
        common_util_lib
        DESTINATION lib)

install(FILES
        file_util.h
        hash_util.h
        lru_cache.h
        lfu_cache.h
        string_util.h
        time_util.h
        CLI11.hpp
        DESTINATION include/common/util)
