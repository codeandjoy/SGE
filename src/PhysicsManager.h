#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H


#include "PhysicalObject.h"
#include "SolidObject.h"

class PhysicsManager{
    public:
        void addPhysicalObject(PhysicalObject *physicalObject);
        void addSolidObject(SolidObject *solidObject);
        std::vector<SolidObject*>* getSolidObjects();
        void updatePhysics();

        bool drawCollideRects = false;

    private:
        std::vector<PhysicalObject*> physicalObjects;
        std::vector<SolidObject*> solidObjects;
};


#endif