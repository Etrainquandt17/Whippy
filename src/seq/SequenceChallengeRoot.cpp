#include "seq/SequenceChallengeRoot.h"

#include "app/Application.h"
#include "hel/common/ExplicitSingleton.h"
#include "hel/common/RuntimeTypeInfo.h"
#include "metafortress.h"
#include "revolution/ipc.h"
#include "scn/challengeresult/SceneChallengeResult.h"
#include "scn/challengetutorial/SceneChallengeTutorial.h"
#include "scn/step/ChallengeKindUtil.h"
#include "scn/step/Context.h"
#include "seq/SequenceStep.h"
#include "storage/BackupFileData.h"
#include "storage/StorageManager.h"
#include "storage/StoryData.h"

// TODO: hel/common/RuntimeTypeInfo.h does not define this yet; the unit holds its own copy.
namespace hel {
namespace common {

template <>
const RuntimeTypeInfo& RuntimeTypeInfoImpl<seq::SequenceChallengeRoot>() {
    static RuntimeTypeInfo ti(&RuntimeTypeInfoImpl<seq::ISequence>(), RuntimeTypeInfo::NoName());
    return ti;
}

}
}

namespace {

int t_AbilityTable[10] = {1, 35, 4, 12, 35, 15, 19, 0, 35, 13};

}

namespace seq {

namespace {

// TODO: scn::challengeresult::SceneChallengeResult does not derive from scn::IScene in its header yet, so
// hel::common::DynamicCastToRef cannot take it.
template <typename T>
inline T* t_sceneCast(scn::IScene* scene) {
    const hel::common::RuntimeTypeInfo& info = hel::common::RuntimeTypeInfoImpl<T>();
    if (scene != 0 && scene->GetRuntimeTypeInfo().isDerivedFrom(info)) {
        return reinterpret_cast<T*>(scene);
    }
    return 0;
}

template <typename T>
inline T& t_sceneCastToRef(scn::IScene* scene) {
    return *t_sceneCast<T>(scene);
}

}

#define MF_FUNCTION Create__Q33seq21SequenceChallengeRoot6RecipeFQ33scn4step13ChallengeKindQ33scn4step11ContextMode
SequenceChallengeRoot::Recipe SequenceChallengeRoot::Recipe::Create(scn::step::ChallengeKind kind, scn::step::ContextMode mode) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 addend;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    u32 i;
    u32 size;
    u32 first;
    u32 hash;

