#include <algorithm>
#include "CollisionShapeManager.h"
#include "CollisionShape.h"


void sge::CollisionShapeManager::registerCollisionShape(sge::CollisionShape* collisionShape){ m_collisionShapes.push_back(collisionShape); }
void sge::CollisionShapeManager::deregisterCollisionShape(sge::CollisionShape* collisionShape){ m_collisionShapes.erase(std::remove(m_collisionShapes.begin(), m_collisionShapes.end(), collisionShape), m_collisionShapes.end()); }
void sge::CollisionShapeManager::registerCollisionShapes(std::vector<sge::CollisionShape*> collisionShapes){ m_collisionShapes.insert(m_collisionShapes.end(), collisionShapes.begin(), collisionShapes.end()); }
void sge::CollisionShapeManager::deregisterAllCollisionShapes(){ m_collisionShapes.clear(); }



std::vector<sge::CollisionShape*> sge::CollisionShapeManager::getCollisionShapes(){ return m_collisionShapes; }



void sge::CollisionShapeManager::alignCollisionShapes(){
    for(sge::CollisionShape* collisionShape : m_collisionShapes){
        collisionShape->align();
    }
}