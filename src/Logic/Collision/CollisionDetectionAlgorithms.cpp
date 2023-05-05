#include "CollisionDetectionAlgorithms.h"
#include "CollisionShape.h"


bool sge::boundingBox(sge::CollisionShape* initiator, sge::CollisionShape* recipient){
    return initiator->getGlobalBounds().intersects(recipient->getGlobalBounds());
}