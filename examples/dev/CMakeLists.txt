add_executable(dev.out dev.cpp ../../SGE.hpp)

target_link_libraries(dev.out -ltmxlite -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system)