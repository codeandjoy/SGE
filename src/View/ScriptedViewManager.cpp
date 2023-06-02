#include "ScriptedViewManager.h"
#include "ScriptedView.h"


void sge::ScriptedViewManager::update(float dt){
    for(sge::ScriptedView* scriptedView : m_components){
        if(scriptedView->script){
            scriptedView->script(scriptedView);
        }
    }
}