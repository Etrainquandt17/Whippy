#ifndef SCN_ARENA_TITLE_TITLE_H
#define SCN_ARENA_TITLE_TITLE_H

#include "info/common/ButtonHelp.h"
#include "info/sequence/Sequence.h"
#include "lyt/Layout.h"
#include "mem/AutoHeapExp.h"
#include "scn/arena/MenuMain.h"
#include "scn/arena/RenderSet.h"
#include "scn/arena/bg/Bg.h"
#include "scn/step/core/BGMController.h"
#include "snd/SERequestor.h"
#include "types.h"

namespace scn {
namespace arena {
namespace title {

class Title : public MenuMain {
public:
    Title(Component& component);

    virtual ~Title();
    virtual void updateUseGPU();
    virtual void updateMain();
    virtual void updateDebug();
    virtual void draw();
    virtual bool isEnd() const;
    virtual bool isCanPause() const;

    void fadeInStart();
    void decideFadeOutStart();
    void cancelFadeOutStart();
    void preLoad();

private:
    RenderSet mRenderSet;
    mem::AutoHeapExp mHeap;
    snd::SERequestor mSE;
    step::core::BGMController mBGM;
    u32 _3A0;
    lyt::Layout mLayout;
    lyt::Layout mButtonLayout;
    info::common::ButtonHelp mButtonHelp;
    bg::Bg mBg;
    info::sequence::Sequence mSequence;
    u32 _F98;
    u32 _F9C;
    bool _FA0;
};

}
}
}

#endif
