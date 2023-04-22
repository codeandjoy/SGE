#ifndef COLLISION_H
#define COLLISION_H

enum CollisionSide : int;
class CollisionShape;


struct Collision{
    CollisionShape *initiator;
    CollisionShape *recipient;
    CollisionSide initiatorImpactSide;
    CollisionSide recipientImpactSide;

    friend bool operator< (const Collision a, const Collision b);
    friend bool operator> (const Collision a, const Collision b);
    friend bool operator== (const Collision a, const Collision b);
    friend bool operator!= (const Collision a, const Collision b);
};


#endif