# CollisionShape

- Defines a [sf::RectangleShape](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RectangleShape.php) of the `Entity` for collision processing.

`CollisionShape` defines the `collisionGroups` vector based on which the collision processing is performed.

<br>

# CollisionShapeManager

`CollisionShapeManager` is used by the `EntityManager` to manager `Entity`'s `CollisionShapes`.

`CollisionShapeManager` can filter and return `CollisionShapes` based on their collision groups.