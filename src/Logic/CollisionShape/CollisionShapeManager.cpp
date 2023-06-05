#include <algorithm>
#include "CollisionShapeManager.h"
#include "CollisionShape.h"


std::vector<sge::CollisionShape*> sge::CollisionShapeManager::getComponentsByCollisionGroup(std::string groupName){
    std::vector<sge::CollisionShape*> collisionGroupMembers;
    for(sge::CollisionShape* collisionShape : m_components){
        // if CollisionShape is a member of 'groupName' collision group
        if(std::find(collisionShape->collisionGroups.begin(), collisionShape->collisionGroups.end(), groupName) != collisionShape->collisionGroups.end()){
            collisionGroupMembers.push_back(collisionShape);
        }
    }

    return collisionGroupMembers;
}


void sge::CollisionShapeManager::update(float dt){
    for(sge::CollisionShape* collisionShape : m_components){
        if(collisionShape->isActive) collisionShape->align();
    }
}