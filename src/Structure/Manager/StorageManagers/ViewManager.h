#ifndef VIEW_MANAGER_H
#define VIEW_MANAGER_H

#include <SFML/Graphics.hpp>
#include <algorithm>
#include <unordered_map>
#include <vector>

namespace sge{
    template<typename T>
    class ViewManager{
        public:
            void registerComponent(sf::View* view, T component){ m_components[view].push_back(component); }
            void deregisterComponent(sf::View* view, T component){ m_components[view].erase(std::remove(m_components[view].begin(), m_components[view].end(), component), m_components[view].end()); }
            std::vector<T> getViewComponents(sf::View* view){ return m_components[view]; }
            std::unordered_map<sf::View*, std::vector<T>> getComponentsUnorderedMap(){ return m_components; }

        protected:
            std::unordered_map<sf::View*, std::vector<T>> m_components;
    };
}



#endif