// TODO: requestBreakEffect calls hel::math::Vector3's copy constructor, the unit's only visible use of it. The
// second use that keeps it a call is not written, so the unit takes the declaration.
#define HEL_MATH_VECTOR3_COPY_CONSTRUCTOR_OUT_OF_LINE

#include "scn/step/gimmick/block/Block.h"

#include "app/Application.h"
#include "effect/Requestor.h"
#include "effect/detail/RequestArg.h"
#include "g3d/ModelAnimAccessor.h"
#include "g3d/ModelBufferOption.h"
#include "g3d/ModelContext.h"
#include "g3d/ResModelContext.h"
#include "hel/common/FixedStringIN.h"
#include "hel/math/Matrix34.h"
#include "hel/math/Random.h"
#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "mcoll/LandManager.h"
#include "metafortress.h"
#include "scn/step/Component.h"
#include "scn/step/gimmick/Effect.h"
#include "scn/step/gimmick/block/BlockInfo.h"
#include "scn/step/gimmick/block/BlockResFiles.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/spstop/Manager.h"

using app::Application;
using g3d::ModelBufferOption;
using g3d::ModelContext;
using g3d::ResModelContext;
using g3d::Root;
using hel::common::FixedStringIN;
using hel::math::Matrix34;
using hel::math::Vector2;
using hel::math::Vector3;
using util::ObjRefHandle;
using util::SIntAABBox;