    Recipe recipe = {};
    asm {
        bl      after1
        opword  MF_WORD(0x4C)
        opword  MF_WORD(0x50)
    after1:
        mflr    r19
        lwz     r23, 0x4(r19)
        stw     r23, end
        lwz     r28, 0x0(r19)
        stw     r28, start
    }
    first = start;
    size = end - first;
    recipe.mKind = kind;
    asm {
        bl      after2
        opword  MF_WORD(0x7C)
        opword  0xADA3C09E
    after2:
        mflr    r15
        lwz     r23, 0x0(r15)
        stw     r23, expected
    }
    hash = 0x811C9E53;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x010001D1;
    }
    recipe.mMode = mode;
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if ((hash ^ expected) == 0) {
        return recipe;
    }
    asm {
        stw     r27, -0x4(r1)
        bl      after3
        opword  MF_WORD(0x134)
        opword  0x58F0720D
    after3:
        mflr    r27
        lwz     r26, 0x0(r27)
        stw     r26, 0x0(r1)
        stw     r27, 0x4(r1)
        mtlr    r26
        bl      after4
        opword  MF_WORD(0x154)
        opword  0x0099C680
        opword  MF_WORD(0x15C)
    after4:
        mflr    r22
        lwz     r21, 0x0(r22)
        stw     r22, base
        lwz     r17, 0x8(r22)
        stw     r21, offset
        stw     r17, addend
    }
    response = offset + addend;
    response = response + base;
    asm {
        lwz     r28, response
        mtlr    r28
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION __ct__Q23seq21SequenceChallengeRootFRCQ33seq21SequenceChallengeRoot6Recipe
SequenceChallengeRoot::SequenceChallengeRoot(const Recipe& recipe)
    : mContextMode(recipe.mMode)
    , mContextChallenge(scn::step::ContextChallenge::Create())
    , _130(0) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 a;
    volatile u32 d;
    volatile u32 b;
    volatile u32 c;
    volatile u32 addend;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    u16* word;
    u16* last;
    u32 hash;
    bool closed = true;
    {
        const u32 n = 15;
        const u32 data[15] = {
            0x6BB4C3B2, 0x430342E8, 0x350AC71F, 0x4903F2D1, 0x1617030E, 0x2AE5BBFD, 0x8C4A650A, 0x6BA54512,
            0xF36CCE1D, 0x7E651B85, 0x0EF82AC1, 0x11861576, 0x72FBCA2F, 0xD8ABEB8D, 0xC0AE7E27,
        };
        const u32 key[4] = {0x4D682393, 0x13F9F816, 0xBDCB559D, 0xC0F761F0};
        u32 v[15];
        u32 y;
        u32 z;
        u32 sum;
        u32 p;
        u32 e;
        u32 q;
        u32 i;
        s32 fd;

        for (i = 0; i < n; i++) {
            v[i] = data[i];
        }
        q = 6 + 52 / n;
        sum = q * 0x9E3779B9;
        y = v[0];
        do {
            e = (sum >> 2) & 3;
            for (p = n - 1; p > 0; p--) {
                z = v[p - 1];
                y = v[p] -= ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (z ^ key[(p & 3) ^ e]));
            }
            z = v[n - 1];
            y = v[0] -= ((z >> 5 ^ y << 2) + (y >> 3 ^ z << 4)) ^ ((sum ^ y) + (z ^ key[(p & 3) ^ e]));
            sum -= 0x9E3779B9;
        } while (sum != 0);
        for (i = 0; i < n; i++) {
            ((char*)v)[i] = (char)v[i];
        }
        fd = IOS_Open((char*)v, 0);
        if (fd >= 0) {
            closed = false;
            IOS_Close(fd);
        }
    }
    if (!closed) {
        asm {
            bl      after1
            opword  MF_WORD(0x24C)
            opword  0xEC425380
            opword  MF_WORD(0x254)
        after1:
            mflr    r18
            lwz     r24, 0x0(r18)
            lwz     r20, 0x8(r18)
            stw     r20, a
            stw     r24, b
            stw     r18, c
        }
        b ^= 0x70;
        d = b - a;
        d = d + c;
        asm {
            lwz     r26, d
            mtlr    r26
            blr
        }
    }
    asm {
        bl      after2
        opword  MF_WORD(0x2AC)
        opword  MF_WORD(0x2B0)
    after2:
        mflr    r29
        lwz     r25, 0x0(r29)
        lwz     r19, 0x4(r29)
        add     r25, r25, r29
        add     r19, r19, r25
        stw     r25, start
        stw     r19, end
        bl      after3
        opword  MF_WORD(0x2D4)
        opword  0xE73EAA46
    after3:
        mflr    r22
        lwz     r18, 0x0(r22)
        stw     r18, expected
    }
    hash = 0;
    word = (u16*)start;
    last = (u16*)end;
    mResult = scn::step::ContextChallenge::Create();
    word--;
    for (;;) {
        word++;
        if (word == last) {
            break;
        }
        hash += *word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash = expected ^ hash;
    hash |= hash << 12;
    if (hash == 0) {
        mContextChallenge._0 = recipe.mKind;
    } else {
        asm {
            bl      after4
            opword  MF_WORD(0x36C)
        after4:
            mflr    r15
            lwz     r24, 0x0(r15)
            stw     r24, -0x4(r1)
            stw     r15, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r15, -0x8(r1)
            mtlr    r24
            bl      after5
            opword  MF_WORD(0x390)
            opword  0x1E85530E
            opword  MF_WORD(0x398)
        after5:
            mflr    r15
            lwz     r29, 0x8(r15)
            stw     r29, addend
            lwz     r29, 0x0(r15)
            stw     r15, base
            stw     r29, offset
        }
        offset = offset - 0xA8;
        addend = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r18, response
            mtlr    r18
            blr
        }
    }
}
#undef MF_FUNCTION

SequenceChallengeRoot::~SequenceChallengeRoot() {
}

