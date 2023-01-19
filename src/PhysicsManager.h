#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "PhysicalObject.h"


class PhysicsManager{
    public:
        void addPhysicalObject(PhysicalObject *physicalObject);
        void updatePhysics();

    private:
        std::vector<PhysicalObject*> physicalObjects;
};


#endif