namespace scn {
namespace step {
namespace gimmick {
namespace block {

namespace {

inline bool t_isHiddenBlock(map::BinGmkBlockKind kind) {
    switch (kind) {
    case 0x14:
    case 0x15:
        return true;
    default:
        return false;
    }
}

inline bool t_isChainBombBlock(map::BinGmkBlockKind kind) {
    switch (kind) {
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
        return true;
    default:
        return false;
    }
}

inline bool t_isChainBlock(map::BinGmkBlockKind kind) {
    switch (kind) {
    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x25:
    case 0x26:
    case 0x27:
    case 0x28:
        return true;
    default:
        return false;
    }
}

}

// TODO: name. The kinds whose model has its own waiting animation.
inline bool Block::mfIsAnimBlock() const {
    return mKind == 0x20 || mKind == 0x21 || mKind == 0x22 || mKind == 0x23 || mKind == 0x24 || mKind == 0x27 || mKind == 0x28 ||
           mKind == 0x29 || mKind == 0x2F || mKind == 0x35 || mKind == 0x36 || mKind == 0x3B;
}

inline bool Block::mfIsDefaultBufferOption() const {
    return isLandBlock() || mfIsAnimBlock();
}

Block::Block(Component& component, mem::IAllocator& allocator, mcoll::LandManager& landManager, BlockResFiles& resFiles,
             map::BinGmkBlockKind kind, const GridPos& pos, Effect& effect, ParamAccessor<Param>& param)
    : mComponent(component)
    , mLandManager(landManager)
    , mKind(kind)
    , mPos(pos)
    , mResFiles(resFiles)
    , mResFile(resFiles.get(kind))
    , mModel(ModelContext(
          ResModelContext(mResFile, resFiles.entryName(kind)),
          mfIsDefaultBufferOption() ? ModelContext::DefaultModelBufferOption() : ModelBufferOption(), 0,
          ModelContext::DefaultNumView(), allocator, false))
    , mEffect(effect)
    , mSE()
    , _260(false)
    , _261(false)
    , _262(false)
    , _263(true)
    , _264(true)
    , mState(0)
    , _26C()
    , _274()
    , _27C()
    , _284()
    , mParam(param) {
    for (int i = 0; i < 4; i++) {
        mHitIds[i] = 0;
    }
    if (t_isHiddenBlock(mKind)) {
        _263 = false;
        _264 = false;
    }
    Vector2 worldPos = pos.toWorldPos();
    mModel.setModelRTMtx(Matrix34::CreateTrans(Vector3(worldPos.x, worldPos.y, 0.0f)));
    startWaitAnim();
}

s32 Block::width() const {
    SIntAABBox box = aabb();
    return box.mMaxX - box.mMinX;
}

s32 Block::height() const {
    SIntAABBox box = aabb();
    return box.mMaxY - box.mMinY;
}

SIntAABBox Block::aabb() const {
    switch (mKind) {
    case 2:
    case 3:
    case 7:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 23:
    case 35:
    case 41:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 50:
    case 56:
    case 59:
        return SIntAABBox(0, 0, 2, 2);
    case 5:
    case 53:
    case 58:
        return SIntAABBox(0, 0, 3, 3);
    case 22:
    case 51:
    case 57:
        return SIntAABBox(0, 0, 4, 4);
    case 24:
        return SIntAABBox(0, 0, 3, 2);
    case 25:
        return SIntAABBox(0, -1, 3, 2);
    case 26:
        return SIntAABBox(0, 0, 3, 3);
    case 27:
        return SIntAABBox(0, 0, 3, 1);
    case 28:
        return SIntAABBox(0, 0, 1, 3);
    case 29:
        return SIntAABBox(0, 0, 4, 4);
    case 31:
        return SIntAABBox(0, 0, 3, 3);
    case 49:
        return SIntAABBox(0, 0, 1, 2);
    case 52:
        return SIntAABBox(0, 0, 4, 2);
    default:
        return SIntAABBox(0, 0, 1, 1);
    }
}

bool Block::isExistBlock(s32 x, s32 y) const {
    SIntAABBox box = aabb();
    if (!box.isInclude(x, y)) {
        return false;
    }
    switch (mKind) {
    case 0x18:
        if (x == 0 && y == 1) {
            return false;
        }
        if (x == 2 && y == 1) {
            return false;
        }
        return true;
    case 0x19:
        if (x == 0 && y == -1) {
            return false;
        }
        if (x == 2 && y == -1) {
            return false;
        }
        return true;
    case 0x1A:
        if (x == 0 && y == 1) {
            return false;
        }
        if (x == 0 && y == 2) {
            return false;
        }
        if (x == 1 && y == 2) {
            return false;
        }
        return true;
    case 0x1D:
        if (x == 0 && y == 1) {
            return false;
        }
        if (x == 0 && y == 3) {
            return false;
        }
        if (x == 3 && y == 1) {
            return false;
        }
        if (x == 3 && y == 3) {
            return false;
        }
        return true;
    case 0x1F:
        if (x == 1 && y == 2) {
            return false;
        }
        if (x == 2 && y == 1) {
            return false;
        }
        if (x == 2 && y == 2) {
            return false;
        }
        return true;
    }
    return true;
}

bool Block::canVacuum(bool flag) const {
    if (mKind == 0) {
        return true;
    }
    return isHeavyBlock() ? flag : false;
}

bool Block::canHit() const {
    switch (mKind) {
    case 0:
        return true;
    case 18:
        return true;
    case 30:
        return true;
    case 32:
        return _274.isEnd();
    case 34:
        return true;
    case 36:
        return true;
    case 41:
    case 53:
        return true;
    case 54:
    case 59:
        return true;
    default:
        return isLandBlock();
    }
}

#define MF_FUNCTION canBreak__Q53scn4step7gimmick5block5BlockCFbbbbbb
bool Block::canBreak(bool a, bool b, bool c, bool d, bool e, bool f) const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 anchor;
    volatile u32 addend;
    volatile u32 response;
    u32 hash;
    u32 word;
    u32 tail;

