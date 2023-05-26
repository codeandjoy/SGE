add_executable(sfx.out sfx.cpp ../../SGE.hpp)

target_link_libraries(sfx.out -ltmxlite -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system)