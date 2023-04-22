#ifndef COLLISION_RESPONSES_H
#define COLLISION_RESPONSES_H

#include <vector>
struct Collision;


void resolveAABB(std::vector<Collision> collisions);

void initiatorStandOnTopOfRecipient(std::vector<Collision> collisions);


#endif