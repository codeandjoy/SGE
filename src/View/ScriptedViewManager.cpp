#include "ScriptedViewManager.h"
#include "ScriptedView.h"


void sge::ScriptedViewManager::update(float dt){
    for(sge::ScriptedView* scriptedView : m_components){
        scriptedView->script();
    }
}