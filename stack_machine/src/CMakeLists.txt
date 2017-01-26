set(core_SRCS main.cpp)

add_library(core ${core_SRCS})
add_executable(exe main.cpp stack_machine.cpp int_stack.cpp)
target_link_libraries(exe core)

#add_executable(Algo ${SOURCE_FILES})