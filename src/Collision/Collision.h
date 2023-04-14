#ifndef COLLISION_H
#define COLLISION_H

#include "CollisionSide.h"
#include "CollisionShape.h"


struct Collision{
    CollisionShape *initiator;
    CollisionShape *recipient;
    CollisionSide initiatorImpactSide;
    CollisionSide recipientImpactSide;

    friend bool operator< (const Collision a, const Collision b){ return a.initiator < b.initiator; }
    friend bool operator> (const Collision a, const Collision b){ return a.initiator > b.initiator; }
    friend bool operator== (const Collision a, const Collision b){ return a.initiator == b.initiator; }
    friend bool operator!= (const Collision a, const Collision b){ return a.initiator != b.initiator; }
};


#endif