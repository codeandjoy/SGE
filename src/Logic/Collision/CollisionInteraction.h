#ifndef COLLISION_INTERACTION_H
#define COLLISION_INTERACTION_H

#include <unordered_map>
#include <vector>
#include <string>


namespace sge{
    struct Collision;
    class CollisionShape;
    class CollisionManager;

    class CollisionInteraction{
        friend class CollisionManager;
        
        public:
            std::vector<std::string> initiatorGroups = {};
            std::vector<std::string> recipientGroups = {};

            virtual bool collisionDetectionAlgorithm(sge::CollisionShape* initiator, sge::CollisionShape* recipient){ return false; }

            virtual void startPhaseCollisionResponse(std::vector<sge::Collision> collisions){}
            virtual void continuousPhaseCollisionResponse(std::vector<sge::Collision> collisions){}
            virtual void endPhaseCollisionResponse(std::vector<sge::Collision> collisions){}

        protected:
            std::unordered_map<sge::CollisionShape*, std::vector<sge::Collision>> pastCollisions;
    };
}



#endif