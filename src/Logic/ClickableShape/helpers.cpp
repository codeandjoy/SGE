#include "helpers.h"

#include "ClickableShape.h"
#include "../../Logic/Entity/Entity.h"


bool sge::isMouseOverClickableShape(ClickableShape* clickableShape, sf::RenderWindow* window){
    return clickableShape->getOwnerEntity()->sprite->getGlobalBounds().contains(window->mapPixelToCoords(sf::Mouse::getPosition(*window)));
}