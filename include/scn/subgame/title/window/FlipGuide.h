#ifndef SCN_SUBGAME_TITLE_WINDOW_FLIPGUIDE_H
#define SCN_SUBGAME_TITLE_WINDOW_FLIPGUIDE_H

#include "lyt/Layout.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace title {
namespace window {

class FlipGuide {
public:
    enum Kind {
        KIND_0,
    };

    FlipGuide(Kind kind, lyt::Layout& layout);
    ~FlipGuide();

    void start();
    void enter();
    void updateMain();
    void updateDebug();
    bool isEnd() const;

private:
    u32 _0[0x25F];
};

}
}
}
}

#endif
