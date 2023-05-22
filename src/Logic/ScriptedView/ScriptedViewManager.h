#ifndef SCRIPTED_VIEW_MANAGER_H
#define SCRIPTED_VIEW_MANAGER_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


namespace sge{
    struct ScriptedView;

    class ScriptedViewManager{
        public:
            void registerScriptedView(sge::ScriptedView* scriptedView);

            void runViewScripts();

        private:
            std::vector<sge::ScriptedView*> m_scriptedViews;
    };
}


#endif