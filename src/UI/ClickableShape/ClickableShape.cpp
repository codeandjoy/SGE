#include "ClickableShape.h"
#include "../UIEntity/UIEntity.h"


sge::ClickableShape::ClickableShape(sge::UIEntity* ownerUIEntity){ m_ownerUIEntityPtr = ownerUIEntity; }

sge::UIEntity* sge::ClickableShape::getOwnerUIEntity(){ return m_ownerUIEntityPtr; }
void sge::ClickableShape::align(){ this->setPosition(m_ownerUIEntityPtr->sprite->getPosition() + offset); }