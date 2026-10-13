#ifndef GFX_IDRAWER_H
#define GFX_IDRAWER_H

namespace gfx {

class IDrawer {
public:
    virtual ~IDrawer();
    virtual void drawerExecDraw() = 0;
};

}

#endif