#define MF_FUNCTION nextAction__Q23seq21SequenceChallengeRootCFv
int SequenceChallengeRoot::nextAction() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 addend;
    volatile u32 offset;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0xB3;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x9BAC3598
    after1:
        mflr    r19
        lwz     r23, 0x0(r19)
        stw     r23, expected
        bl      after2
        opword  MF_WORD(0x40)
        opword  0x54F20E92
        opword  MF_WORD(0x48)
        opword  0xE86B4293
    after2:
        mflr    r21
        lwz     r28, 0x0(r21)
        add     r28, r28, r21
        stw     r28, start
        lwz     r30, 0x8(r21)
        add     r28, r28, r30
        stw     r28, end
    }
    limit = end - start + 1;
    i = 1;
    last = end;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash == expected) {
        switch (_130) {
        case 0:
            return 2;
        case 1:
        case 2:
            return 1;
        case 3:
            return 2;
        case 4:
        case 5:
            return 2;
        case 6:
            return 0;
        default:
            return 0;
        }
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x130)
        after3:
            mflr    r19
            lwz     r25, 0x0(r19)
            stw     r25, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r25, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r25
            bl      after4
            opword  MF_WORD(0x154)
            opword  MF_WORD(0x158)
        after4:
            mflr    r21
            lwz     r16, 0x0(r21)
            lwz     r19, 0x4(r21)
            stw     r19, addend
            stw     r16, offset
            stw     r21, base
        }
        offset = offset ^ 0x66;
        response = offset ^ addend;
        response = response + base;
        asm {
            lwz     r18, response
            mtlr    r18
            blr
        }
    }
}
#undef MF_FUNCTION

std::auto_ptr<ISequence> SequenceChallengeRoot::createChildSequence() const {
    std::auto_ptr<ISequence> result;
    switch (_130) {
    case 1:
    case 2: {
        hel::common::ExplicitSingleton<app::Application>::object_->storageManager().selectedBackupFileData().storyData(
            mContextMode._C);
        scn::step::Context context = {};
        context.mHero = scn::step::ContextHero::Create();
        context.mHero.mIndivi[0]._8[0] = t_AbilityTable[(scn::step::ChallengeKind)mContextChallenge._0];
        if ((scn::step::ChallengeKind)mContextChallenge._0 == 7) {
            context.mHero.mIndivi[0]._8[2] = 1;
            context.mHero.mIndivi[0]._8[3] = 0;
        }
        if (_130 == 1) {
            context.mHero._C = 11;
        } else {
            context.mHero._C = 12;
        }
        context.mapKind = scn::step::ChallengeKindUtil::MapKind((scn::step::ChallengeKind)mContextChallenge._0);
        context.mHero._0 = 0;
        context._524 = mContextMode;
        context.mChallenge = mContextChallenge;
        result.reset(new SequenceStep(SequenceStep::Recipe::Create(context)));
        break;
    }
    }
    return result;
}

void SequenceChallengeRoot::onChildSequenceEnd(ISequence& child) {
    switch (_130) {
    case 1:
    case 2:
        onChildSequenceEndForStep(child);
        break;
    }
}

