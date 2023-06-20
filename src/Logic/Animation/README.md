# AnimationCluster

- Defines `Entity`'s texture animations.

`AnimationCluster` is a container component that stores a set of defined `TextureSequences`.

`AnimationCluster` iteratively sets it's owner's `Sprite` texture to the next one in the current `TextureSequence` through the defined animation delay.

<br>

# TextureSequence

- Defines a sequence of [sf::IntRect](https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Rect.php)s that represent certain animation.

<br>

# AnimationManager

`AnimationManager` is a `VectorManager` and `UpdateManager`.

It is used by the `EntityManager` to register `Entity`'s given `AnimationCluster`.