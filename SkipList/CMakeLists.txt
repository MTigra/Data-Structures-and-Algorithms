set(core_SRCS main.cpp)

add_library(core ${core_SRCS})
add_executable(exe main.cpp NetActivity.cpp TimeStamp.cpp JournalNetActivity.hpp OrderedList.hpp SkipList.hpp)
target_link_libraries(exe core)