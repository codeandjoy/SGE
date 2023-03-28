#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "PhysicalObject.h"


class PhysicsManager{
    public:
        void registerPhysicalObject(PhysicalObject* _physicalObject);
        void deregisterPhysicalObject(PhysicalObject* _physicalObject);
        std::vector<PhysicalObject*> getAllPhysicalObjects();

        void updatePhysics(float dt);

    private:
        std::vector<PhysicalObject*> physicalObjects;
};


#endif