#ifndef UI_SCREEN_MANAGER_H
#define UI_SCREEN_MANAGER_H

#include <unordered_map>
#include <string>


namespace sge{
    class UIScreen;
    class UIEntityManager;

    class UIScreenManager{
        public:
            UIScreenManager(sge::UIEntityManager* uiEntityManager);

            void registerUIScreen(std::string name, sge::UIScreen* uiScreen);
            void deregisterUIScreen(std::string name);
            sge::UIScreen* getUIScreen(std::string name);

            void hideUIScreen(std::string name);
            void showUIScreen(std::string name);

        private:
            std::unordered_map<std::string, sge::UIScreen*> m_uiScreens;

            sge::UIEntityManager* m_uiEntityManagerPtr;
    };
}


#endif