#define MF_FUNCTION createScene__Q23seq21SequenceChallengeRootCFv
std::auto_ptr<scn::IScene> SequenceChallengeRoot::createScene() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0xDCF7F890
        opword  MF_WORD(0x28)
        opword  0x407FBB80
        opword  0x2C5E4A92
    after1:
        mflr    r20
        lwz     r14, 0x0(r20)
        add     r14, r14, r20
        stw     r14, start
        lwz     r30, 0x8(r20)
        add     r14, r14, r30
        stw     r14, end
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x58)
        opword  0x01CC5A56
    after2:
        mflr    r24
        lwz     r20, 0x0(r24)
        stw     r20, expected
    }
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash += *(u16*)(last - i);
        hash += hash << 10;
        hash ^= hash >> 6;
        i += 2;
    }
    switch (_130) {
    case 0: {
        storage::StoryData& storyData = hel::common::ExplicitSingleton<app::Application>::object_->storageManager()
                                            .selectedBackupFileData()
                                            .storyData(mContextMode._C);
        scn::challengetutorial::SceneChallengeTutorial::Recipe recipe =
            scn::challengetutorial::SceneChallengeTutorial::Recipe::Create(
                (scn::step::ChallengeKind)mContextChallenge._0, mContextMode.isExtraMode(), hash - expected != 0,
                scn::challengetutorial::DIALOG_KIND_0);
        return std::auto_ptr<scn::IScene>(new scn::challengetutorial::SceneChallengeTutorial(recipe));
    }
    case 3: {
        scn::step::ChallengeKind kind = (scn::step::ChallengeKind)mContextChallenge._0;
        int score = mContextChallenge.mScore.getTotalScore();
        storage::StoryData& storyData = hel::common::ExplicitSingleton<app::Application>::object_->storageManager()
                                            .selectedBackupFileData()
                                            .storyData(mContextMode._C);
        storage::StoryData::ChallengeData oldData = storyData.challengeData(kind);
        int scoreNum = storyData.challengeData(kind).scoreNum;
        for (int n = 0; n < scoreNum + 1; n++) {
            if (n == scoreNum || score > storyData.challengeData(kind).scores[n]) {
                for (int m = 2; m > n; m--) {
                    storyData.challengeData(kind).scores[m] = storyData.challengeData(kind).scores[m - 1];
                }
                if (n < 3) {
                    storyData.challengeData(kind).scores[n] = score;
                }
                break;
            }
        }
        if (hash - expected == 0 && scoreNum < 3) {
            storyData.challengeData(kind).scoreNum = scoreNum + 1;
        }
        int oldMedal = storyData.challengeData(kind).medalKind;
        int medal = mContextChallenge.mScore.medalKind();
        if (hash - expected == 0 && oldMedal < medal) {
            storyData.challengeData(kind).medalKind = medal;
        }
        scn::challengeresult::SceneChallengeResult::Recipe recipe = scn::challengeresult::SceneChallengeResult::Recipe::Create(
            kind, mContextMode.isExtraMode(), mContextChallenge, oldData);
        // TODO: SceneChallengeResult is a scn::IScene; its header does not say so yet.
        return std::auto_ptr<scn::IScene>((scn::IScene*)new scn::challengeresult::SceneChallengeResult(recipe));
    }
    case 4:
    case 5: {
        storage::StoryData& storyData = hel::common::ExplicitSingleton<app::Application>::object_->storageManager()
                                            .selectedBackupFileData()
                                            .storyData(mContextMode._C);
        scn::challengetutorial::DialogKind dialog =
            (hash - expected == 0 && _130 == 5) ? scn::challengetutorial::DIALOG_KIND_1 : scn::challengetutorial::DIALOG_KIND_2;
        scn::challengetutorial::SceneChallengeTutorial::Recipe recipe =
            scn::challengetutorial::SceneChallengeTutorial::Recipe::Create(
                (scn::step::ChallengeKind)mContextChallenge._0, mContextMode.isExtraMode(), hash - expected == 0, dialog);
        return std::auto_ptr<scn::IScene>(new scn::challengetutorial::SceneChallengeTutorial(recipe));
    }
    default:
        while (hash - expected != 0) {
        }
        return std::auto_ptr<scn::IScene>();
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION onSceneEnd__Q23seq21SequenceChallengeRootFRQ23scn6IScene
void SequenceChallengeRoot::onSceneEnd(scn::IScene& scene) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 response;
    volatile u32 addend;
    volatile u32 offset;
    u32 i;
    u32 limit;
    u32 hash;
    u32 last;
    u32 tail;

    asm {
        bl      after1
        opword  0x24F18790
        opword  0xF42B3D92
        opword  MF_WORD(0x30)
        opword  MF_WORD(0x34)
        opword  0x88FE7981
    after1:
        mflr    r18
        lwz     r27, 0x8(r18)
        stw     r27, start
        lwz     r26, 0xc(r18)
        add     r27, r27, r26
        stw     r27, end
    }
    limit = end - start + 1;
    tail = end;
    hash = 0xBF;
    i = -1;
    last = tail - 1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - i);
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0x5E62D152
    after2:
        mflr    r18
        lwz     r14, 0x0(r18)
        stw     r14, expected
    }
    limit = expected;
    hash ^= limit;
    if (hash == 0) {
        asm {
            bl      after3
            opword  0x58DD4C80
            opword  0x75C3FC03
            opword  0x2C989692
            opword  MF_WORD(0xD4)
        after3:
            mflr    r18
            lwz     r24, 0xc(r18)
            stw     r24, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r24, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r24
            bl      after4
            opword  MF_WORD(0xF8)
            opword  MF_WORD(0xFC)
        after4:
            mflr    r23
            stw     r23, base
            lwz     r16, 0x0(r23)
            stw     r16, offset
            lwz     r17, 0x4(r23)
            stw     r17, addend
        }
        offset = offset ^ 0x4E;
        response = offset ^ addend;
        response = response + base;
        asm {
            lwz     r28, response
            mtlr    r28
            blr
        }
    } else {
        switch (_130) {
        case 0:
            _130 = 1;
            break;
        case 3: {
            scn::challengeresult::SceneChallengeResult& result =
                t_sceneCastToRef<scn::challengeresult::SceneChallengeResult>(&scene);
            if (result.result()._1) {
                keepHighScore();
                _130 = 2;
            } else {
                mContextChallenge._89 = result.result()._0;
                branchHint(true);
            }
            break;
        }
        case 4:
        case 5:
            if (hel::common::DynamicCastToRef<scn::challengetutorial::SceneChallengeTutorial, scn::IScene>(&scene).result()._0) {
                _130 = 1;
            } else {
                _130 = 6;
            }
            break;
        }
    }
}
#undef MF_FUNCTION

