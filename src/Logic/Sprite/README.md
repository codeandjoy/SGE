# sge::Sprite

- Defines `Entity`'s texture and position.

`sge::Sprite` inherits all functionality from [sf::Sprite](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Sprite.php).

It is redefined to inherit the `StatefulComponent` functionality.

### Usage examples:

Adding a `sge::Sprite` to `Entity`:

```C++
class PlainEntity : public sge::Entity{
    public:
        PlainEntity(sf::Texture* texture, sf::IntRect textureRect, sf::Vector2f position){
            sprite = new sge::Sprite(*texture, textureRect);
            sprite->setPosition(position);
        }
};
```

<br>

# SpriteManager

`SpriteManager` is a `ViewManager` and a `DrawManager`.

It is used by the `EntityManager` to register `Entity`'s given `sge::Sprite`.