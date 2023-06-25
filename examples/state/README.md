# State

- Shows how to use state functionality in SGE

At the moment, SGE implements a multi state machine. That means that it's possible for multitude of states to be active at once. 

## Creating state

To create a state in SGE you should:

- Write a class that inherits `sge::State`:

```C++
class CustomState : public sge::State{
    public:
        CustomState(sge::Entity* entity) : sge::State(entity){};
    
    ...
};
```

- Override one or more of script functions:

```C++
void enterScript() override{
    // Code that's executed when state becomes active
}
void exitScript() override{
    // Code that's executed when state becomes inactive
}
void updateScript(float dt) override{
    // Code that's executed constantly when state is active
}
```

## Managing state

When all needed `sge::State`s are written for a particular `Entity`, you should combine then in a `StateCluster`:

```C++
WalkingLeft* walkingLeftEntityState = new WalkingLeft(entity);
WalkingRight* walkingRightEntityState = new WalkingRight(entity);

sge::StateCluster* entityStateCluster = new sge::StateCluster();
entityStateCluster->states["walking_right"] = walkingRightEntityState;
entityStateCluster->states["walking_left"] = walkingLeftEntityState;
```

And add the `StateCluster` to the `Entity` build:

```C++
entity->stateCluster = entityStateCluster;
```

After that, you can manage entity's states using it's `stateCluster` pointer:

```C++
...
entity->stateCluster->deactivateState("walking_right");
entity->stateCluster->activateState("walking_left");
...
```

<br>

A good example usecase of the state machine is also the `KeyboardController` written in `/examples/_common/KeyboardController.h`.