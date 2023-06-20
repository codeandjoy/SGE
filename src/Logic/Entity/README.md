# Entity

- Key engine component that defines any object on the screen.

The key idea is that `Entity` is **built** using the specific set of possible *parts* based on the desired functionality of the object.

Possible parts include: `sge::Sprite`, `MotionUnit`, one or more `CollisionShape`, `ClicableShape`, `SpriteText`, `AnimationCluster` and `StateCluster`.

`Entity` must contain `sge::Sprite` (whether with or without texture).

For example the player's `Entity` object may consist of `Sprite`, `MotionUnit`, `CollisionShape`, `AnimationCluster` and possibly the `StateCluster`.

While the button's `Entity` object may be built just with `Sprite` and `ClickableShape`.

This way of "building" the `Entity` object allows high level of flexibility while keeping the engine structure simple and easy to understand.

<br>

# EntityManager

- Manages `Entity` objects in a specific way.

`EntityManager` is a `ViewManager`.

When `Entity` is registered or deregistered, the manager recursively performs registration or deregistration of all `Entity`'s specified parts using corresponding managers. (For example on 'button' object registration the `Sprite` and `ClickableShape` objects will be registered in the engine loop and button's `Entity` object pointer will be saved in `EntityManager`).

