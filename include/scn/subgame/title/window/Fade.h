#ifndef SCN_SUBGAME_TITLE_WINDOW_FADE_H
#define SCN_SUBGAME_TITLE_WINDOW_FADE_H

#include "revolution/gx/GXStruct.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace title {
namespace window {

class Fade {
public:
    Fade();
    ~Fade();

    void draw() const;
    void setColor(const GXColor& color);

    void update();
    void setFadeIn(u32 frame);
    void setFadeOut(u32 frame);
    bool isEnd() const;

private:
    u32 _0[0xE];
};

}
}
}
}

#endif
