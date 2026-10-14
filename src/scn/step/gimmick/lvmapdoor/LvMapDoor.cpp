#include "scn/step/gimmick/lvmapdoor/LvMapDoor.h"

#include "hel/common/FixedStringIN.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/StageKindUtil.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/camera/MainCamera.h"
#include "scn/step/gimmick/lvmapdoor/Manager.h"
#include "scn/step/gimmick/lvmapdoor/MintLvMapDoor.h"

using hel::common::FixedStringIN;
using hel::math::Vector2;

namespace scn {
namespace step {
namespace gimmick {
namespace lvmapdoor {

namespace {

// TODO: remove once the functions these strings belong to are here. They are the strings of the
// unit's two name tables and of the constructor, and stand in .data ahead of the ones the
// functions below address. Strings come out in the order of the file, so this has to stay first.
#pragma force_active on
const char* const T_EARLIER_STRINGS[] = {
    "step/gimmick/DoorWhispy",
    "step/gimmick/DoorDoubter",
    "step/gimmick/DoorFattyBuffer",
    "step/gimmick/DoorGoliath",
    "step/gimmick/DoorGrantLowper",
    "step/gimmick/DoorMetalGeneral",
    "step/gimmick/DoorLandia",
    "Lv1BossDoorAppear",
    "Lv2BossDoorAppear",
    "Lv3BossDoorAppear",
    "Lv4BossDoorAppear",
    "Lv5BossDoorAppear",
    "Lv6BossDoorAppear",
    "Lv7BossDoorAppear",
    "step/gimmick/LvMapDoor",
    "step/gimmick/DoorLvMap",
    "step/gimmick/DoorFlagLvMap",
    "step/gimmick/StageBoard",
    "LMapStageSphereN",
};
#pragma force_active reset

}

void LvMapDoor::procAnim() {
    cameraOutCheck();
    if (!mStop.isObjStopped()) {
        updateDoorInOut();
        MintLvMapDoor::Register(*this);
        mRunner.execute();
        MintLvMapDoor::Unregister(*this);
        mfUpdateSoundSE();
        _398.updateFrame();
        _30.updateFrame();
        _1E4.updateFrame();
        if (_1912 && _1E4.isAnimEnd()) {
            _1E4.setAnimByName(_1917 ? "CompleteWait" : "NormalWait");
            _1E4.start(true);
        }
        if (_398.isAnimEnd()) {
            const char* kind = _24 ? "Boss" : "";
            _398.setAnimByName(FixedStringIN<char, 40>::FromFormat(_1911 ? "ClearWait%sStage%d" : "NormalWait%sStage%d", kind, _1C + 1));
            _398.start(true);
        }
        if (_54C) {
            _54C->updateFrame();
            if (_54C->isAnimEnd()) {
                setBossNormalWaitAnim();
                reqUnlockEndEffect1();
            }
        }
    }
    mStageSphere.updateFrame();
    stageSphereControl();
}

void LvMapDoor::returnDemoDoorInit() {
    _1914 = true;
    setDoorWaitAnim();
    if (_54C != 0) {
        setBossNormalWaitAnim();
        reqUnlockEffect1();
    }
    _2178 = true;
    if (mManager.showDoorUnlockStarDemo()) {
        _28.reset(mParam.obj()._4);
    }
    mRunner.setEntryPoint("Scn.Step.Gimmick.LvMapDoor.Unlock.CloseDoor");
}

void LvMapDoor::unlockDemoDoorInit() {
    _30.setAnimByName("InvalidWait");
    _30.start(true);
    if (_54C != 0) {
        _30.setVisibility(false);
        _54C->setAnimByName("InvalidWait");
        if (_20 != 0x1A) {
            _54C->start(true);
        }
        reqBossInvalidWaitEffect();
    }
    _1915 = true;
    if (isFirstDoorDemo()) {
        mRunner.setEntryPoint("Scn.Step.Gimmick.LvMapDoor.Unlock.FirstDoor");
    } else {
        mRunner.setEntryPoint(_24 ? "Scn.Step.Gimmick.LvMapDoor.Unlock.UnlockBossDoor" : "Scn.Step.Gimmick.LvMapDoor.Unlock.UnlockDoor");
    }
}

#define MF_FUNCTION clearedDoorInit__Q53scn4step7gimmick9lvmapdoor9LvMapDoorFv
void LvMapDoor::clearedDoorInit() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 tail;
    u32 hash = 0;

