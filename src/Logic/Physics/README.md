# MotionUnit

- Defines `Entity`'s physical attributes and computations.

By default `MotionUnit` defines `velocity` and `acceleration` and has the `extraProperties` map that can be used to keep track of extra variables.

`MotionUnit` also defines the map of `contactForces` and `fieldForces` which can be used to keep track of forces that impact given object.

All mentioned above can be used in "computation scripts" to code physical interaction like kinetic friction.

Computation scripts get executed every engine loop iteration **in order of insertion**.

<br>

# MotionUnitManager

`MotionUnitManager` is a `VectorManager` and `UpdateManager`.

It is used by the `EntityManager` to manager `Entity`'s given `MotionUnit`.