    asm {
        bl      after1
        opword  MF_WORD(0x3C)
        opword  0x23D06800
        opword  0x29FB0303
        opword  MF_WORD(0x48)
    after1:
        mflr    r26
        lwz     r19, 0x0(r26)
        lwz     r20, 0xc(r26)
        add     r19, r19, r26
        add     r20, r20, r19
        stw     r19, start
        stw     r20, end
    }
    word = start;
    tail = end;
    hash = 0;
    for (; word != tail; word += 2) {
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA0)
        opword  0x85156DBC
    after2:
        mflr    r27
        lwz     r18, 0x0(r27)
        stw     r18, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash == expected) {
        switch (mKind) {
        case 0:
            if (c) {
                return false;
            }
            return true;
        case 18:
            if (c) {
                return false;
            }
            return true;
        case 30:
            if (c) {
                return false;
            }
            return true;
        case 32:
            if (mState == 1) {
                if (c) {
                    return false;
                }
                return true;
            }
            if (b || c) {
                return true;
            }
            return false;
        case 36:
            if (e) {
                return true;
            }
            return false;
        case 34:
            if (d) {
                return true;
            }
            return false;
        case 41:
        case 53:
            if (f) {
                return true;
            }
            return false;
        case 54:
        case 59:
            return true;
        default:
            if (isLandBlock()) {
                return a;
            }
            return false;
        }
    }
    asm {
        bl      after3
        opword  MF_WORD(0x204)
        opword  0x0C206893
    after3:
        mflr    r14
        addi    r24, r14, 0x14
        mtlr    r24
        lwz     r22, 0x0(r14)
        stw     r22, -0x4(r1)
        stw     r24, 0x0(r1)
        stw     r14, 0x4(r1)
        blrl
        bl      after4
        opword  MF_WORD(0x230)
        opword  0x54BCD792
        opword  MF_WORD(0x238)
    after4:
        mflr    r22
        stw     r22, anchor
        lwz     r29, 0x0(r22)
        stw     r29, offset
        lwz     r24, 0x8(r22)
        stw     r24, addend
    }
    offset = offset + 0x8D;
    response = offset + addend;
    response = response + anchor;
    asm {
        lwz     r19, response
        mtlr    r19
        blr
    }
}
#undef MF_FUNCTION

bool Block::onVacuum() {
    if (!isHeavyBlock()) {
        return false;
    }
    bool isFirst = !_261;
    _260 = true;
    _261 = true;
    if (isFirst) {
        if (mModel.tryToSetAnim(mResFile, FixedStringIN<char, 40>::FromFormat("%sWaitVacuum", mResFiles.entryName(mKind)))) {
            mModel.anim().setFrame(static_cast<f32>(Application::Object().random().rand(mModel.anim().totalFrame())));
            mModel.start(true);
        }
    }
    return isFirst;
}

bool Block::onHit(u64 attackId, u64 ownerId) {
    if (mKind != 0x22 && mKind != 0x29 && mKind != 0x35) {
        return false;
    }
    bool isSame = false;
    ObjRefHandle<hero::Hero> handle = mComponent.heroManager().searchHeroFromObjCollOwnerID(ownerId);
    hero::Hero* hero = handle.operator->();
    if (hero == 0) {
        return false;
    }
    u32 chan = hero->padChan();
    if (mHitIds[chan] == attackId) {
        isSame = true;
    } else {
        mHitIds[chan] = attackId;
    }
    bool result = !_262 && !isSame;
    _260 = true;
    _262 = true;
    return result;
}

#define MF_FUNCTION onBroken__Q53scn4step7gimmick5block5BlockFv
void Block::onBroken() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 hash;
    u32 last;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  0xE74AC302
        opword  0x80864E90
        opword  MF_WORD(0x30)
        opword  0x8CF22F80
        opword  0xD7BC4C0D
        opword  MF_WORD(0x3C)
        opword  0x5EB8D40B
    after1:
        mflr    r19
        lwz     r15, 0x8(r19)
        lwz     r20, 0x14(r19)
        stw     r20, start
        stw     r15, end
    }
    limit = end - start + 1;
    last = end;
    mEffect.release();
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash += *(u16*)(last - 1 - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xAC)
        opword  0x8D458AC2
    after2:
        mflr    r29
        lwz     r22, 0x0(r29)
        stw     r22, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash - expected == 0) {
        if (mKind == 0x20) {
            if (mState == 0) {
                mModel.setAnim(mResFile, "WaitCool");
                mModel.start(true);
                u32 x = mPos.x();
                u32 y = mPos.y();
                mLandManager.setIsExistFireBlock(x, y, false);
                mLandManager.setIsExistGimmickBlock(x, y, true);
                _274.reset(0x14);
                mState = 1;
            } else {
                mState = 4;
            }
        } else {
            mState = 4;
        }
    } else {
        volatile u32 response;
        volatile u32 offset;
        volatile u32 addend;
        volatile u32 anchor;

        asm {
            bl      after3
            opword  0xD582280F
            opword  0x301CC292
            opword  0xF9D97609
            opword  MF_WORD(0x188)
        after3:
            mflr    r30
            lwz     r26, 0xc(r30)
            stw     r26, -0x4(r1)
            stw     r30, 0x0(r1)
            stw     r26, -0x4(r1)
            stw     r30, -0x8(r1)
            mtlr    r26
            bl      after4
            opword  MF_WORD(0x1AC)
            opword  0x68481A81
            opword  0x14C89680
            opword  MF_WORD(0x1B8)
        after4:
            mflr    r18
            stw     r18, anchor
            lwz     r20, 0x0(r18)
            stw     r20, offset
            lwz     r29, 0xc(r18)
            stw     r29, addend
        }
        response = offset + addend;
        response = response + anchor;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    }
}
#undef MF_FUNCTION

