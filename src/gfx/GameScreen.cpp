#include "gfx/GameScreen.h"

namespace gfx {

GameScreen::GameScreen()
    : mScreenType(SCREEN_TYPE_1) {}

u16 GameScreen::gameWidth() const {
    if (mScreenType == SCREEN_TYPE_0) {
        return 608;
    }
    return 832;
}

u16 GameScreen::gameHeight() const {
    return 456;
}

void GameScreen::setDefaultScreenType() {
    mScreenType = SCREEN_TYPE_1;
}

void GameScreen::setScreenType(ScreenType type) {
    mScreenType = type;
}

GameScreen::ScreenType GameScreen::getScreenType() const {
    return mScreenType;
}

}  // namespace gfx
