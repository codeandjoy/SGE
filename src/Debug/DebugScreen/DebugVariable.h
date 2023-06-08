#ifndef DEBUG_VARIABLE_H
#define DEBUG_VARIABLE_H

#include <functional>
#include <string>


namespace sge{
    class DebugVariable{
        public:
            std::function<std::string()> valueUpdateScript = [](){ return ""; };
            std::string value = "";

        friend class sge::DebugScreenManager;
        protected:
            void update(){ value = valueUpdateScript(); };
    };
}



#endif