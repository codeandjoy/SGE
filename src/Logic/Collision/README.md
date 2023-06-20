# Collision detection functionality

## CollisionInteraction

The engine defines the concept of `CollisionInteraction`.

Collisions can happen between the `initiator` and the `recipient` collision shapes. The vectors of `initiatorGroups` and `recipientGroups` is defined in the `CollisionInteraction` object.

Collisions are detected using the specified `collisionDetectionAlgorithm`.

Based on the collision phase of the objects the appropriate response is executed (`startPhaseCollisionResponse`, `continuousPhaseCollisionResponse` or `endPhaseCollisionResponse`).

<br>

## CollisionManager

- Processes regsitered collision interactions.

Collision detection algorithm iterates in the following way:

```py
for each initiator:
    for all recipients:
        check collision:
            if collision:
                determine collision phase
                run appropriate response
            else continue
```

**Each individual initiator gets tested for collision against all recipients**

<br>

## Collision

- Structure that defines the specific collsion information