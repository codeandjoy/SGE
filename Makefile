.PHONY: clean

OUT = build/main.out

_headers = TextureSheetSizes.h CollisionGroup.h CollisionGroupType.h CollisionPair.h CollisionResponses.h CollisionDetectionAlgorithms.h Collision.h CollisionUtils.h ContinuousAction.h
headers = $(addprefix src/,$(_headers))

_src = main.cpp Universe.cpp PhysicalObject.cpp TextureSheet.cpp Animation.cpp TextureManager.cpp PhysicsManager.cpp CollisionManager.cpp
src = $(addprefix src/,$(_src))

_objects = main.o Universe.o PhysicalObject.o TextureSheet.o Animation.o TextureManager.o PhysicsManager.o CollisionManager.o
objects = $(addprefix build/obj/,$(_objects))

lib = -ltmxlite -ljsoncpp -lsfml-graphics -lsfml-window -lsfml-system

all: $(OUT)

$(OUT): $(objects)
	g++ -o $(OUT) $(objects) $(lib)

$(objects): $(src) $(headers)
	g++ -c $(src); \
	mkdir -p ./build/obj; \
	mv *.o ./build/obj;

clean:
	rm -rf build