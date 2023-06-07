#ifndef SCRIPTED_VIEW_H
#define SCRIPTED_VIEW_H

#include <functional>
#include <SFML/Graphics.hpp>


namespace sge{
    struct ScriptedView : public sf::View{
        virtual void script(){};
    };
}


#endif