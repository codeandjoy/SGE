#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "PhysicalObject.h"


class PhysicsManager{
    public:
        void addPhysicalObject(PhysicalObject* _physicalObject);
        void removePhysicalObject(PhysicalObject* _physicalObject);

        void updatePhysics(float dt);

    private:
        std::vector<PhysicalObject*> physicalObjects;
};


#endif