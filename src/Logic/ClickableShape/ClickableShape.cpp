#include "ClickableShape.h"
#include "../../Logic/Entity/Entity.h"


sge::ClickableShape::ClickableShape(sge::Entity* ownerUIEntity){ m_ownerEntityPtr = ownerUIEntity; }

sge::Entity* sge::ClickableShape::getOwnerEntity(){ return m_ownerEntityPtr; }
void sge::ClickableShape::align(){ this->setPosition(m_ownerEntityPtr->sprite->getPosition() + offset); }