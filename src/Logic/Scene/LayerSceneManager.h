#ifndef LAYER_SCENE_MANAGER_H
#define LAYER_SCENE_MANAGER_H

#include <string>

#include "SceneManager.h"


namespace sge{
    class Scene;

    class LayerSceneManager : public sge::SceneManager{
        public:
            LayerSceneManager(sge::EntityManager* entityManager, sge::CollisionManager* collisionManager)
                : sge::SceneManager(entityManager, collisionManager){};

            void registerComponent(std::string label, sge::Scene* scene);
            void deregisterComponent(std::string label);
        
        private:
            // Hidden because extended
            using sge::SceneManager::registerComponent;
            using sge::SceneManager::deregisterComponent;
            //
    };
}



#endif