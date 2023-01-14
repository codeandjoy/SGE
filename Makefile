.PHONY: clean

OUT = build/main.out

_src = main.cpp Universe.cpp utils/readTiledMapData.cpp Entity.cpp PhysicalObject.cpp Gravity.cpp TextureSheet.cpp Animation.cpp TextureManager.cpp PhysicsManager.cpp Moveable.cpp SolidObject.cpp CollisionManager.cpp
src = $(addprefix src/,$(_src))

_objects = main.o Universe.o readTiledMapData.o Entity.o PhysicalObject.o Gravity.o TextureSheet.o Animation.o TextureManager.o PhysicsManager.o Moveable.o SolidObject.o CollisionManager.o
objects = $(addprefix build/obj/,$(_objects))

lib = -ltmxlite -ljsoncpp -lsfml-graphics -lsfml-window -lsfml-system

all: $(OUT)

$(OUT): $(objects)
	g++ -o $(OUT) $(objects) $(lib)

$(objects): $(src)
	g++ -c $(src); \
	mkdir -p ./build/obj; \
	mv *.o ./build/obj;

clean:
	rm -rf build