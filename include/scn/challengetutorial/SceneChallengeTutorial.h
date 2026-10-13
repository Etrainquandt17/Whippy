#ifndef SCN_CHALLENGETUTORIAL_SCENECHALLENGETUTORIAL_H
#define SCN_CHALLENGETUTORIAL_SCENECHALLENGETUTORIAL_H

#include "g3d/Root.h"
#include "scn/IScene.h"
#include "scn/challengetutorial/DialogKind.h"
#include "scn/challengetutorial/info/Manager.h"
#include "scn/step/ChallengeKind.h"
#include "scn/step/challenge/Score.h"
#include "sfx/Fade.h"
#include "snd/SERequestor.h"
#include "std/new.h"
#include "types.h"
#include "util/FrameCounter.h"
#include "util/PlacementNew.h"

// TODO: util/PlacementNew.h has no construct() and no access to the object yet.
// Until it does, it is specialized here.
namespace util {

template <>
class PlacementNew<scn::challengetutorial::info::Manager> {
public:
    PlacementNew() : mObj(0) {}
    ~PlacementNew();

    void destruct();
    void construct(bool isExtraMode) {
        destruct();
        mObj = new (mBuffer) scn::challengetutorial::info::Manager(isExtraMode);
    }
    scn::challengetutorial::info::Manager* operator->() const { return mObj; }

private:
    scn::challengetutorial::info::Manager* mObj;
    u32 mBuffer[sizeof(scn::challengetutorial::info::Manager) / sizeof(u32)];
};

}

// TODO: the constructor of sfx::Fade. sfx/Fade.h gives the class 0x140 bytes where it has 0x24,
// so the scene cannot hold one as a member yet and builds it through this.
extern "C" void __ct__Q23sfx4FadeFv(void* fade);

namespace scn {
namespace challengetutorial {

class SceneChallengeTutorial : public IScene {
public:
    class Recipe {
    public:
        static Recipe Create(step::ChallengeKind kind, bool isExtraMode, bool, DialogKind dialog);

        step::ChallengeKind mKind;
        bool mIsExtraMode;
        bool _5;
        DialogKind mDialog;
    };

    struct Result {
        bool _0;
    };

    SceneChallengeTutorial(const Recipe& recipe);

    Result result();

    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~SceneChallengeTutorial();
    virtual void updateMain();
    virtual void updateUseGPU();
    virtual void updateDebug();
    virtual void draw(const DrawReqInfo& info);
    virtual bool isSceneEnd() const;

private:
    class Fade {
    public:
        Fade() { __ct__Q23sfx4FadeFv(this); }

        sfx::Fade* operator->() { return (sfx::Fade*)this; }

    private:
        u32 _0[9];
    };

    Recipe mRecipe;
    g3d::Root mRoot;
    int mState;
    step::ChallengeKind mKind;
    u32 _68;
    step::challenge::Score mScore;
    u32 _F0;
    util::PlacementNew<info::Manager> mInfo;
    util::FrameCounter mCounter;
    Fade mFade;
    snd::SERequestor mSE;
    bool _1C78;
};

}}  // namespace scn::challengetutorial

#endif
