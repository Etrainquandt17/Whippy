#include "scn/step/gimmick/challengedoor/ChallengeDoor.h"

#include "g3d/CharaModelContext.h"
#include "g3d/NodeAccessor.h"
#include "g3d/ResFileRepository.h"
#include "hel/math/Math.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Vector3.h"
#include "metafortress.h"
#include "scn/step/ChallengeKindUtil.h"
#include "scn/step/Component.h"
#include "scn/step/Context.h"
#include "scn/step/SphereUtil.h"
#include "scn/step/StorageAccessor.h"
#include "scn/step/camera/CameraController.h"
#include "scn/step/chara/Location.h"
#include "scn/step/core/MintManager.h"
#include "scn/step/gimmick/challengedoor/MintChallengeDoor.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/StateChecker.h"
#include "scn/step/hero/gimmick/StateEnterChallengeDoor.h"
#include "scn/step/map/BinGmkGeneralEntry.h"
#include "scn/step/map/MemManager.h"
#include "util/ObjList.h"
#include "util/StateChanger.h"

using g3d::CharaModelContext;
using g3d::ResModelContext;
using g3d::Root;
using hel::math::Math;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;

namespace g3d {
class Model;
}

// TODO: a stand-in. The original emits this here and the link drops it, which leaves its strings at the end of
// .data: g3d::ModelAccessor's destructor is implicit there and brings the list node's.
template util::ObjListNode<g3d::Model, util::ObjListDummyType>::~ObjListNode();

