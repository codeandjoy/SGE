# StateCluster

- Defines a set of `Entity`'s possible and currently active states.

`StateCluster` is written in a way that multiple states can be active at the same time.

When certain `State` is active it's `updateScript` gets continuously executed in the engine loop.

<br>

# State

- Defines a specific state of the `Entity`.

`enterScript` - is executed the moment state becomes active.

`exitScript` - is executed the moment state becomes inactive.

`updateScript` - is executed while state is active.

To create a custom state, you should define a class that inherits the `State` class and overrides one or all of the three functions specified above.

<br>

# StateManager

`StateManager` is a `VectorManager` and `UpdateManager`.

It is used by `EntityManager` to manage `Entity`'s given `StateCluster`.