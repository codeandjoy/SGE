#include "ScriptedViewManager.h"
#include "ScriptedView.h"


void sge::ScriptedViewManager::registerScriptedView(sge::ScriptedView* scriptedView){ m_scriptedViews.push_back(scriptedView); }

void sge::ScriptedViewManager::runViewScripts(){
    for(sge::ScriptedView* scriptedView : m_scriptedViews){
        if(scriptedView->script){
            scriptedView->script(scriptedView);
        }
    }
}