namespace scn {
namespace step {
namespace gimmick {
namespace challengedoor {

namespace {

const SphereUnlockKind T_UNLOCKKIND_LIST[] = {
    SPHERE_UNLOCK_KIND_0, SPHERE_UNLOCK_KIND_NONE, SPHERE_UNLOCK_KIND_1, SPHERE_UNLOCK_KIND_2,    SPHERE_UNLOCK_KIND_NONE,
    SPHERE_UNLOCK_KIND_4, SPHERE_UNLOCK_KIND_3,    SPHERE_UNLOCK_KIND_6, SPHERE_UNLOCK_KIND_NONE, SPHERE_UNLOCK_KIND_5,
};

const f32 T_ICONFRAME_LIST[] = { 0.0f, 0.0f, 2.0f, 3.0f, 0.0f, 4.0f, 5.0f, 6.0f, 0.0f, 1.0f };

const char* T_ANIM_LIST[] = { "InvalidWait00", "InvalidFadeout00", "NormalClose00", "NormalOpen00", "NormalWait00" };

}

Result::Result(const Result& other)
    : _0(other._0)
    , mPos(other.mPos)
    , mKind(other.mKind)
    , mDoor(other.mDoor)
    , mUnlockKind(other.mUnlockKind) {}

#define MF_FUNCTION __ct__Q53scn4step7gimmick13challengedoor13ChallengeDoorFRCQ43scn4step3map18BinGmkGeneralEntryRQ33scn4step9Component
namespace {

// TODO: name. Only seen inlined into the constructor.
inline Result CreateResult(ChallengeDoor* door, const map::BinGmkGeneralEntry& entry, ChallengeKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 tail;
    u32 hash;
    Result result;

    asm {
        bl      after1
        opword  MF_WORD(0x44)
        opword  0x8CB2149B
    after1:
        mflr    r23
        lwz     r29, 0x0(r23)
        stw     r29, expected
        bl      after2
        opword  MF_WORD(0x5C)
    after2:
        mflr    r14
        lwz     r28, 0x0(r14)
        stw     r28, end
        bl      after3
        opword  MF_WORD(0x70)
        opword  0x43BA4F0B
        opword  0xACC91093
    after3:
        mflr    r14
        lwz     r28, 0x0(r14)
        stw     r28, start
    }
    word = start;
    tail = end;
    hash = 0;
    for (;;) {
        if (word == tail) {
            break;
        }
        hash *= 61;
        hash += *(u16*)word;
        word += 2;
    }
    result._0 = expected == hash;
    result.mPos = entry._4.toMaproPos().toWorldPos();
    result.mKind = kind;
    result.mDoor = door;
    result.mUnlockKind = T_UNLOCKKIND_LIST[kind];
    return result;
}

}

ChallengeDoor::ChallengeDoor(const map::BinGmkGeneralEntry& entry, Component& component)
    : mComponent(component)
    , mResult(CreateResult(this, entry, ChallengeKind(entry._14 - 1)))
    , mPos(entry._4.toMaproPos().toWorldPos())
    , mResFile(component.resFileRepos().get("step/gimmick/DoorChallenge", false))
    , mModelMain(CharaModelContext(ResModelContext(mResFile, "TopL"), CharaModelContext::DefaultModelBufferOption(), 0,
                                   CharaModelContext::DefaultNumView(), 1, component.mapMemManager().allocator(), true,
                                   CharaModelContext::DefaultOneAnimSlotWorkMemSize(), "GmkDoorChallenge"))
    , mIcon(component, "step/gimmick/ChallengeIcon", "TopL", true, false)
    , mBoard(component, "step/gimmick/ChallengeBoard", "TopL", true, false)
    , _4F4(0)
    , mStop(component)
    , mSe()
    , _5D4(false)
    , _5D5(false)
    , _5D6(false)
    , mRunner(component.mintManager().engine())
    , mSphereCounter(component,
                     mPos.toVector3() + mModelMain.model().nodeByName("NumberL").worldTrans(),
                     SphereUtil::GetNeedSphere(mResult.mUnlockKind))
    , mEffectDoorRelease(component)
    , mEffectDoorRing(component)
    , mEffectDoorWelcome(component)
    , _1128()
    , _1130() {
    mEffectDoorRelease.changeLayer(core::DRAW_LAYER_KIND_4);
    mEffectDoorRing.changeLayer(core::DRAW_LAYER_KIND_4);
    mEffectDoorWelcome.changeLayer(core::DRAW_LAYER_KIND_4);
    if (mResult.mKind < 0 || mResult.mKind > 9) {
        mResult.mKind = CHALLENGE_KIND_SWORD;
    }
    Matrix34 mtx = Matrix34::CreateTrans(Vector3(mPos.x, mPos.y, -2.5f));
    mModelMain.setModelRTMtx(mtx);
    mModelMain.model().setVisibility(true);
    if (StorageAccessor::GetSphereUnlockExecutedDemo(mComponent, ChallengeKindUtil::ToSphereUnlockKind(mResult.mKind)) &&
        StorageAccessor::GetSphereUnlockUnlocked(mComponent, ChallengeKindUtil::ToSphereUnlockKind(mResult.mKind))) {
        if (isLeaveDoor()) {
            mfModelMainSetAnim(T_ANIM_LIST[3]);
            mfModelMainStart(false);
            mModelMain.anim(0).setFrameToTail();
            startLeaveDemo();
            _4F4 = 2;
        } else {
            mfModelMainSetAnim(T_ANIM_LIST[4]);
            mfModelMainStart(true);
        }
        _5D4 = true;
    } else {
        mfModelMainSetAnim(T_ANIM_LIST[0]);
        mfModelMainStart(true);
    }
    mIcon.setAnimByName("Main");
    mIcon.setFrame(T_ICONFRAME_LIST[mResult.mKind]);
    mBoard.setTrans(Vector3(mPos.x, 2.5f + mPos.y, -2.5f));
    mBoard.setVisibility(true);
    const char* name = "Normal";
    if (_5D4) {
        if (!StorageAccessor::GetSphereUnlockEntered(mComponent, ChallengeKindUtil::ToSphereUnlockKind(mResult.mKind))) {
            name = "New";
        } else {
            switch (StorageAccessor::GetChallengeStageMedalKind(mComponent, mResult.mKind)) {
            case 1:
                name = "Copper";
                break;
            case 2:
                name = "Silver";
                break;
            case 3:
                name = "Gold";
                break;
            case 4:
                name = "Platinum";
                break;
            }
        }
    }
    mBoard.setAnimByName(name);
    mBoard.start(true);
    mStop.add(mSe);
    mStop.add(mEffectDoorRelease);
    mStop.add(mEffectDoorRing);
    mStop.add(mEffectDoorWelcome);
    if (_4F4 == 2) {
        mfEffectSetupDoorRing();
        mfEffectSetupDoorWelcome();
    }
}
#undef MF_FUNCTION

ChallengeDoor::~ChallengeDoor() {
    mStop.remove(mEffectDoorWelcome);
    mStop.remove(mEffectDoorRing);
    mStop.remove(mEffectDoorRelease);
    mStop.remove(mSe);
}

void ChallengeDoor::registerToRoot(Root& root) {
    mModelMain.updateWorldMtx();
    mModelMain.registerToRoot(root);
    mIcon.registerToRoot(root);
    mBoard.registerToRoot(root);
    mfSphereCounterRegisterToRoot(root);
}

void ChallengeDoor::mfSphereCounterRegisterToRoot(Root& root) {
    if (_4F4 == 0 && !_5D4) {
        mSphereCounter.registerToRoot(root);
    } else if (!_1130.isEnd()) {
        _1130.advanceIfNotEnd();
        if (_1130.frame() % 5 > 1) {
            mSphereCounter.registerToRoot(root);
        }
    }
}

void ChallengeDoor::procAnim() {
    Vector3 pos = mComponent.heroManager().getMainPlayer().location().pos();
    Vector2 heroPos(pos.x, pos.y);
    mModelMain.updateFrame();
    mBoard.updateFrame();
    mfUpdateCover();
    switch (_4F4) {
    case 0:
        if (mfModelMainIsAnimEnd()) {
            mfSeStop();
        }
        if (searchAir(heroPos) == true) {
            mfModelMainSetAnim(T_ANIM_LIST[3]);
            mfModelMainStart(false);
            mfSeRequest(true);
            mfEffectSetupDoorRing();
            mfEffectSetupDoorWelcome();
            mfSeRequest(true);
            _4F4 = 1;
        }
        break;
    case 1:
        if (mfModelMainIsAnimEnd()) {
            _4F4 = 2;
        }
        break;
    case 2:
        if (mfModelMainIsAnimEnd()) {
            mfSeStop();
        }
        if (!searchAir(heroPos)) {
            mfModelMainSetAnim(T_ANIM_LIST[2]);
            mfSeRequest(false);
            mfModelMainStart(false);
            mfEffectReleaseDoorWelcome();
            _4F4 = 3;
        }
        break;
    case 3:
        if (mfModelMainIsAnimEnd()) {
            mfEffectReleaseDoorRing();
            mfModelMainSetAnim(T_ANIM_LIST[4]);
            mfModelMainStart(true);
            _4F4 = 0;
        }
        break;
    case 4:
        _1128.advanceIfNotEnd();
        if (_1128.isEnd()) {
            mBoard.setAnimByName("NewRelease");
            mBoard.start(false);
            _4F4 = 5;
        }
        break;
    case 5:
        if (mfModelMainIsAnimEnd()) {
            mBoard.setAnimByName("New");
            mBoard.start(true);
            _4F4 = 3;
        }
        break;
    }
    if (_5D5) {
        hero::Hero& hero = mComponent.heroManager().getMainPlayer();
        if (!hero.stateChecker().is_44()) {
            hero.stateChanger().setNextState<hero::gimmick::StateEnterChallengeDoor, hero::Hero*, Vector2, ChallengeKind, bool>(
                &hero, mResult.mPos, mResult.mKind, true);
            _5D5 = false;
            _4F4 = 6;
        }
    }
    MintChallengeDoor::Register(*this);
    mRunner.execute();
    MintChallengeDoor::Unregister(*this);
}

bool ChallengeDoor::searchAir(const Vector2& pos) const {
    if (_4F4 == 6) {
        return true;
    }
    if (!_5D4) {
        return false;
    }
    if (Math::Abs(pos.x - mResult.mPos.x) < 2.0f && pos.y > mResult.mPos.y - 1.0f && pos.y < 2.0f + mResult.mPos.y) {
        return true;
    }
    return false;
}

bool ChallengeDoor::search(const Vector2& pos) const {
    if (_4F4 == 6) {
        return true;
    }
    if (!_5D4) {
        return false;
    }
    if (Math::Abs(pos.x - mResult.mPos.x) < 1.0f && pos.y > mResult.mPos.y - 0.1f && pos.y < 0.1f + mResult.mPos.y) {
        return true;
    }
    return false;
}

Result ChallengeDoor::check(const Vector2& pos) const {
    Result result;
    if (!_5D5 && search(pos)) {
        result = mResult;
    }
    return result;
}

void ChallengeDoor::startCameraDemo() {
    mRunner.setEntryPoint("Scn.Step.Gimmick.ChallengeDoor.Common.Enter");
}

void ChallengeDoor::setToEnter() {
    _5D5 = true;
}

bool ChallengeDoor::isLeaveDoor() const {
    ChallengeKind kind = mResult.mKind;
    if (ChallengeKindUtil::IsChallengePortal(mComponent.context().mHero._0)) {
        return kind == ChallengeKindUtil::PortalToChallengeKind(mComponent.context().mHero._0);
    }
    return false;
}

void ChallengeDoor::startLeaveDemo() {
    mRunner.setEntryPoint("Scn.Step.Gimmick.ChallengeDoor.Common.Leave");
}

void ChallengeDoor::unlock() {
    mfModelMainSetAnim(T_ANIM_LIST[1]);
    mfModelMainStart(false);
    _1128.reset(50);
    mSe.start(0x4DE);
    _1130.reset(20);
    mfEffectSetupDoorRelease();
    _4F4 = 4;
    _5D4 = true;
}

// Reads the hidden object dcpl_0x4f6b02d9 (docs/metafortress.md) and hangs if it does not decode to zero.
// The fetch names r17 and moves it to `w`: the compiler gives `w` that register and drops the move, and with
// r17 taken there is no register left for `this`, which lives on the stack.
#define MF_FUNCTION isUnlockEnd__Q53scn4step7gimmick13challengedoor13ChallengeDoorCFv
bool ChallengeDoor::isUnlockEnd() const {
    volatile u32 word0;
    volatile u32 word1;
    volatile u32 word2;
    volatile u32 word3;
    register u32 w;
    u32 t;
    u32 v;
    u32 b1;
    u32 b2;
    u32 b3;
    u32 b4;
    u32 b5;

    asm {
        bl      after1
        opword  0x0462F890
        opword  MF_WORD(0x28)
        opword  0xB7C3A00A
        opword  0x521A250F
    after1:
        mflr    r27
        lwz     r29, 0x4(r27)
        stw     r29, word0
        bl      after2
        opword  0x5887E980
        opword  MF_WORD(0x48)
    after2:
        mflr    r27
        lwz     r29, 0x4(r27)
        stw     r29, word1
        bl      after3
        opword  0x9C6C7D93
        opword  MF_WORD(0x60)
        opword  0x003EA080
        opword  MF_WORD(0x68)
        opword  0x95DD7803
        opword  0x7C806D81
    after3:
        mflr    r21
        lwz     r17, 0x4(r21)
        lwz     r24, 0xc(r21)
        stw     r24, word3
        stw     r17, word2
        mr      w, r17
    }
    v = (((w >> 2) | (w << 30)) & 0xCCCCCCCC) | (((w << 2) | (w >> 30)) & 0x33333333);
    v = v + 0x0C220000;
    b1 = v + 0x2201;
    v = ((b1 >> 20) ^ (b1 >> 2)) & 0xFFF;
    v = b1 ^ ((v << 20) | (v << 2));
    b2 = (v >> 22) | (v << 10);
    v = (((b2 >> 2) | (b2 << 30)) & 0x99999999) | (((b2 << 2) | (b2 >> 30)) & 0x66666666);
    v ^= 0xACBB49F6;
    t = (v >> 16) | (v << 16);
    v = (t & 0x60549FAB) | (t & 0x9FAB6054);
    v += 0x606AD87D;
    v = (v << 26) | (v >> 6);
    v ^= 0x9619EDD6;
    t = ((v >> 17) ^ (v >> 7)) & 0xF;
    v = v ^ ((t << 17) | (t << 7));
    v ^= 0xA3A270F5;
    v = (((v >> 4) | (v << 28)) & 0x3C3C3C3C) | (((v << 4) | (v >> 28)) & 0xC3C3C3C3);
    v += 0x2B796F8D;
    v = (((v >> 2) | (v << 30)) & 0x99999999) | (((v << 2) | (v >> 30)) & 0x66666666);
    b3 = *(u32*)v;
    v = ((b3 >> 24) ^ (b3 >> 4)) & 0xFF;
    v = b3 ^ ((v << 24) | (v << 4));
    b4 = ~v;
    v = ((b4 >> 15) ^ (b4 >> 1)) & 0x3FFF;
    v = b4 ^ ((v << 15) | (v << 1));
    b5 = (((v >> 2) | (v << 30)) & 0x99999999) | (((v << 2) | (v >> 30)) & 0x66666666);
    b5 += 0x577DADE3;
    b5 = (b5 >> 28) | (b5 << 4);
    b5 -= 0x777A887D;
    b5 = (((b5 >> 4) | (b5 << 28)) & 0xD2D2D2D2) | (((b5 << 4) | (b5 >> 28)) & 0x2D2D2D2D);
    b5 = (((b5 >> 2) | (b5 << 30)) & 0x99999999) | (((b5 << 2) | (b5 >> 30)) & 0x66666666);
    b5 ^= 0xFBF4D7FB;
    b1 = ((b5 >> 2) | (b5 << 30)) & 0xCCCCCCCC;
    b5 = b1 | (((b5 << 2) | (b5 >> 30)) & 0x33333333);
    b5 = (((b5 >> 4) | (b5 << 28)) & 0x3C3C3C3C) | (((b5 << 4) | (b5 >> 28)) & 0xC3C3C3C3);
    b5 -= 0x4417F7D3;
    b5 = (((b5 >> 4) | (b5 << 28)) & 0x2D2D2D2D) | (((b5 << 4) | (b5 >> 28)) & 0xD2D2D2D2);
    b5 = (b5 >> 10) | (b5 << 22);
    if (b5 != 0) {
        volatile u32 anchor;
        volatile u32 offset;
        volatile u32 response;
        volatile u32 key;

        asm {
            bl      after4
            opword  MF_WORD(0x36C)
            opword  0x948E3F80
            opword  0xEF5AAF0E
            opword  MF_WORD(0x378)
        after4:
            mflr    r18
            lwz     r19, 0xc(r18)
            stw     r19, key
            lwz     r19, 0x0(r18)
            stw     r18, anchor
            stw     r19, offset
        }
        response = offset ^ key;
        response = response + anchor;
        asm {
            lwz     r21, response
            mtlr    r21
            blr
        }
    }
    bool isEnd = false;
    if (_4F4 != 5 && _4F4 != 4) {
        isEnd = true;
    }
    return isEnd;
}
#undef MF_FUNCTION

void ChallengeDoor::setZoom(f32 zoom, f32 frame) {
    Vector3 pos = mComponent.heroManager().getMainPlayerPos();
    Vector2 center(pos.x, 1.0f + pos.y);
    mComponent.cameraController().setZoom(center, zoom, frame, true, camera::ZOOM_PRIORITY_1);
}

void ChallengeDoor::updateZoom(u32 handle, f32 zoom) {
    Vector3 pos = mComponent.heroManager().getMainPlayerPos();
    Vector2 center(pos.x, 1.0f + pos.y);
    mComponent.cameraController().updateZoom(handle, center, zoom);
}

void ChallengeDoor::unsetZoom(u32 handle) {
    mComponent.cameraController().unsetZoom(handle);
}

void ChallengeDoor::mfSeRequest(bool isLong) {
    if (isLong) {
        mSe.start(0x4DB);
    } else {
        mSe.start(0x4DA);
    }
    _5D6 = true;
}

void ChallengeDoor::mfSeStop() {
    if (_5D6) {
        mSe.stop();
    }
}

void ChallengeDoor::mfModelMainSetAnim(const char* name) {
    mModelMain.setAnim(0, mResFile, name);
}

#define MF_FUNCTION mfModelMainStart__Q53scn4step7gimmick13challengedoor13ChallengeDoorFb
void ChallengeDoor::mfModelMainStart(bool doLoop) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 u;
    u32 t;
    u32 w;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0x16D5CB01
        opword  0x80901593
        opword  MF_WORD(0x34)
        opword  0xF491FD91
        opword  0x7CC9A080
    after1:
        mflr    r23
        lwz     r18, 0x0(r23)
        add     r18, r18, r23
        lwz     r17, 0xc(r23)
        stw     r18, start
        add     r17, r17, r18
        stw     r17, end
    }
    word = start;
    last = end;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0x1CA78F85
    after2:
        mflr    r30
        lwz     r18, 0x0(r30)
        stw     r18, expected
    }
    hash = 0xC5;
    for (;;) {
        if (word == last) {
            break;
        }
        w = *(u16*)word;
        u = hash << 4;
        t = hash >> 28;
        t = u ^ t;
        hash = w ^ t;
        word += 2;
    }
    t = expected;
    u = hash & ~t;
    t = expected;
    t = t & ~hash;
    t = u | t;
    u = __cntlzw(t);
    t = u >> 5;
    u = t * 40;
    hash = t + u;
    if (hash == 0) {
        volatile u32 offset;
        volatile u32 response;
        volatile u32 anchor;
        volatile u32 key;

        asm {
            bl      after3
            opword  0x490B8C02
            opword  0x74E50880
            opword  MF_WORD(0xDC)
        after3:
            mflr    r17
            lwz     r16, 0x8(r17)
            stw     r16, -0x4(r1)
            stw     r17, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r17, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x100)
            opword  MF_WORD(0x104)
        after4:
            mflr    r21
            lwz     r30, 0x0(r21)
            lwz     r17, 0x4(r21)
            stw     r17, key
            stw     r30, offset
            stw     r21, anchor
        }
        key = 0;
        response = offset;
        response = response + anchor;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    } else {
        mModelMain.anim(0).start(doLoop);
    }
}
#undef MF_FUNCTION

