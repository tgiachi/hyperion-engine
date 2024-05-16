#ifndef MOUSE_POSITION_H
#define MOUSE_POSITION_H


namespace hyperion::engine {
    typedef struct {
        int x;
        int y;
        bool leftButton;
        bool rightButton;
        bool middleButton;
        int gridX;
        int gridY;
    } MousePosition;
}


#endif //MOUSE_POSITION_H