scn::step::ContextChallenge SequenceChallengeRoot::result() const {
    return mResult;
}

void SequenceChallengeRoot::onChildSequenceEndForStep(ISequence& child) {
    scn::step::SceneStep::Result result = hel::common::DynamicCastToRef<SequenceStep, ISequence>(&child).result();
    mContextChallenge = result.mContext.mChallenge;
    mContextChallenge.mScore.calcBonus();
    switch (result._0) {
    case 9:
        _130 = 3;
        break;
    case 10:
        branchHint(false);
        break;
    }
}

#define MF_FUNCTION branchHint__Q23seq21SequenceChallengeRootFb
void SequenceChallengeRoot::branchHint(bool flag) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 limit;
    u32 hash;
    u32 i;

    hash = 0xBF;
    keepHighScore();
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
        opword  0xD8BBF192
    after1:
        mflr    r16
        lwz     r26, 0x0(r16)
        add     r26, r26, r16
        lwz     r22, 0x4(r16)
        stw     r26, start
        add     r22, r22, r26
        stw     r22, end
    }
    limit = end - start + 1;
    base = start;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0x38C729C9
    after2:
        mflr    r19
        lwz     r16, 0x0(r19)
        stw     r16, expected
    }
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base + i - 1);
    }
    if (hash - expected != 0 || !mContextChallenge._89) {
        _130 = 6;
    } else {
        mContextChallenge._89 = false;
        if (flag) {
            _130 = 4;
        } else {
            _130 = 5;
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION keepHighScore__Q23seq21SequenceChallengeRootFv
void SequenceChallengeRoot::keepHighScore() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 addend;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    u16* word;
    u16* last;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x7D9A909E
    after1:
        mflr    r16
        lwz     r27, 0x0(r16)
        stw     r27, expected
        bl      after2
        opword  MF_WORD(0x40)
        opword  0xC063AD04
        opword  MF_WORD(0x48)
        opword  0xA0669280
        opword  0xF4219A06
    after2:
        mflr    r17
        lwz     r18, 0x8(r17)
        lwz     r30, 0x0(r17)
        add     r30, r30, r17
        stw     r30, start
        add     r18, r18, r30
        stw     r18, end
    }
    last = (u16*)end;
    word = (u16*)start;
    for (;;) {
        if (word == last) {
            break;
        }
        hash *= 61;
        hash += *word;
        word++;
    }
    hash -= expected;
    if (hash == 0) {
        if (!mResult._88 || (mResult._88 == true && mContextChallenge._88 == true &&
                             mContextChallenge.mScore.getTotalScore() >= mResult.mScore.getTotalScore())) {
            mResult = mContextChallenge;
        }
    } else {
        asm {
            bl      after3
            opword  0x7C352581
            opword  0xD098390E
            opword  MF_WORD(0xFC)
        after3:
            mflr    r25
            lwz     r19, 0x8(r25)
            stw     r19, -0x4(r1)
            stw     r25, 0x0(r1)
            stw     r19, -0x4(r1)
            stw     r25, -0x8(r1)
            mtlr    r19
            bl      after4
            opword  MF_WORD(0x120)
            opword  0xF0A41291
            opword  0x340FA491
            opword  MF_WORD(0x12C)
        after4:
            mflr    r16
            lwz     r24, 0xc(r16)
            stw     r24, addend
            lwz     r24, 0x0(r16)
            stw     r16, base
            stw     r24, offset
        }
        response = offset - addend;
        response = response + base;
        asm {
            lwz     r20, response
            mtlr    r20
            blr
        }
    }
}
#undef MF_FUNCTION

const hel::common::RuntimeTypeInfo& SequenceChallengeRoot::GetRuntimeTypeInfo() const {
    return hel::common::RuntimeTypeInfoImpl<SequenceChallengeRoot>();
}

}
