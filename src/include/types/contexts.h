#ifndef MOUSE_POSITION_H
#define MOUSE_POSITION_H


namespace hyperion::engine::contexts {
    typedef struct {
        int x;
        int y;
        bool leftButton;
        bool rightButton;
        bool middleButton;
        int gridX;
        int gridY;
    } MousePosition;

    typedef struct {
        int width;
        int height;
    } ScreenSize;

    typedef struct {
        int width;
        int height;
    } TilesSize;
}


#endif //MOUSE_POSITION_H