    _1914 = false;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x3E356720
    after1:
        mflr    r26
        lwz     r20, 0x0(r26)
        stw     r20, expected
    }
    setDoorWaitAnim();
    asm {
        bl      after2
        opword  MF_WORD(0x48)
        opword  0xE82FAF92
        opword  MF_WORD(0x50)
        opword  0x88B9D180
    after2:
        mflr    r15
        lwz     r27, 0x8(r15)
        stw     r27, start
        lwz     r29, 0x0(r15)
        stw     r29, end
    }
    word = start;
    tail = end;
    word -= 2;
    while (word != tail - 2) {
        word += 2;
        hash *= 107;
        hash += *(u16*)word;
    }
    if (hash - expected == 0 && has54C()) {
        setBossNormalWaitAnim();
        reqUnlockEffect1();
    }
}
#undef MF_FUNCTION

namespace {

// TODO: remove once mfStageBoardInit is here; this is its string, in its place.
#pragma force_active on
const char* const T_STAGE_BOARD_STRING = "InvalidWaitStage%d";
#pragma force_active reset

}

void LvMapDoor::setDoorCloseAnim() {
    if (_1914) {
        _30.setAnimByName(_1911 ? "ClearClose" : "NormalClose");
        _30.start(false);
        _AA0.release();
        _1916 = true;
        _1914 = false;
        _1913 = false;
    }
}

void LvMapDoor::setDoorNearAnim() {
    if (!_1914) {
        _30.setAnimByName(_1911 ? "ClearKirbyNear" : "NormalKirbyNear");
        _30.start(false);
        _1968.start(0x4B8);
        _1914 = true;
        _1913 = false;
    }
}

#define MF_FUNCTION setDoorWaitAnim__Q53scn4step7gimmick9lvmapdoor9LvMapDoorFv
void LvMapDoor::setDoorWaitAnim() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 tail;
    u32 hash;
    const char* name;

    hash = 0x811C9E07;
    asm {
        bl      after1
        opword  0xACA42D92
        opword  MF_WORD(0x38)
        opword  0xF84CD391
        opword  0x24064580
        opword  MF_WORD(0x44)
        opword  0x1F11FD0E
        opword  0xF8647907
    after1:
        mflr    r23
        lwz     r14, 0x4(r23)
        lwz     r27, 0x10(r23)
        stw     r27, end
        stw     r14, start
    }
    word = start;
    tail = end;
    for (; word != tail; word += 2) {
        hash ^= *(u16*)word;
        hash *= 0x010001A7;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    asm {
        bl      after2
        opword  MF_WORD(0xA4)
        opword  0x7C5283C6
    after2:
        mflr    r18
        lwz     r21, 0x0(r18)
        stw     r21, expected
    }
    hash += hash << 15;
    if (hash - expected != 0 || _1914) {
        if (_2197) {
            if (_1911) {
                name = "ClearOpen";
            } else {
                name = "NormalOpen";
            }
            _30.setAnimByName(name);
            _30.start(false);
            _1913 = true;
        } else {
            if (_1911) {
                name = "ClearKirbyNearWait";
            } else {
                name = "NormalKirbyNearWait";
            }
            _30.setAnimByName(name);
            _30.start(true);
            _1913 = true;
            _AA0.requestP(effect::KIND_225, GetModelPos(_10), false);
        }
    } else {
        if (_1911) {
            name = "ClearWait";
        } else {
            name = "NormalWait";
        }
        _30.setAnimByName(name);
        _30.start(true);
        _1913 = true;
    }
}
#undef MF_FUNCTION

void LvMapDoor::onVisibleStageBoard() {
    _398.setVisibility(true);
}

#define MF_FUNCTION setZoom__Q53scn4step7gimmick9lvmapdoor9LvMapDoorFff
void LvMapDoor::setZoom(f32 a, f32 b) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 tail;
    u32 limit;
    u32 last;
    u32 hash;
    Vector2 pos(_10);