void Block::onActEnd() {
    _274.advanceIfNotEnd();
    if (!_260) {
        if (_261) {
            _261 = false;
            if (!isLandBlock()) {
                startWaitAnim();
            }
        }
        if (_262) {
            _262 = false;
        }
    }
    _260 = false;
    if (!isLandBlock() && mComponent.superStopManager().isStopped()) {
        return;
    }
    if (mState == 2) {
        _26C.advanceIfNotEnd();
    }
    if (!mModel.wasSetAnim()) {
        return;
    }
    mModel.updateFrame();
    if (mState == 5) {
        _284.advanceIfNotEnd();
        if (_284.isEnd()) {
            _27C.reset(mParam.obj()._4);
            mState = 6;
            mModel.setAnim(mResFile, "BigShake");
            mModel.start(true);
            if (mKind == 0x21) {
                mEffect.requestP(static_cast<effect::Kind>(0x1D5), mPos.toWorldPos().toVector3(), false);
            }
        }
    } else if (mState == 6) {
        _27C.advanceIfNotEnd();
        if (_27C.isEnd()) {
            mState = 7;
            mModel.setAnim(mResFile, "Crumble");
            mModel.start(false);
            effect::Kind kind = mKind == 0x21 ? static_cast<effect::Kind>(0x1D3) : static_cast<effect::Kind>(0x1D4);
            mEffect.requestP(kind, mPos.toWorldPos().toVector3(), false);
            mSE.start(0x524);
            setMapColl(mPos.x(), mPos.y(), false);
        }
    } else if (mState == 7) {
        if (mModel.isAnimEnd()) {
            mState = 4;
        }
    }
}

void Block::registerToRoot(Root& root) {
    if (_263) {
        mModel.registerToRoot(root);
    }
}

void Block::startWaitAnim() {
    switch (mKind) {
    case 0x20:
        mModel.setAnim(mResFile, "Wait");
        mModel.start(true);
        break;
    case 0x23:
        mModel.setAnim(mResFile, "Wait");
        mModel.start(true);
        break;
    case 0x22:
        mModel.setAnim(mResFile, "Wait");
        mModel.start(true);
        break;
    case 0x24:
        mModel.setAnim(mResFile, "Wait");
        mModel.start(true);
        break;
    case 0x27:
        mModel.setAnim(mResFile, "Wait");
        mModel.start(true);
        break;
    case 0x28:
        mModel.setAnim(mResFile, "Wait");
        mModel.start(true);
        break;
    case 0x29:
        mModel.setAnim(mResFile, "Wait");
        mModel.start(true);
        break;
    case 0x35:
        mModel.setAnim(mResFile, "TopL3x3Wait");
        mModel.start(true);
        break;
    case 0x36:
        mModel.setAnim(mResFile, "Wait");
        mModel.start(true);
        break;
    case 0x3B:
        mModel.setAnim(mResFile, "Wait");
        mModel.start(true);
        break;
    default:
        if (mModel.tryToSetAnim(mResFile, mResFiles.entryName(mKind))) {
            mModel.start(true);
        }
        break;
    }
}

