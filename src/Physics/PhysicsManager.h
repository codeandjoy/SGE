#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "PhysicalObject.h"


class PhysicsManager{
    public:
        void registerPhysicalObject(PhysicalObject* physicalObject);
        void deregisterPhysicalObject(PhysicalObject* physicalObject);
        std::vector<PhysicalObject*> getAllPhysicalObjects();


        void updatePhysics(float dt);

    private:
        std::vector<PhysicalObject*> m_physicalObjects;
};


#endif