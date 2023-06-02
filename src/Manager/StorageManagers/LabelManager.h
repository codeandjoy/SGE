#ifndef LABEL_MANAGER_H
#define LABEL_MANAGER_H

#include <string>
#include <unordered_map>


namespace sge{
    template<typename T>
    class LabelManager{
        public:
            void registerComponent(std::string label, T component){ m_components[label] = component; }
            void deregisterComponent(std::string label){ m_components.erase(label); }
            T getComponent(std::string label){ return m_components[label]; }
            std::unordered_map<std::string, T> getComponentsMap(){ return m_components; }

        protected:
            std::unordered_map<std::string, T> m_components;
    };
}


#endif