    asm {
        bl      after1
        opword  MF_WORD(0x40)
        opword  0x84428915
    after1:
        mflr    r15
        lwz     r28, 0x0(r15)
        stw     r28, expected
        bl      after2
        opword  MF_WORD(0x58)
        opword  0xB088C791
        opword  0xFCFE9491
    after2:
        mflr    r24
        lwz     r16, 0x0(r24)
        add     r16, r16, r24
        stw     r16, start
        bl      after3
        opword  0xAC198D93
        opword  MF_WORD(0x7C)
        opword  0x7033A193
        opword  0x845BE080
    after3:
        mflr    r24
        lwz     r26, 0x4(r24)
        add     r16, r16, r26
        stw     r16, end
    }
    limit = end - start + 1;
    i = 1;
    tail = end;
    f32 offset = mParam->_10;
    pos.y += offset;
    hash = 0;
    last = tail - 1;
    for (; i != limit; i += 2) {
        hash += *(u16*)(last - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    mComponent.cameraController().setZoom(pos, a, b, expected != hash);
}
#undef MF_FUNCTION

u32 LvMapDoor::setZoom(f32 a, f32 b, f32 c, f32 d) {
    Vector2 pos = _10;
    pos.x += b;
    pos.y += c;
    return mComponent.cameraController().setZoom(pos, a, d, false);
}

void LvMapDoor::setDistance(f32 distance) {
    mComponent.mainCamera().setDistance(distance);
    distance -= mComponent.mainCamera().getNearDistance();
    if (distance < 1.0f) {
        distance = 1.0f;
    }
    mComponent.mainCamera().setNear(distance);
}

void LvMapDoor::setTargetDistance(f32 distance) {
    mComponent.mainCamera().setTargetDistance(distance);
}

void LvMapDoor::setTargetFrame(int frame) {
    mComponent.mainCamera().setTargetFrame(frame);
}

void LvMapDoor::reqQuake(camera::QuakeKind kind) {
    mComponent.cameraController().reqQuake(kind);
}

void LvMapDoor::setCameraTargetDoor() {
    mComponent.cameraController().addCameraTarget(_10);
}

void LvMapDoor::unsetCameraTargetDoor() {
    mComponent.cameraController().clearCameraTarget();
}

void LvMapDoor::unsetZoom(u32 handle) {
    mComponent.cameraController().unsetZoom(handle);
}

void LvMapDoor::setCamRotDegX(f32 a, f32 b) {
    mComponent.cameraController().setRotDegX(a, b, true);
}

void LvMapDoor::unsetCamRotDegX(u32 handle) {
    mComponent.cameraController().unsetRotDegX(handle);
}

#define MF_FUNCTION setRotRateBGX__Q53scn4step7gimmick9lvmapdoor9LvMapDoorFf
void LvMapDoor::setRotRateBGX(f32 rate) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0xC5;
    asm {
        bl      after1
        opword  0xFC10D980
        opword  MF_WORD(0x34)
        opword  0x982C3B91
        opword  0x788C7293
        opword  MF_WORD(0x40)
        opword  0x1465F092
        opword  0xC4ABEF91
    after1:
        mflr    r19
        lwz     r22, 0x4(r19)
        lwz     r24, 0x10(r19)
        add     r24, r22, r24
        stw     r22, start
        stw     r24, end
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    asm {
        bl      after2
        opword  MF_WORD(0x7C)
        opword  0xFC6F0853
    after2:
        mflr    r25
        lwz     r24, 0x0(r25)
        stw     r24, expected
    }
    for (;;) {
        if (i == limit) {
            break;
        }
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(last - 1 - i);
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash ^= expected;
    if (hash == 0) {
        mComponent.cameraController().setRotRateBGX(rate);
    } else {
        volatile u32 subtrahend;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 anchor;

        asm {
            bl      after3
            opword  0x0813BB92
            opword  MF_WORD(0x100)
        after3:
            mflr    r24
            lwz     r28, 0x4(r24)
            stw     r28, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r28, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r28
            bl      after4
            opword  MF_WORD(0x124)
            opword  0xFB58CC01
            opword  0xE0384A91
            opword  MF_WORD(0x130)
        after4:
            mflr    r24
            lwz     r19, 0x0(r24)
            stw     r24, anchor
            lwz     r27, 0xc(r24)
            stw     r19, offset
            stw     r27, subtrahend
        }
        response = offset - subtrahend;
        response = response + anchor;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    }
}
#undef MF_FUNCTION

bool LvMapDoor::isInDoor() {
    return _2197;
}

bool LvMapDoor::isBossUnlock() {
    StageKind stage = static_cast<StageKind>(_20 + 1);
    if (stage < 0x26 && StageKindUtil::IsBossStage(stage)) {
        return true;
    }
    return false;
}

int LvMapDoor::getLevel() {
    return _18 + 1;
}

void LvMapDoor::reqUnlockEffect1() {
    switch (_18 + 1) {
    case 4:
    case 5:
    case 6:
    case 7:
        reqOpenEffect1();
        break;
    }
}

void LvMapDoor::reqUnlockEndEffect1() {
    u32 level = _18 + 1;
    if (level == 4 || level == 6 || level == 7) {
        reqOpenEffect1();
    }
}

void LvMapDoor::stopUnlockEffect2() {
    _11D8.release();
}

void LvMapDoor::stopUnlockEffect3() {
    _1574.release();
}

void LvMapDoor::reqCommonEffect() {
    mfSetupCommonEffect();
}

void LvMapDoor::setForbidShowLvMapDoorInfo(bool forbid) {
    _2195 = forbid;
}

info::lvmap::StageSphere& LvMapDoor::stageSphere() {
    return mStageSphere;
}

void LvMapDoor::hideDoorInfoForce() {
    _2171 = false;
    _2174 = 0;
    _2194 = false;
}

// TODO: where these two stand is not known exactly. The link folded both; the map lists them behind
// hel::common::Array<info::SpherePart*, 5>::operator[] in this object, so behind the first stage sphere function.
Component& LvMapDoor::comp() {
    return mComponent;
}

Manager& LvMapDoor::manager() {
    return mManager;
}

}}}}  // namespace scn::step::gimmick::lvmapdoor
