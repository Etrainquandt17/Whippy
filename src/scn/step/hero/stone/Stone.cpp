#include "scn/step/hero/stone/Stone.h"

#include "file/FileAccessor.h"
#include "file/Utility.h"
#include "g3d/ModelAccessor.h"
#include "g3d/ResFileRepository.h"
#include "gobj/FootState.h"
#include "gobj/GearModel.h"
#include "gobj/Model.h"
#include "metafortress.h"
#include "mintglue/VectorInline.h"
#include "scn/step/Component.h"
#include "scn/step/hero/Gear.h"
#include "scn/step/hero/Heap.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Model.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/StoryModeUtil.h"
#include "scn/step/hero/Water.h"
#include "scn/step/hero/modeldesc/ModelDesc.h"
#include "scn/step/hero/stone/StateChange.h"
#include "scn/step/hero/stone/StateStartJump.h"
#include "scn/step/hero/stone/StateUpper.h"
#include "std/tr1/reference_wrapper.h"
#include "util/StateChanger.h"

using g3d::ModelAccessor;
using g3d::ResFileAccessor;
using hel::math::Vector3;

namespace scn {
namespace step {
namespace hero {
namespace stone {

namespace {

const u32 STONEBODY_TABLE_0[16] = {
    12, 12, 12, 12, 12, 10, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0,
};

const u32 STONEBODY_TABLE_1[16] = {
    1200, 1200, 1200, 1200, 1200, 1000, 1000, 1000, 225, 225, 225, 225, 0, 0, 0, 0,
};

const u32 STONEBODY_TABLE_2[16] = {
    1200, 1200, 1200, 1200, 1200, 1000, 1000, 1000, 225, 225, 225, 225, 25, 25, 25, 25,
};

const u32 STONEBODY_TABLE_EXTRA[16] = {
    1180, 1180, 1180, 1180, 1180, 1000, 1000, 1000, 225, 225, 225, 225, 50, 50, 50, 50,
};

const char* STONEBODY_MODEL_TABLE[16] = {
    "g3d/step/chara/hero/kirby/stone/stonebody/Stone.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/StarBlock.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/HachiTon.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/Kirby.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/Glove.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/MMan.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/HoshiBlock.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/RickKineCoo.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/Marc.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/Wambam.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/FujiHAL.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/Dragoon.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/DogEgg.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/LegendItem.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/FirstKirby.brres.cmpbin",
    "g3d/step/chara/hero/kirby/stone/stonebody/MetaGalactic.brres.cmpbin",
};

// TODO: the part of hero::Model at 0xC, of which only this virtual function is known.
class ModelHolder {
public:
    virtual void _8();
    virtual ModelAccessor model();
};

inline ModelHolder& t_modelHolder(Model& model) {
    return *reinterpret_cast<ModelHolder*>(reinterpret_cast<u8*>(&model) + 0xC);
}

inline gobj::Model& t_gobjModel(Model& model) {
    return *reinterpret_cast<gobj::Model*>(reinterpret_cast<u8*>(&model) + 0xC);
}

}

Stone::Stone(Component& component, Hero& hero)
    : AbilityBase(component, hero)
    , _C(false)
    , _10(0)
    , mNodeChanger(mHero.model().body())
    , mContext(mNodeChanger)
    , mHeap(mHero.heap().getAllocator(), 0xC000, "HrStoneBody")
    , mBlock(mem::MemBlock::EmptyBlock()) {
}

#define MF_FUNCTION __dt__Q53scn4step4hero5stone5StoneFv
Stone::~Stone() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    hash = 0xC1;
    asm {
        bl      after1
        opword  MF_WORD(0x40)
        opword  0x714C9226
    after1:
        mflr    r28
        lwz     r27, 0x0(r28)
        stw     r27, expected
        bl      after2
        opword  MF_WORD(0x58)
        opword  0xB13EE709
        opword  0x240CDC92
        opword  MF_WORD(0x64)
    after2:
        mflr    r14
        lwz     r25, 0x0(r14)
        add     r25, r25, r14
        lwz     r26, 0xc(r14)
        stw     r25, start
        add     r26, r26, r25
        stw     r26, end
    }
    limit = end - start + 1;
    base = start;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash = (hash << 4 ^ hash >> 28) ^ *(u16*)(base + i - 1);
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected == 0 && _C) {
        stoneBodyClear();
        mHero.model().mAnim.unregisterResFile(9);
    }
}
#undef MF_FUNCTION

void Stone::setup() {
    ResFileAccessor base = mComponent.resFileRepos().get("step/chara/hero/kirby/base/Pink", false);
    ResFileAccessor motion = mComponent.resFileRepos().get("step/chara/hero/kirby/stone/Motion", true);
    motion.bind(base, false);
    mHero.model().mAnim.registerResFile(9, motion);
    gearHat().set(modeldesc::Stone::HatPath());
    gearHand().set(modeldesc::Stone::HandPath());
    gearHand().setVisibility(false);
    _C = true;
}

bool Stone::tryToChangeState() {
    if (mHero.water().isInWater()) {
        return false;
    }
    if (mHero.stateChecker().isFloat()) {
        return false;
    }
    if (StateUpper::TryToChangeState(&mHero)) {
        return true;
    }
    if (StateChange::ChkChangeStateScrew(&mHero)) {
        stoneChangePrepare();
        mContext.setIsScrew(true);
        mContext.setIsRun(false);
        mHero.stateChanger().setNextState<StateChange, Hero*, std::tr1::reference_wrapper<Context> >(
            &mHero, std::tr1::ref(mContext));
        return true;
    }
    if (StateStartJump::ChkChangeState(&mHero)) {
        stoneChangePrepare();
        mHero.stateChanger().setNextState<StateStartJump, Hero*, std::tr1::reference_wrapper<Context> >(
            &mHero, std::tr1::ref(mContext));
        return true;
    }
    return false;
}

void Stone::onStateEndCleanUp() {
    t_modelHolder(mHero.model()).model().setVisibility(true);
    t_gobjModel(mHero.model()).setScale(Vector3(1.0f, 1.0f, 1.0f));
    if (gearHat().isValid()) {
        gearHat().setVisibility(true);
    }
    if (gearBody().isValid()) {
        gearBody().setVisibility(false);
    }
    if (gearHand().isValid()) {
        gearHand().setVisibility(false);
    }
}

void Stone::stoneChangePrepare() {
    if (StoryModeUtil::IsExtraMode(mHero.comp())) {
        mNodeChanger.select(STONEBODY_TABLE_EXTRA, 16);
    } else if (_10 > 35) {
        mNodeChanger.select(STONEBODY_TABLE_2, 16);
    } else if (_10 > 20) {
        mNodeChanger.select(STONEBODY_TABLE_1, 16);
    } else {
        mNodeChanger.select(STONEBODY_TABLE_0, 16);
    }
    _10++;
    mContext.resetFlag();
    bool isGround = mHero.footState().isGround();
    bool isRun = mHero.stateChecker().isRun();
    mContext.setIsRun(isGround && isRun);
    stoneBodyClear();
    u32 index = mNodeChanger.selectedIndex();
    file::FileAccessor file(STONEBODY_MODEL_TABLE[index], false);
    mBlock = file::Utility::UncompressedFile(file.block(), mHeap.obj());
    nw4r::g3d::ResFile res(mBlock.address());
    res.Init();
    res.Bind();
    mResFile.construct(res);
    gearBody().set(*mResFile, modeldesc::Stone::BodyModel(), true);
    gearBody().setVisibility(false);
    gearBody().model().removeParentNode();
}

#define MF_FUNCTION stoneBodyClear__Q53scn4step4hero5stone5StoneFv
void Stone::stoneBodyClear() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x90B5BEB8
    after1:
        mflr    r26
        lwz     r20, 0x0(r26)
        stw     r20, expected
        bl      after2
        opword  MF_WORD(0x38)
        opword  0x8DCEF70F
    after2:
        mflr    r30
        lwz     r20, 0x0(r30)
        add     r20, r20, r30
        stw     r20, start
        bl      after3
        opword  0x79618404
        opword  0x90587680
        opword  MF_WORD(0x5C)
    after3:
        mflr    r30
        lwz     r22, 0x8(r30)
        add     r20, r20, r22
        stw     r20, end
    }
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (; i != limit; i += 2) {
        hash *= 193;
        hash += *(u16*)(last - i);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected == 0) {
        if (!gearBody().isValid()) {
            asm {
                b       done
            }
        }
        gearBody().clear();
        gearBody().procDispose();
        {
            nw4r::g3d::ResFile file(mBlock.address());
            file.Release();
            file.Terminate();
        }
        mResFile.destruct();
        mHeap.obj().free(mBlock.address());
        mBlock = mem::MemBlock::EmptyBlock();
    }
done:;
}
#undef MF_FUNCTION

