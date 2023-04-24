add_executable(collision_phase.out collision_phase.cpp ../../SGE.hpp)

target_link_libraries(collision_phase.out -ltmxlite -lsfml-graphics -lsfml-window -lsfml-system)