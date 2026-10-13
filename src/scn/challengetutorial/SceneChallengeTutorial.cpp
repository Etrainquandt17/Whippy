#include "scn/challengetutorial/SceneChallengeTutorial.h"

#include "app/Application.h"
#include "app/HIDErrorMenu.h"
#include "file/Utility.h"
#include "g3d/CameraAccessor.h"
#include "g3d/RootContext.h"
#include "hel/common/ArrayUtil.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/FixedString.h"
#include "hel/common/MutableArray.h"
#include "hel/common/RuntimeTypeInfo.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "metafortress.h"
#include "scn/step/ChallengeKindUtil.h"
#include "snd/BgmPlayer.h"
#include "snd/SoundManager.h"

// TODO: hel/common/RuntimeTypeInfo.h does not define this yet; the unit holds its own copy.
namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<scn::challengetutorial::SceneChallengeTutorial>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<scn::IScene>(), RuntimeTypeInfo::NoName());
    return ti;
}

}}  // namespace hel::common

namespace scn {
namespace challengetutorial {

#define MF_FUNCTION Create__Q43scn17challengetutorial22SceneChallengeTutorial6RecipeFQ33scn4step13ChallengeKindbbQ33scn17challengetutorial10DialogKind
SceneChallengeTutorial::Recipe SceneChallengeTutorial::Recipe::Create(step::ChallengeKind kind, bool isExtraMode, bool flag,
                                                                      DialogKind dialog) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    u32 hash;
    Recipe recipe = {};

    hash = 0x811C9E07;
    recipe.mKind = kind;
    asm {
        bl      after1
        opword  0x8890EC93
        opword  0x58066192
        opword  MF_WORD(0x50)
    after1:
        mflr    r27
        lwz     r24, 0x8(r27)
        stw     r24, start
        bl      after2
        opword  0x4CE8C680
        opword  0x70B21580
        opword  MF_WORD(0x6C)
        opword  0x1621F70C
        opword  0x38199680
    after2:
        mflr    r27
        lwz     r24, 0x8(r27)
        stw     r24, end
    }
    recipe.mIsExtraMode = isExtraMode;
    {
        u32 word;
        u32 last;

        last = end;
        word = start;
        word -= 2;
        for (;;) {
            word += 2;
            if (word == last) {
                break;
            }
            hash ^= *(u16*)word;
            hash *= 0x010001A7;
        }
    }
    recipe._5 = flag;
    hash ^= hash >> 10;
    asm {
        bl      after3
        opword  MF_WORD(0xC8)
        opword  0x275A4C9C
    after3:
        mflr    r15
        lwz     r14, 0x0(r15)
        stw     r14, expected
    }
    recipe.mDialog = dialog;
    hash ^= hash << 20;
    if (hash == expected) {
        goto intact;
    }
    asm {
        bl      after4
        opword  MF_WORD(0xF8)
    after4:
        mflr    r27
        lwz     r26, 0x0(r27)
        stw     r26, -0x4(r1)
        stw     r27, 0x0(r1)
        stw     r26, -0x4(r1)
        stw     r27, -0x8(r1)
        mtlr    r26
        bl      after5
        opword  MF_WORD(0x11C)
        opword  0x98C25180
        opword  MF_WORD(0x124)
    after5:
        mflr    r27
        lwz     r28, 0x0(r27)
        stw     r27, base
        lwz     r17, 0x8(r27)
        stw     r28, offset
        stw     r17, key
    }
    offset = offset + 0x87;
    key = 0;
    response = offset;
    response = response + base;
    asm {
        lwz     r21, response
        mtlr    r21
        blr
    }
    goto done;
intact:
    return recipe;
done:;
}
#undef MF_FUNCTION

#define MF_FUNCTION __ct__Q33scn17challengetutorial22SceneChallengeTutorialFRCQ43scn17challengetutorial22SceneChallengeTutorial6Recipe
SceneChallengeTutorial::SceneChallengeTutorial(const Recipe& recipe)
    : mRecipe(recipe)
    , mRoot(g3d::RootContext(g3d::RootContext::DefaultAllocator(), g3d::RootContext::DefaultMaxNumChildren(),
                             g3d::RootContext::DefaultMaxNumScnObj(), g3d::RootContext::DefaultNumLightObj(),
                             g3d::RootContext::DefaultNumLightSet()))
    , mState(0)
    , mKind(recipe.mKind)
    , mScore()
    , mInfo()
    , mCounter()
    , mFade()
    , mSE() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 limit;
    u32 hash;
    u32 base;

