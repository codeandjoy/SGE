# Collision phase example

- shows how to use `sge::CollisionInteraction` and how to code responses based on collision phase.

<br>

## `CollisionInteraction` and `CollisionShape`

To make `Entity` responsive to collisions, you should build it with a `CollisionShape`. Entity by default contains an empty `unordered_map` of collision shapes.

You create Entity's collision shapes the following way:

```C++
class CustomEntity : public sge::Entity{
    public:
        CustomEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position, std::vector<std::string> collisionGroups){
            // Setting up Entity's Sprite
            sprite = new sge::Sprite(*texture, textureRect);
            sprite->setPosition(position);
            //

            // Setting up Entity's collisionShapes
            collisionShapes["global_bounds"] = new sge::CollisionShape(this);
            collisionShapes["global_bounds"]->collisionGroups = collisionGroups;
            //
        }
};
```

The `collisionShapes["name"]->collisionGroups` is the most important part. Collision interaction happen between collision shapes *in* certain collision groups. So, in other words, a collision group is a marker of the behaviour that a specific collision shape has.

For instance, in this example project, when creating tile Entities, their collision shapes get assigned a group called `tiles`:

```C++
std::vector<sge::Entity*> mapTileEntities;

for(int i = 0; i < map::tileCountY; i++){
    for(int j = 0; j < map::tileCountX; j++){
        if(map::map_data[map::tileCountX*i+j] != 0){
            mapTileEntities.push_back(new sge::StaticEntity(
                universe->assetsManager->getTextureSheet("tileset")->getTexture(),
                universe->assetsManager->getTextureSheet("tileset")->getTextureRect(map::map_data[map::tileCountX*i+j] - 1),
                sf::Vector2f(j*map::tileSizeX, i*map::tileSizeY),
                {"tiles"} // == collisionShapes["global_bounds"]->collisionGroups = {"tiles"};
            ));
        }
    }
}
```

And when creating player Entity, it's collision shape gets assigned a group called `player`:

```C++
PlayerEntity* playerEntity = new PlayerEntity(
    universe->assetsManager->getTextureSheet("tileset")->getTexture(),
    universe->assetsManager->getTextureSheet("tileset")->getTextureRect(260),
    sf::Vector2f(200, 100),
    {"player"}, // == collisionShapes["global_bounds"]->collisionGroups = {"tiles"};
    universe->assetsManager->getTextureSheet("tileset")
);
```

Then, based on these groups, `CollisionInteraction`s are registered:

```C++
universe->collisionManager->registerComponent(new AABBInteraction({"player"}, {"tiles"}));
universe->collisionManager->registerComponent(new PlayerSurfaceInteraction({"player"}, {"tiles"}));
universe->collisionManager->registerComponent(new CollisionHighlightInteraction({"player"}, {"tiles"}, mapTileDebugEntities));
```

The `CollisionShape`s that belong to the groups in the first vector (`{"player"}`) are called **initiators**,

The `CollisionShape`s that belong to the groups in the second vector (`{"tiles"}`) are called **recipients** of the collision.

<br>

### Let's look at how to create a `CollisionInteraction`

![Collision highlight example](../../notes/gifs/CollisionPhaseExample.gif)

In the gif above you can see collision shapes in "tiles" group highlighted in blue and "player" group collision shape highlighted in red. When "tiles" collide with "player" their border changes color.

<br>
<br>

To create a `CollisionInteraction` you should:

- Inherit the `sge::CollisionInteraction` class
- Override it's constructor
- Override it's algorithm function:
```C++
bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient) override{
    // if collision return true
    // else return false
}
```
- Override one or more of collision phase response functions:
```C++
void startPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
    // your code
}
void continuousPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
    // your code
}
void endPhaseCollisionResponse(std::vector<sge::Collision> collisions) override{
    // your code
}
```

SGE defines a couple of default `CollisionDetectionAlgorithms` and `CollisionResponses` that you can use in your programs. (see `SGE.hpp` or `/src/Logic/Collision/...`)