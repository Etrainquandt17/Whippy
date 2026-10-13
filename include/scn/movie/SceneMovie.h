#ifndef SCN_MOVIE_SCENEMOVIE_H
#define SCN_MOVIE_SCENEMOVIE_H

#include "font/FontLoader.h"
#include "hel/common/ScopedPtr.h"
#include "info/common/SkipHelp.h"
#include "info/cutin/CutIn.h"
#include "mem/AutoHeapExp.h"
#include "mem/ExplicitScopedPtr.h"
#include "mem/SDKAllocator.h"
#include "mov/MovieKind.h"
#include "mov/MoviePlayer.h"
#include "revolution/gx/GXStruct.h"
#include "scn/IScene.h"
#include "scn/movie/LoadIcon.h"
#include "scn/movie/Subtitle.h"
#include "types.h"
#include "util/PlacementNew.h"

namespace scn {
namespace movie {

class SceneMovie : public IScene {
public:
    enum Mode {
        MODE_0,
    };

    enum UnlockMode {
        UNLOCK_MODE_0,
    };

    class Recipe {
    public:
        static Recipe Create(Mode mode, mov::MovieKind kind, const GXColor& preFade, const GXColor& postFade, bool,
                             UnlockMode unlockMode);

    private:
        u32 _0[6];
    };

    class Fade {
    public:
        Fade(const GXColor&, const GXColor&);

    private:
        u32 _0[6];
    };

    SceneMovie(const Recipe& recipe);

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneMovie();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    u32 _4;
    util::PlacementNew<mov::MoviePlayer> mPlayer;
    util::PlacementNew<mem::SDKAllocator> mAllocator;
    hel::common::ScopedPtr<mem::AutoHeapExp> _3E8;
    u32 _3EC;
    mov::MovieKind mKind;
    Fade mFade;
    u32 _40C[2];
    font::FontLoader mFontLoader;
    mem::ExplicitScopedPtr<info::cutin::CutIn> mCutIn;
    mem::AutoHeapExp mHeap;
    info::common::SkipHelp mSkipHelp;
    LoadIcon mLoadIcon;
    Subtitle mSubtitle;
};

}
}

#endif
