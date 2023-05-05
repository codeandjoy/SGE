add_executable(ui.out ui.cpp ../../SGE.hpp)

target_link_libraries(ui.out -ltmxlite -lsfml-graphics -lsfml-window -lsfml-system)