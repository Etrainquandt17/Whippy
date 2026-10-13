#ifndef SCN_ARENA_MENUMAIN_H
#define SCN_ARENA_MENUMAIN_H

#include "types.h"

namespace sfx {
class Fade;
}

namespace scn {
namespace arena {

class ArenaData;
class Component;

class MenuMain {
public:
    MenuMain(Component& component);

    virtual ~MenuMain();
    virtual void updateUseGPU();
    virtual void updateMain();
    virtual void updateDebug();
    virtual void draw();
    virtual bool isEnd() const;
    virtual bool isCanPause() const;

    Component& comp();
    sfx::Fade& fade();
    ArenaData& data();
    // TODO: an enum of the title's two choices, most likely.
    int& crsr();

private:
    Component& mComponent;
};

}
}

#endif
