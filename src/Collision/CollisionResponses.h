#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include <vector>


namespace sge{
    struct Collision;
    
    void resolveAABB(std::vector<sge::Collision> collisions);

    void initiatorStandOnTopOfRecipient(std::vector<sge::Collision> collisions);
}


#endif