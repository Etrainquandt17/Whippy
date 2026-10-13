#ifndef GFX_XFBMANAGER_H
#define GFX_XFBMANAGER_H

#include "mem/DataBlock.h"

namespace gfx {

class VISetting;

class XFBManager {
public:
    XFBManager(const VISetting& setting);

    void* drawTargetXFB();
    void changeDrawTargetXFB();
    void* target1();
    void* target2();

private:
    mem::DataBlock mTarget1;
    mem::DataBlock mTarget2;
    bool mIsDrawTarget1;
};

}

#endif
