add_executable(state.out state.cpp ../../SGE.hpp)

target_link_libraries(state.out -ltmxlite -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-system)