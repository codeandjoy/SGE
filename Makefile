.PHONY: clean



lib = -ltmxlite -ljsoncpp -lsfml-graphics -lsfml-window -lsfml-system
obj_directory = build/obj

#
# Dev
#
dev_directory = ./examples/dev
dev = $(dev_directory)/build/dev.out

_dev_src = dev.cpp
dev_src = $(addprefix $(dev_directory)/,$(_dev_src))

_dev_obj = dev.o
dev_obj = $(addprefix $(dev_directory)/$(obj_directory)/,$(_dev_obj))


dev: $(dev)

$(dev): $(dev_obj)
	g++ -o $(dev) $(dev_obj) $(lib)

$(dev_obj): $(dev_src) SGE.hpp
	g++ -c -g $(dev_src); \
	mkdir -p $(dev_directory)/$(obj_directory); \
	mv *.o $(dev_directory)/$(obj_directory);
#
#
#

clean:
	rm -rf $(dev_directory)/build