bool Block::isLandBlock() const {
    switch (mKind) {
    case 1:
    case 3:
    case 6:
    case 7:
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 23:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 55:
    case 56:
    case 57:
    case 58:
        return true;
    case 35:
        return true;
    default:
        return false;
    }
}

bool Block::isHeavyBlock() const {
    switch (mKind) {
    case 0x18:
    case 0x19:
    case 0x1A:
    case 0x1B:
    case 0x1C:
    case 0x1D:
    case 4:
    case 5:
    case 2:
    case 0x16:
    case 0x1F:
        return true;
    default:
        return false;
    }
}

#define MF_FUNCTION isChainBlock__Q53scn4step7gimmick5block5BlockCFv
bool Block::isChainBlock() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 hash;
    u32 tail;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x48C45E80
        opword  MF_WORD(0x2C)
        opword  0xB3E47900
    after1:
        mflr    r19
        lwz     r23, 0x8(r19)
        lwz     r29, 0x0(r19)
        add     r29, r29, r19
        stw     r29, start
        add     r23, r23, r29
        stw     r23, end
    }
    word = start;
    tail = end;
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x60)
        opword  0xF49E50D9
    after2:
        mflr    r17
        lwz     r27, 0x0(r17)
        stw     r27, expected
    }
    word -= 2;
    while (word != tail - 2) {
        word += 2;
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash -= expected;
    hash = __cntlzw(hash);
    word = hash >> 5;
    hash = word | word << 5;
    if (hash == 0) {
        volatile u32 anchor;
        volatile u32 unused;
        volatile u32 response;
        volatile u32 offset;

        asm {
            bl      after3
            opword  0xB82CE791
            opword  MF_WORD(0xE4)
        after3:
            mflr    r29
            lwz     r14, 0x4(r29)
            stw     r14, -0x4(r1)
            stw     r29, 0x0(r1)
            stw     r14, -0x4(r1)
            stw     r29, -0x8(r1)
            mtlr    r14
            bl      after4
            opword  MF_WORD(0x108)
            opword  MF_WORD(0x10C)
        after4:
            mflr    r27
            stw     r27, anchor
            lwz     r20, 0x0(r27)
            stw     r20, offset
            lwz     r18, 0x4(r27)
            stw     r18, unused
        }
        offset = offset + 0xA8;
        unused = 0;
        response = offset;
        response = response + anchor;
        asm {
            lwz     r28, response
            mtlr    r28
            blr
        }
    } else {
        switch (mKind) {
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
            return true;
        default:
            return false;
        }
    }
}
#undef MF_FUNCTION

bool Block::canChainBreak() const {
    if (mState != 0) {
        return false;
    }
    return t_isChainBlock(mKind);
}

void Block::startChainBreak() {
    u32 frame = mParam.obj()._0;
    if (t_isChainBombBlock(mKind)) {
        frame = 0;
    }
    startChainBreak(frame);
}

void Block::startChainBreak(u32 frame) {
    mState = 2;
    _26C.reset(frame);
}

bool Block::isEndChainBreak() const {
    bool isEnd = false;
    if (mState == 2 && _26C.isEnd()) {
        isEnd = true;
    }
    return isEnd;
}

void Block::onChainBreak() {
    if (mKind == 0x15) {
        _263 = true;
        mState = 3;
        _264 = true;
        mLandManager.setIsExistGimmickBlock(mPos.x(), mPos.y(), true);
    } else {
        mState = 4;
    }
}

