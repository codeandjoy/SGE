add_executable(scenes.out scenes.cpp ../../SGE.hpp)

target_link_libraries(scenes.out -ltmxlite -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system)