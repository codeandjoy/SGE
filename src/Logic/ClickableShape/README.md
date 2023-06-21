# ClickableShape

- Defines a [sf::RectangleShape](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RectangleShape.php) of the `Entity` for mouse click processing.

`ClickableShape` defines the `action(...)` function that will be executed each engine loop iteration and can be used to write click handling code.

### Usage examples:

Adding `ClickableShape` to `Entity`:

```C++
```

<br>

# ClickableShapeManager

`ClickableShapeManager` is a `ViewManager`, `UpdateManager` and `EventManager`.

It is used by `EntityManager` to manage `Entity`'s given `ClickableShape`.
