#ifndef STATEFUL_COMPONENT_H
#define STATEFUL_COMPONENT_H


namespace sge{
    struct StatefulComponent{
        bool isActive = true;
        bool isPaused = false;
        bool isHidden = false;

        void activate(){
            isActive = true;
            isPaused = false;
            isHidden = false;
        }
        void pause(){
            isActive = false;
            isPaused = true;
            isHidden = false;
        }
        void hide(){
            isActive = false;
            isPaused = false;
            isHidden = true;
        }
    };
}



#endif