#define MF_FUNCTION isRemove__Q53scn4step7gimmick5block5BlockCFv
bool Block::isRemove() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 unused;
    volatile u32 anchor;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xD7B2AAC7
    after1:
        mflr    r30
        lwz     r20, 0x0(r30)
        stw     r20, expected
    }
    hash = 0x811C9DDB;
    asm {
        bl      after2
        opword  0x383FE180
        opword  MF_WORD(0x48)
        opword  MF_WORD(0x4C)
    after2:
        mflr    r16
        lwz     r27, 0x8(r16)
        lwz     r24, 0x4(r16)
        add     r27, r24, r27
        stw     r27, end
        stw     r24, start
    }
    i = 1;
    base = start;
    limit = end - base + 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000193;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash = expected ^ hash;
    hash |= hash << 4;
    if (hash == 0) {
        return mState == 4;
    }
    asm {
        bl      after3
        opword  MF_WORD(0xFC)
    after3:
        mflr    r23
        lwz     r21, 0x0(r23)
        stw     r21, -0x4(r1)
        stw     r23, 0x0(r1)
        stw     r21, -0x4(r1)
        stw     r23, -0x8(r1)
        mtlr    r21
        bl      after4
        opword  MF_WORD(0x120)
        opword  MF_WORD(0x124)
    after4:
        mflr    r19
        lwz     r22, 0x4(r19)
        stw     r22, unused
        lwz     r22, 0x0(r19)
        stw     r19, anchor
        stw     r22, offset
    }
    offset = offset - 0x3B;
    unused = 0;
    response = offset;
    response = response + anchor;
    asm {
        lwz     r28, response
        mtlr    r28
        blr
    }
}
#undef MF_FUNCTION

void Block::setMapColl(u32 x, u32 y, bool isExist) {
    switch (mKind) {
    case 32:
        if (mState == 0) {
            mLandManager.setIsExistFireBlock(x, y, isExist);
        } else {
            mLandManager.setIsExistGimmickBlock(x, y, isExist);
        }
        break;
    case 34:
        mLandManager.setIsExistIronBlockLand(x, y, isExist);
        break;
    case 35:
        mLandManager.setIsExistFireBlock(x, y, isExist);
        break;
    case 36:
    case 39:
    case 40:
        mLandManager.setIsExistIceBlock(x, y, isExist);
        break;
    case 54:
    case 59:
        mLandManager.setIsExistFireBlock(x, y, isExist);
        break;
    case 41:
    case 53:
        mLandManager.setIsExistIronBlockLand(x, y, isExist);
        break;
    case 47:
        mLandManager.setIsExistIronBlockLand(x, y, isExist);
        break;
    case 37:
    case 38:
        mLandManager.setIsExistSnowBlockLand(x, y, isExist);
        break;
    case 3:
    case 55:
    case 56:
    case 57:
        mLandManager.setIsExistGrassBlockLand(x, y, isExist);
        break;
    case 1:
    case 6:
    case 7:
    case 48:
    case 49:
    case 50:
    case 51:
    case 52:
    case 58:
        mLandManager.setIsExistStoneBlockLand(x, y, isExist);
        break;
    case 8:
    case 9:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 23:
    case 42:
    case 43:
    case 44:
    case 45:
    case 46:
        mLandManager.setIsExistWoodBlockLand(x, y, isExist);
        break;
    default:
        if (_264) {
            mLandManager.setIsExistGimmickBlock(x, y, isExist);
        }
        break;
    }
}

void Block::requestBreakEffect(const BlockEffRequestInfo::Info& info, const BlockInfo& blockInfo, ::effect::Requestor& requestor) {
    if (info._0 == 0xFFFFFFFF) {
        return;
    }
    ::effect::detail::RequestArgOption option = ::effect::detail::RequestArgOption::CreateP(blockInfo.gridPos().toWorldPos().toVector3());
    option.setScale(info._8);
    option.setOffset(Vector3(info._10));
    if (mKind == 0x20) {
        if (isRemove()) {
            ::effect::detail::RequestArgOption removeOption =
                ::effect::detail::RequestArgOption::CreateP(blockInfo.gridPos().toWorldPos().toVector3());
            removeOption.setScale(info._C);
            removeOption.setOffset(Vector3(info._1C));
            requestor.request(::effect::detail::RequestArg(info._4, removeOption));
        } else {
            requestor.request(::effect::detail::RequestArg(info._0, option));
        }
    } else {
        requestor.request(::effect::detail::RequestArg(info._0, option));
    }
}

