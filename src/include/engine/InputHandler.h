//
// Created by squid on 5/16/24.
//

#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H
#include <functional>
#include <map>
#include <SDL.h>
#include <string>
#include <sstream>
#include <vector>


namespace hyperion::engine::services {
    typedef std::function<void(SDL_Keycode, std::string keystroke)> InputCallback;

    class InputHandler {
    private:
        std::map<SDL_Keycode, std::vector<InputCallback> > keys;

    public:
        void subscribeKeystroke(std::string keystroke, InputCallback callback);
    };
}


#endif //INPUTHANDLER_H
