#include "DrumSceneManager.h"
#include "Scene.h"
#include "../Entity/EntityManager.h"
#include "../Collision/CollisionManager.h"
#include "../../Debug/DebugManager/DebugManager.h"


void sge::DrumSceneManager::setCurrentScene(std::string name){ m_currentScene = name; }

void sge::DrumSceneManager::alignScene(){
    if(m_currentScene.length()){
        if(m_loadedScene != m_currentScene){
            m_deregisterSceneMembers(m_loadedScene);

            m_registerSceneMembers(m_currentScene);

            m_loadedScene = m_currentScene;
        }
    }
}