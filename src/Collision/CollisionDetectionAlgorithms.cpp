#include "CollisionDetectionAlgorithms.h"
#include "CollisionShape.h"


bool boundingBox(CollisionShape* initiator, CollisionShape* recipient){
    return initiator->getGlobalBounds().intersects(recipient->getGlobalBounds());
}