#include "LayerSceneManager.h"
#include "SceneManager.h"


void sge::LayerSceneManager::registerComponent(std::string label, sge::Scene* scene){
    sge::SceneManager::registerComponent(label, scene);
    m_registerSceneMembers(label);
}
void sge::LayerSceneManager::deregisterComponent(std::string label){
    m_deregisterSceneMembers(label);
    sge::SceneManager::deregisterComponent(label);
}