bool ChallengeDoor::mfModelMainIsAnimEnd() {
    return mModelMain.anim(0).isAnimEnd();
}

void ChallengeDoor::mfUpdateCover() {
    Vector3 trans = mModelMain.model().nodeByName("IconConstL").worldTrans();
    mModelMain.model().nodeByName("IconConstL").worldTrans();
    Vector3 scale = mModelMain.model().nodeByName("IconConstL").worldScale();
    trans.z += -0.1f;
    mIcon.setTrans(trans);
    mIcon.setScale(scale);
}

void ChallengeDoor::mfEffectSetupDoorRing() {
    Vector3 pos = mPos.toVector3();
    pos.z = -2.5f;
    mEffectDoorRing.requestP(static_cast<effect::Kind>(0x4D2), pos, false);
}

void ChallengeDoor::mfEffectReleaseDoorRing() {
    mEffectDoorRing.release();
}

#define MF_FUNCTION mfEffectSetupDoorRelease__Q53scn4step7gimmick13challengedoor13ChallengeDoorFv
void ChallengeDoor::mfEffectSetupDoorRelease() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xD696AEC3
    after1:
        mflr    r17
        lwz     r30, 0x0(r17)
        stw     r30, expected
    }
    hash = 0xBF;
    asm {
        bl      after2
        opword  MF_WORD(0x40)
        opword  0x2E40FC02
        opword  MF_WORD(0x48)
    after2:
        mflr    r18
        lwz     r30, 0x0(r18)
        add     r30, r30, r18
        stw     r30, start
        lwz     r28, 0x8(r18)
        add     r30, r30, r28
        stw     r30, end
    }
    word = start;
    last = end;
    for (; word != last; word += 2) {
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash -= expected;
    if (hash != 0) {
        volatile u32 offset;
        volatile u32 anchor;
        volatile u32 response;
        volatile u32 key;

        asm {
            bl      after3
            opword  MF_WORD(0xB8)
        after3:
            mflr    r14
            addi    r19, r14, 0x10
            mtlr    r19
            lwz     r25, 0x0(r14)
            stw     r25, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r14, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0xE0)
            opword  0xE5498C01
            opword  MF_WORD(0xE8)
        after4:
            mflr    r18
            lwz     r30, 0x0(r18)
            stw     r18, anchor
            lwz     r25, 0x8(r18)
            stw     r30, offset
            stw     r25, key
        }
        offset = offset - 0xC4;
        key = 0;
        response = offset;
        response = response + anchor;
        asm {
            lwz     r21, response
            mtlr    r21
            blr
        }
    } else {
        mEffectDoorRelease.requestP(static_cast<effect::Kind>(0x4D1), mPos.toVector3(), false);
    }
}
#undef MF_FUNCTION

void ChallengeDoor::mfEffectSetupDoorWelcome() {
    mEffectDoorWelcome.requestP(static_cast<effect::Kind>(0x4D3), mPos.toVector3(), false);
}

void ChallengeDoor::mfEffectReleaseDoorWelcome() {
    mEffectDoorWelcome.release();
}

}}}}  // namespace scn::step::gimmick::challengedoor

// One of the hidden objects of the copy protection (docs/metafortress.md). Functions of other units reach it
// through an address they decode from inline data.
u32 dcpl_0xd622c6e3_dcpl0_mfort6317_[4] = { 0xEC2BCBF9, 0x34B75ABC, 0xCC232475, 0xA6B4B42B };
