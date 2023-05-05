#include "helpers.h"

#include "ClickableShape.h"
#include "../UIEntity/UIEntity.h"


bool sge::isMouseOverClickableShape(ClickableShape* clickableShape, sf::RenderWindow* window){
    return clickableShape->getOwnerUIEntity()->sprite->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
}