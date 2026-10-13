#ifndef GFX_GAMESCREEN_H
#define GFX_GAMESCREEN_H

#include "types.h"

namespace gfx {

class GameScreen {
public:
    // TODO: name the values.
    enum ScreenType {
        SCREEN_TYPE_0,
        SCREEN_TYPE_1,
    };

    GameScreen();

    u16 gameWidth() const;
    u16 gameHeight() const;
    void setDefaultScreenType();
    void setScreenType(ScreenType type);
    ScreenType getScreenType() const;

private:
    ScreenType mScreenType;
};

}  // namespace gfx

#endif
