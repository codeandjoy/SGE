# sge::Sprite

- Defines `Entity`'s texture and position.

`sge::Sprite` inherits all functionality from [sf::Sprite](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Sprite.php).

It is redefined to inherit the `StatefulComponent` functionality.

# SpriteManager

`SpriteManager` is a `ViewManager` and a `DrawManager`.

It is used by the `EntityManager` to register `Entity`'s given `sge::Sprite`.