#ifndef COLLISION_UTILS_H
#define COLLISION_UTILS_H

class CollisionShape;
enum CollisionSide : int;


float determineCollisionDepth(CollisionSide initiatorImpactSide, CollisionShape *initiator, CollisionShape *recipient);

CollisionSide determineInitiatorImpactSide(CollisionShape *initiator, CollisionShape *recipient);

CollisionSide flipInitiatorImpactSide(CollisionSide initiatorImpactSide);


#endif