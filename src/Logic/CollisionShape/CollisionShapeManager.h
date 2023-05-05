#ifndef COLLISION_SHAPE_MANAGER_H
#define COLLISION_SHAPE_MANAGER_H

#include <vector>


namespace sge{
    class CollisionShape;

    class CollisionShapeManager{
        public:
            void registerCollisionShape(sge::CollisionShape* collisionShape);
            void deregisterCollisionShape(sge::CollisionShape* collisionShape);
            void registerCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes);
            void deregisterAllCollisionShapes();
            

            std::vector<sge::CollisionShape*> getCollisionShapes();
            
            
            void alignCollisionShapes();

        private:
            std::vector<CollisionShape*> m_collisionShapes;
    };
}


#endif