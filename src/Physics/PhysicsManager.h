#ifndef PHYSICS_MANAGER_H
#define PHYSICS_MANAGER_H

#include <vector>


namespace sge{
    class PhysicalObject;

    class PhysicsManager{
        public:
            void registerPhysicalObject(sge::PhysicalObject* physicalObject);
            void deregisterPhysicalObject(sge::PhysicalObject* physicalObject);
            std::vector<sge::PhysicalObject*> getAllPhysicalObjects();


            void updatePhysics(float dt);

        private:
            std::vector<sge::PhysicalObject*> m_physicalObjects;
    };
}


#endif