Gear& Stone::gearHat() {
    return mHero.model().hat();
}

#define MF_FUNCTION gearBody__Q53scn4step4hero5stone5StoneFv
Gear& Stone::gearBody() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 addend;
    volatile u32 mfBase;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x4CBB4980
        opword  MF_WORD(0x34)
        opword  0x6C7C6291
        opword  0x5B30DE0C
    after1:
        mflr    r24
        lwz     r30, 0x8(r24)
        lwz     r20, 0x0(r24)
        add     r20, r20, r24
        stw     r20, start
        add     r30, r30, r20
        stw     r30, end
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    asm {
        bl      after2
        opword  MF_WORD(0x78)
        opword  0x8251CC9D
    after2:
        mflr    r16
        lwz     r25, 0x0(r16)
        stw     r25, expected
    }
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000181;
    }
    limit = hash >> 10;
    hash ^= limit;
    limit = hash << 20;
    hash ^= limit;
    limit = expected;
    hash ^= limit;
    if (hash != 0) {
        asm {
            stw     r30, -0x4(r1)
            bl      after3
            opword  MF_WORD(0xDC)
            opword  0x0685640A
            opword  0xB878FA80
        after3:
            mflr    r30
            lwz     r25, 0x0(r30)
            stw     r25, 0x0(r1)
            stw     r30, 0x4(r1)
            mtlr    r25
            bl      after4
            opword  MF_WORD(0x100)
            opword  0x38B7ED91
            opword  0x2000E190
            opword  MF_WORD(0x10C)
        after4:
            mflr    r20
            lwz     r28, 0x0(r20)
            lwz     r25, 0xc(r20)
            stw     r25, addend
            stw     r28, offset
            stw     r20, mfBase
        }
        offset = offset - 0xE3;
        response = offset + addend;
        response = response + mfBase;
        asm {
            lwz     r29, response
            mtlr    r29
            blr
        }
    } else {
        return mHero.model().body();
    }
}
#undef MF_FUNCTION

Gear& Stone::gearHand() {
    return mHero.model().weapon();
}

}}}}  // namespace scn::step::hero::stone
