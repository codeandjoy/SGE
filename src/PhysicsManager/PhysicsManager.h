#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include "PhysicalObject.h"


class PhysicsManager{
    public:
        void addPhysicalObject(std::string _name, PhysicalObject* _physicalObject);
        void removePhysicalObject(std::string _name);

        void updatePhysics(float dt);

    private:
        std::map<std::string, PhysicalObject*> physicalObjects;
};


#endif