#define MF_FUNCTION getBreakSE__Q53scn4step7gimmick5block5BlockCFv
u32 Block::getBreakSE() const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 base;
    u32 size;
    u32 tail;
    u32 last;
    u32 i;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0xE83C9F91
        opword  0x7BAEB00E
        opword  MF_WORD(0x28)
        opword  0xEB664F0B
        opword  0x440F2691
    after1:
        mflr    r25
        lwz     r18, 0x0(r25)
        lwz     r22, 0xc(r25)
        add     r18, r18, r25
        add     r22, r22, r18
        stw     r18, start
        stw     r22, end
    }
    base = start;
    size = end;
    size -= base;
    tail = end;
    hash = 0x811C9E29;
    asm {
        bl      after2
        opword  MF_WORD(0x6C)
        opword  0x80F0BE18
    after2:
        mflr    r19
        lwz     r27, 0x0(r19)
        stw     r27, expected
    }
    i = -1;
    last = tail - 1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(last - i);
        hash *= 0x010001AB;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0 || mKind == 0x20) {
        if (isRemove()) {
            return 0x29B;
        }
        return 0x512;
    }
    if (mKind == 0x24) {
        return 0x519;
    }
    if (isLandBlock()) {
        return 0x155;
    }
    return 0x29B;
}
#undef MF_FUNCTION

void Block::startCrumble() {
    if ((mKind == 0x21 || mKind == 0x2F) && mState == 0) {
        mState = 5;
        mModel.setAnim(mResFile, "Shake");
        mModel.start(true);
        _284.reset(mParam.obj()._8);
    }
}

#define MF_FUNCTION isRemainBroken__Q53scn4step7gimmick5block5BlockCFb
bool Block::isRemainBroken(bool flag) const {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 subtrahend;
    volatile u32 response;
    volatile u32 anchor;
    u32 limit;
    u32 hash;
    u32 last;
    u32 i;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x6A830605
        opword  MF_WORD(0x34)
        opword  0xF7640900
    after1:
        mflr    r29
        lwz     r15, 0x8(r29)
        stw     r15, start
        lwz     r20, 0x0(r29)
        stw     r20, end
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0x2B83BEB7
    after2:
        mflr    r18
        lwz     r23, 0x0(r18)
        stw     r23, expected
    }
    last--;
    for (; i != limit; i += 2) {
        hash += *(u16*)(last - i);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    i = expected;
    last = i & ~hash;
    i = expected;
    i = hash & ~i;
    hash = last | i;
    i = hash >> 7;
    hash = hash - i;
    if (hash == 0) {
        if (isLandBlock()) {
            return true;
        }
        if ((mKind == 0x29 || mKind == 0x35) && flag) {
            return true;
        }
        return false;
    }
    asm {
        bl      after3
        opword  0x9828C980
        opword  0x08C0BD92
        opword  0x46731F0F
        opword  MF_WORD(0x124)
    after3:
        mflr    r23
        lwz     r28, 0xc(r23)
        stw     r28, -0x4(r1)
        stw     r23, 0x0(r1)
        stw     r28, -0x4(r1)
        stw     r23, -0x8(r1)
        mtlr    r28
        bl      after4
        opword  MF_WORD(0x148)
        opword  0xF8647892
        opword  MF_WORD(0x150)
    after4:
        mflr    r27
        stw     r27, anchor
        lwz     r26, 0x0(r27)
        stw     r26, offset
        lwz     r22, 0x8(r27)
        stw     r22, subtrahend
    }
    offset = offset - 0x83;
    response = offset - subtrahend;
    response = response + anchor;
    asm {
        lwz     r23, response
        mtlr    r23
        blr
    }
}
#undef MF_FUNCTION

map::BinGmkBlockKind Block::kind() const {
    return mKind;
}

const GridPos& Block::getGridPos() const {
    return mPos;
}

}}}}  // namespace scn::step::gimmick::block
