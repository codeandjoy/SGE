#ifndef DRUM_SCENE_MANAGER_H
#define DRUM_SCENE_MANAGER_H

#include "SceneManager.h"


namespace sge{
    class Scene;

    class DrumSceneManager : public sge::SceneManager{
        public:
            DrumSceneManager(sge::EntityManager* entityManager)
                : sge::SceneManager(entityManager){};


            void setCurrentScene(std::string name);
            void alignScene();

        private:
            std::string m_currentScene = "";
            std::string m_loadedScene = "";
    };
}



#endif