    {
        hel::common::MutableArray<hel::common::FixedString<64>, 24> paths;
        paths.add(step::ChallengeKindUtil::TutorialDNPath(recipe.mKind));
        hash = 0xBF;
        file::Utility::DNProcess(paths, true);
        file::Utility::SetIsFileLoadWarningEnable(true);
    }
    asm {
        bl      after1
        opword  MF_WORD(0x18C)
        opword  0x640D9804
        opword  0xB443B993
        opword  MF_WORD(0x198)
        opword  0x48D30C80
    after1:
        mflr    r14
        lwz     r23, 0x0(r14)
        lwz     r29, 0xc(r14)
        add     r23, r23, r14
        add     r29, r29, r23
        stw     r23, start
        stw     r29, end
    }
    hel::common::ExplicitSingleton<app::Application>::object_->hidErrorMenu().setup(app::HIDErrorMenu::DISCONNECT_MENU_MODE_0);
    mInfo.construct(recipe.mIsExtraMode);
    limit = end - start + 1;
    i = 1;
    base = end;
    mState = 0;
    hel::common::ExplicitSingleton<snd::SoundManager>::object_->bgm().stop();
    asm {
        bl      after2
        opword  MF_WORD(0x220)
        opword  0x7FC40EB1
    after2:
        mflr    r24
        lwz     r25, 0x0(r24)
        stw     r25, expected
    }
    info::Tutorial::Recipe tutorialRecipe = {};
    tutorialRecipe.mKind = mKind;
    tutorialRecipe._4 = recipe._5;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base - 1 - i);
        i += 2;
    }
    tutorialRecipe.mDialog = recipe.mDialog;
    mInfo->tutorial().appear(tutorialRecipe);
    GXColor color = {0, 0, 0, 255};
    mFade->setColor(color);
    hash += hash << 3;
    mFade->setFadeIn(25);
    mFade->update();
    hash ^= hash >> 11;
    mRoot.currentCamera().setViewMtx(hel::math::Matrix34::CreateLookAt(
        hel::math::Vector3(0.0f, 0.0f, 40.0f), hel::math::Vector3::BASIS_Y, hel::math::Vector3::BASIS_Z * -1.0f));
    mRoot.currentCamera().setProjPerspective(60.0f, 16.0f / 9.0f, 0.1f, 1000.0f);
    hash += hash << 15;
    if (hash - expected == 0 && !mRecipe._5) {
        hel::common::ExplicitSingleton<snd::SoundManager>::object_->bgm().start(0x3F);
    } else {
        hel::common::ExplicitSingleton<snd::SoundManager>::object_->bgm().start(0x5A);
    }
}
#undef MF_FUNCTION

}}  // namespace scn::challengetutorial

namespace util {

void PlacementNew<scn::challengetutorial::info::Manager>::destruct() {
    if (mObj != 0) {
        mObj->~Manager();
        mObj = 0;
    }
}

PlacementNew<scn::challengetutorial::info::Manager>::~PlacementNew() {
    destruct();
}

}

namespace scn {
namespace challengetutorial {

SceneChallengeTutorial::~SceneChallengeTutorial() {
}

SceneChallengeTutorial::Result SceneChallengeTutorial::result() {
    Result result;
    result._0 = _1C78;
    return result;
}

void SceneChallengeTutorial::updateUseGPU() {
}

void SceneChallengeTutorial::updateMain() {
    mCounter.advanceIfNotEnd();
    mFade->update();
    switch (mState) {
    case 0:
        if (mInfo->tutorial().isAnimEnd()) {
            _1C78 = mInfo->tutorial()._1874;
            if (!mRecipe._5 || _1C78) {
                mState = 3;
            } else {
                GXColor color = {0, 0, 0, 255};
                mFade->setColor(color);
                mFade->setFadeOut(25);
                mCounter.reset(25);
                mState = 1;
            }
        }
        break;
    case 1:
        if (mCounter.isEnd()) {
            mState = 2;
        }
        break;
    case 2:
        mState = 3;
        break;
    }
    mInfo->procAnim();
    mInfo->procReadyToRender();
}

void SceneChallengeTutorial::updateDebug() {
}

void SceneChallengeTutorial::draw(const DrawReqInfo&) {
    mInfo->draw();
    mFade->draw();
}

bool SceneChallengeTutorial::isSceneEnd() const {
    return mState == 3;
}

const hel::common::RuntimeTypeInfo& SceneChallengeTutorial::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<SceneChallengeTutorial>();
}

}}  // namespace scn::challengetutorial
