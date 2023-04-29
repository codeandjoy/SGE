add_executable(scenes.out scenes.cpp ../../SGE.hpp)

target_link_libraries(scenes.out -ltmxlite -lsfml-graphics -lsfml-window -lsfml-system)

set_property(TARGET scenes.out PROPERTY CXX_STANDARD 20)