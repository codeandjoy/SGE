#include <algorithm>
#include "CollisionShapeManager.h"
#include "CollisionShape.h"


void sge::CollisionShapeManager::update(float dt){
    for(sge::CollisionShape* collisionShape : m_components){
        if(collisionShape->isActive) collisionShape->align();
    }
}