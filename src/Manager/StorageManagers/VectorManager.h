#ifndef VECTOR_MANAGER_H
#define VECTOR_MANAGER_H

#include <algorithm>
#include <vector>


namespace sge{
    template<typename T>
    class VectorManager{
        public:
            void registerComponent(T component){ m_components.push_back(component); }
            void deregisterComponent(T component){ m_components.erase(std::remove(m_components.begin(), m_components.end(), component), m_components.end()); }
            std::vector<T> getComponents(){ return m_components; };
        
        protected:
            std::vector<T> m_components;
    };
}



#endif