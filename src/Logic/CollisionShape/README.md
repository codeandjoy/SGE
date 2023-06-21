# CollisionShape

- Defines a [sf::RectangleShape](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RectangleShape.php) relative to the `Entity`'s `Sprite` for collision processing.

`CollisionShape` defines the `collisionGroups` vector based on which the collision processing is performed.

### Usage examples:

Adding `CollisionShape` to `Entity`:

```C++
class VoidEntity : public sge::Entity{
    public:
        VoidEntity(sf::Vector2f size, sf::Vector2f position, std::vector<std::string> collisionGroups){
            // Sprite is required
            sprite = new sge::Sprite();
            sprite->setPosition(position);
            //
            
            collisionShapes["global_bounds"] = new sge::CollisionShape(this);
            collisionShapes["global_bounds"]->setSize(size);
            collisionShapes["global_bounds"]->collisionGroups = collisionGroups;
        }
};
```

<br>

# CollisionShapeManager

`CollisionShapeManager` is used by the `EntityManager` to manager `Entity`'s `CollisionShapes`.

`CollisionShapeManager` can filter and return `CollisionShapes` based on their collision groups.