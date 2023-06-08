#ifndef DEBUG_SCREEN_MANAGER_H
#define DEBUG_SCREEN_MANAGER_H

#include <SFML/Graphics.hpp>
#include <unordered_map> 


namespace sge{
    struct DebugVariable;
    class Entity;
    class EntityManager;

    class DebugScreenManager{
        public:
            DebugScreenManager(sge::EntityManager* entityManager, sf::View* debugScreenView, sf::Font* debugScreenFont, int fontSize)
                : m_entityManagerPtr(entityManager), m_view(debugScreenView), m_font(debugScreenFont), m_fontSize(fontSize){};


            void addDebugVariable(sf::Vector2f position, sge::DebugVariable* debugVariable);
            std::unordered_map<sge::DebugVariable*, sge::Entity*> getDebugVariables();

            void updateDebugVariables();


        private:
            std::unordered_map<sge::DebugVariable*, sge::Entity*> m_debugVariables;

            sf::View* m_view;
            sf::Font* m_font;
            int m_fontSize;
            sge::EntityManager* m_entityManagerPtr;
    };
}



#endif
