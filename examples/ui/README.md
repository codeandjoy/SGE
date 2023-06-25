# UI

- shows how to create UI elements in SGE.

<br>

## UI elements

As you already may know, everything in SGE is an `Entity`. That means to create UI elements you build `sge::Entity` in a certain way.

To do this you write a class that inherits `sge::Entity` and, in it's constructor, create and describe parts of the entity that you need.


### Text entity

To create an entity that draws text on the screen you do what's described above and add `Sprite` and `SpriteText` to the `Entity`:

```C++
class ClickCountEntity : public sge::Entity{
    public: 
        ClickCountEntity(sf::Font* font){
            sprite = new sge::Sprite();
            sprite->setPosition(484, 40);

            spriteText = new sge::SpriteText(sprite);
            spriteText->setFont(*font);
            spriteText->setString("0");
            spriteText->setFillColor(sf::Color::White);
            spriteText->setCharacterSize(100);
        }
};
```

Which can be used in the following way:

```C++
ClickCountEntity* clickCountEntity = new ClickCountEntity(universe->assetsManager->getFont("m5x7"));

...

clickCountEntity->spriteText->setString(std::to_string(clickCount)); // Update text
```

### Button entity

To create a clickable button entity you build `sge::Entity` with `sge::Sprite` and `sge::ClickableShape`:

```C++
class ClickButtonEntity : public sge::Entity{
    public:
        ClickButtonEntity(sf::Texture* texture, sf::IntRect textureRect){
            sprite = new sge::Sprite(); 
            sprite->setScale(2,2);
            sprite->setTexture(*texture);
            sprite->setTextureRect(textureRect);
            sprite->setPosition(468, 200);

            clickableShape = new sge::ClickableShape(this);
            // Action is setup outside, in main
        }
};
```

For convenience, if action function needs a lot of captures, you can define it directly in main:

```C++
ClickButtonEntity* clickButtonEntity = new ClickButtonEntity(
    universe->assetsManager->getTextureSheet("button")->getTexture(),
    universe->assetsManager->getTextureSheet("button")->getTextureRect(0)
);
// Action is setup outside because of captures
clickButtonEntity->clickableShape->action = [window, universe, &clickCount, clickCountEntity, otherUIScreenScene](sge::ClickableShape* thisClickableShape, sf::Event event){
    if(sge::isMouseOverClickableShape(thisClickableShape, window)){
        printf("Mouse over Button\n");
    }

    if(event.type == sf::Event::MouseButtonPressed){
        if(sge::isMouseOverClickableShape(thisClickableShape, window)){
            thisClickableShape->getOwnerEntity()->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(1));
        }
    }
    if(event.type == sf::Event::MouseButtonReleased){
        thisClickableShape->getOwnerEntity()->sprite->setTextureRect(universe->assetsManager->getTextureSheet("button")->getTextureRect(0));
        
        // Click count
        if(sge::isMouseOverClickableShape(thisClickableShape, window)){
            clickCount++;
            clickCountEntity->spriteText->setString(std::to_string(clickCount));
        }
        //

        // Toggle ui screen
        if(otherUIScreenScene->isActive){
            otherUIScreenScene->hideSceneParts();
        }
        else{
            otherUIScreenScene->activateSceneParts();
        }
        //
    }
};
```

As you can see, inside `action` you can use SGE's `isMouseOverClickableShape` and SFML's event types to write your click handling code.

<br>

## Screens

Sometimes the UI you are creating is a bit more complex and dynamic. `LayerSceneManager` allows you to create collections of ui `Entities` and manipulate (show, hide, add, delete) them together. (see `ui.cpp`)