add_executable(pong.out pong.cpp ../../SGE.hpp)

target_link_libraries(pong.out -ltmxlite -lsfml-graphics -lsfml-window -lsfml-system)