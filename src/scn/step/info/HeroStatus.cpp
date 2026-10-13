#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS

#include "scn/step/info/HeroStatus.h"

#include "hel/math/Vector2.h"
#include "hel/math/Vector3.h"
#include "info/Util.h"
#include "lyt/LayoutContext.h"
#include "lyt/PaneAccessor.h"
#include "lyt/TagUtil.h"
#include "metafortress.h"
#include "nw4r/lyt/lyt_textBox.h"
#include "util/ObjList.h"

namespace scn {
namespace step {
namespace info {

HeroStatus::HeroStatus(mem::IAllocator& allocator, const lyt::PaneAccessor& parent, hero::Kind kind, bool flag, bool isChallenge,
                       hero::AbilityKind ability, effect::Manager& effectManager, effect::Group& effectGroup)
    : mState(0)
    , mIsPinch(false)
    , mIsInvincible(false)
    , mIsBlank(false)
    , _8(lyt::LayoutContext(isChallenge ? "step/challenge/Main" : "step/game/Main", isChallenge ? "ChallengeHeroPanel" : "HeroPanel",
                            allocator))
    , _198(lyt::LayoutContext("step/game/Main", "HeroPanelInvincible", allocator))
    , _328(lyt::LayoutContext("step/game/Main", "HeroGAEffect", allocator))
    , mLayout(lyt::LayoutContext("step/game/Main", "HeroPanelName", allocator))
    , mIcon(allocator, _8.paneByName(!isChallenge ? "HeroStatusIconN" : "AbGageN"), kind)
    , mLifeBar(allocator, _8.paneByName("HeroLifeBarN"))
    , mEffect(effectManager)
    , _12E8(0.0f)
    , _12EC(0.0f)
    , _1364(_8.pane("Bounding"))
    , mKind(kind)
    , _137C(flag)
    , _137D(isChallenge)
    , _1380(_8.pane("Ita02N"))
    , _1394(_8.pane("ItaN"))
    , _13A8(_8.pane("TransparencyN"))
    , _13BC(_8.pane("HeroGAEffectN")) {
    mEffect.changeGroup(effectGroup);
    _8.setParent(parent);
    _198.setParent(_8.pane("InvincibleN"));
    _198.rootPane().hide();
    if (!isChallenge) {
        ::info::selectHeroPaneByAction(_8, kind);
    }
    _328.setParent(_8.paneByName("HeroGAEffectN"));
    _328.setAnimByName("GetAbility");
    _328.rootPane().setVisibility(false);
    _12D8 = mLayout.pane("Name").textBox()->GetFontSize();
    _12E0 = mLayout.pane("Name2Line").textBox()->GetFontSize();
    _12E8 = mLayout.pane("Name").textBox()->GetCharSpace();
    _12EC = mLayout.pane("Name2Line").textBox()->GetCharSpace();
    if (isChallenge) {
        mLayout.rootPane().hide();
    } else {
        mLayout.setParent(_8.pane("NameN"));
    }
    abilitySet(ability);
    _8.updateMatrix();
}

void HeroStatus::updateFrame(bool flag) {
    _8.updateFrame();
    _198.updateFrame();
    _328.updateFrame();
    mLayout.updateFrame();
    mIcon.updateFrame();
    mLifeBar.updateFrame(flag);
    switch (mState) {
    case 2:
    case 3:
        if (mIcon.isAnimEnd()) {
            toIdleState();
        }
        break;
    case 4:
        if (_328.isAnimEnd()) {
            toIdleState();
        }
        break;
    }
}

bool HeroStatus::hitTest(const hel::math::Vector2& a, const hel::math::Vector2& b) {
    return ::info::hitTest(_1364, a, b);
}

void HeroStatus::setAlpha(u8 alpha) {
    _1380.setAlpha(alpha);
    _1394.setAlpha(alpha);
    _13A8.setAlpha(alpha);
    _13BC.setAlpha(alpha);
}

void HeroStatus::setBlank(bool isBlank) {
    _8.pane("Ita02N").setVisibility(!isBlank);
    _8.pane("TransparencyN").setVisibility(!isBlank);
    _8.pane("HeroGAEffectN").setVisibility(!isBlank);
    mLifeBar.blank(isBlank);
    mIsBlank = isBlank;
}

void HeroStatus::lifeSetLength(f32 length) {
    mLifeBar.setLength(length);
}

void HeroStatus::lifeSetRate(f32 rate) {
    mLifeBar.set(rate);
}

f32 HeroStatus::lifeGetRate() const {
    return mLifeBar.lifeBarRate();
}

void HeroStatus::lifeDamage(f32 rate) {
    mIcon.startDamageAnim();
    mLifeBar.damage(rate, mIsPinch);
    mState = 2;
}

void HeroStatus::lifeCure(f32 rate) {
    if (rate != mLifeBar.lifeBarRate()) {
        mIcon.startCureAnim();
        mLifeBar.cure(rate, mIsPinch, mIsInvincible);
        mState = 3;
    }
}

void HeroStatus::lifeDead() {
    mIcon.startDeadAnim();
    mLifeBar.set(0.0f);
    mLifeBar.normal();
    _198.rootPane().hide();
    mEffect.releaseAndVanish();
    mState = 0;
}

void HeroStatus::lifeSetIsPinch(bool isPinch, bool playSE) {
    if (0.0f != mLifeBar.lifeBarRate() && mIsPinch != isPinch) {
        mIsPinch = isPinch;
        if (mIsPinch && playSE && !_137C) {
            mSE.start(0xAD);
        }
        if (mState == 0 || mState == 1) {
            toIdleState();
        }
    }
}

void HeroStatus::lifeInvincibleStart() {
    _198.rootPane().show();
    _198.play("Start", "Wait");
    mLifeBar.invincibleStart();
    mIcon.startWaitAnim();
    mEffect.requestP(0x331, _8.pane("HeroEffectN").pos());
    mState = 5;
    mIsInvincible = true;
}

void HeroStatus::lifeInvincibleLow() {
    _198.play("Bit");
    mLifeBar.invincibleLow();
}

void HeroStatus::lifeInvincibleEnd() {
    _198.play("End");
    mLifeBar.invincibleEnd();
    mEffect.release();
    mIsInvincible = false;
    toIdleState();
}

void HeroStatus::lifeIgnoreObjStop() {
    mLifeBar.ignoreObjStop();
}

#define MF_FUNCTION abilitySet__Q43scn4step4info10HeroStatusFQ43scn4step4hero11AbilityKind
void HeroStatus::abilitySet(hero::AbilityKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 mfBase;
    volatile u32 response;
    volatile u32 key;
    u32 hash;
    u32 t2;
    u32 t1;
    u32 p;
    u32 stop;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x5ED2C209
        opword  0x789B5E93
        opword  MF_WORD(0x38)
        opword  0xC4B83680
    after1:
        mflr    r23
        lwz     r18, 0x0(r23)
        lwz     r19, 0xc(r23)
        stw     r18, end
        stw     r19, start
    }
    if (!_137D) {
        mIcon.setParent(_8.pane("HeroStatusIconN"));
    } else {
        mIcon.setParent(_8.pane("AbGageN"));
    }
    stop = end;
    p = start;
    p -= 2;
    for (;;) {
        p += 2;
        if (p == stop) {
            break;
        }
        hash *= 0x97;
        hash += *(u16*)p;
    }
    mIcon.changeIcon(kind);
    asm {
        bl      after2
        opword  MF_WORD(0xF0)
        opword  0x443D24F1
    after2:
        mflr    r22
        lwz     r27, 0x0(r22)
        stw     r27, expected
    }
    hash += hash << 3;
    setName(kind);
    t1 = hash >> 11;
    hash ^= t1;
    t1 = hash << 15;
    hash += t1;
    t1 = expected;
    t1 = hash & ~t1;
    t2 = expected;
    t2 = t2 & ~hash;
    t2 = t1 | t2;
    hash = __cntlzw(t2);
    t2 = hash >> 5;
    hash = t2 * 57;
    hash = t2 + hash;
    if (hash == 0) {
        asm {
            stw     r29, -0x4(r1)
            bl      after3
            opword  MF_WORD(0x15C)
            opword  0x7B68E407
            opword  0x864F8C08
            opword  0xF7964702
        after3:
            mflr    r29
            lwz     r28, 0x0(r29)
            stw     r28, 0x0(r1)
            stw     r29, 0x4(r1)
            mtlr    r28
            bl      after4
            opword  MF_WORD(0x184)
            opword  0x30A5BA91
            opword  MF_WORD(0x18C)
        after4:
            mflr    r22
            lwz     r16, 0x0(r22)
            lwz     r28, 0x8(r22)
            stw     r28, key
            stw     r16, offset
            stw     r22, mfBase
        }
        offset = offset + 0x4C;
        key = 0;
        response = offset;
        response = response + mfBase;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    } else {
        setNameColor(kind);
    }
}
#undef MF_FUNCTION

void HeroStatus::abilityChange(hero::AbilityKind kind) {
    abilitySet(kind);
    mIcon.startGetAbilityAnim();
    _328.rootPane().setVisibility(true);
    _328.stop();
    _328.setFrameToHead();
    _328.start(false);
    if (!mIsInvincible) {
        if (mIsPinch) {
            mLifeBar.pinchWait();
        } else {
            mLifeBar.normal();
        }
    }
    mState = 4;
}

#define MF_FUNCTION toIdleState__Q43scn4step4info10HeroStatusFv
void HeroStatus::toIdleState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 response;
    volatile u32 mfBase;
    volatile u32 offset;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x59E843E8
    after1:
        mflr    r26
        lwz     r25, 0x0(r26)
        stw     r25, expected
        bl      after2
        opword  MF_WORD(0x3C)
        opword  0x20970608
        opword  0x65CE9802
        opword  MF_WORD(0x48)
        opword  0x13197205
    after2:
        mflr    r29
        lwz     r30, 0x0(r29)
        add     r30, r30, r29
        stw     r30, start
        lwz     r18, 0xc(r29)
        add     r30, r30, r18
        stw     r30, end
    }
    hash = 0x811C9DC5;
    limit = end - start + 1;
    i = 1;
    last = end;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x01000181;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (hash == expected) {
        if (mIsInvincible) {
            mState = 5;
        } else if (mIsPinch) {
            mIcon.startPinchAnim();
            mLifeBar.pinch();
            mState = 1;
        } else {
            mIcon.stopPinchAnim();
            mLifeBar.normal();
            mState = 0;
        }
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x134)
        after3:
            mflr    r26
            addi    r18, r26, 0x10
            mtlr    r18
            lwz     r27, 0x0(r26)
            stw     r27, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r26, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x15C)
            opword  MF_WORD(0x160)
        after4:
            mflr    r21
            stw     r21, mfBase
            lwz     r25, 0x0(r21)
            stw     r25, offset
            lwz     r27, 0x4(r21)
            stw     r27, key
        }
        offset = offset - 0x97;
        response = offset ^ key;
        response = response + mfBase;
        asm {
            lwz     r28, response
            mtlr    r28
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setName__Q43scn4step4info10HeroStatusFQ43scn4step4hero11AbilityKind
void HeroStatus::setName(hero::AbilityKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 size;
    u32 i;
    u32 hash;
    u32 base;
    const wchar_t* name;
    f32 charSpace;
    f32 width;
    f32 textWidth;
    f32 scale;

    lyt::PaneAccessor oneLine = mLayout.paneByName("Name");
    lyt::PaneAccessor twoLine = mLayout.paneByName("Name2Line");
    lyt::PaneAccessor pane;
    name = ::info::abilityName(kind);
    nw4r::lyt::Size fontSize;
    asm {
        bl      after1
        opword  MF_WORD(0x78)
        opword  0x6F0797EF
    after1:
        mflr    r17
        lwz     r23, 0x0(r17)
        stw     r23, expected
    }
    if (lyt::TagUtil::Find(name, L'\n') == -1) {
        oneLine.show();
        twoLine.hide();
        pane = oneLine;
        fontSize = _12D8;
        charSpace = _12E8;
    } else {
        oneLine.hide();
        twoLine.show();
        pane = twoLine;
        fontSize = _12E0;
        charSpace = _12EC;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x100)
        opword  0x041DF693
    after2:
        mflr    r22
        lwz     r26, 0x0(r22)
        add     r26, r26, r22
        stw     r26, start
        bl      after3
        opword  0x8C86E080
        opword  MF_WORD(0x120)
        opword  0x14867493
        opword  0x74253993
    after3:
        mflr    r22
        lwz     r21, 0x4(r22)
        add     r26, r26, r21
        stw     r26, end
    }
    base = start;
    size = end - base;
    pane.textBox()->SetFontSize(fontSize);
    hash = 0;
    pane.textBox()->SetCharSpace(charSpace);
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash *= 37;
        hash += *(u16*)(base + i - 1);
    }
    width = pane.size().x;
    hash += hash << 13;
    textWidth = ::info::CalcStringWidth(name, pane);
    hash ^= hash >> 7;
    hash += hash << 3;
    scale = 1.0f;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0 || textWidth > 0.0f) {
        scale = width / textWidth;
        if (scale > 1.0f) {
            scale = 1.0f;
        } else {
            scale *= 0.95f;
        }
    }
    fontSize.width *= scale;
    pane.textBox()->SetFontSize(fontSize);
    pane.textBox()->SetCharSpace(charSpace * scale);
    pane.setText(name);
}
#undef MF_FUNCTION

#define MF_FUNCTION setNameColor__Q43scn4step4info10HeroStatusFQ43scn4step4hero11AbilityKind
void HeroStatus::setNameColor(hero::AbilityKind kind) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 mfBase;
    volatile u32 offset;
    volatile u32 key;
    HeroStatus* self = this;
    hero::AbilityKind k = kind;
    u32 i;
    u32 base;
    u32 size;
    u32 mult;
    u32 hash;

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  MF_WORD(0x38)
        opword  0x54E43192
        opword  MF_WORD(0x40)
    after1:
        mflr    r27
        lwz     r20, 0x8(r27)
        lwz     r16, 0x0(r27)
        add     r16, r16, r27
        stw     r16, start
        add     r20, r20, r16
        stw     r20, end
    }
    size = end - start;
    base = start;
    i = -1;
    mult = 0x01000181;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= mult;
    }
    asm {
        bl      after2
        opword  MF_WORD(0xA4)
        opword  0xA14A371D
    after2:
        mflr    r20
        lwz     r23, 0x0(r20)
        stw     r23, expected
    }
    if ((hash ^ expected) != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xCC)
            opword  0xACA06C90
            opword  0x7D652605
        after3:
            mflr    r29
            addi    r22, r29, 0x18
            mtlr    r22
            lwz     r30, 0x0(r29)
            stw     r30, -0x4(r1)
            stw     r22, 0x0(r1)
            stw     r29, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0xFC)
            opword  0x6DB4C10B
            opword  MF_WORD(0x104)
        after4:
            mflr    r22
            lwz     r25, 0x8(r22)
            stw     r25, key
            lwz     r25, 0x0(r22)
            stw     r22, mfBase
            stw     r25, offset
        }
        offset = offset ^ 0xF6;
        response = offset ^ key;
        response = response + mfBase;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        if (hero::ABILITY_KIND_SUPER_SWORD <= k && k <= hero::ABILITY_KIND_SUPER_ICE) {
            switch (self->mKind) {
            case 0:
                self->mLayout.play("SuperPink");
                break;
            case 1:
                self->mLayout.play("SuperYellow");
                break;
            case 2:
                self->mLayout.play("SuperBlue");
                break;
            case 3:
                self->mLayout.play("SuperGreen");
                break;
            }
        } else {
            ::info::selectHeroPaneByAction(self->mLayout, self->mKind);
        }
    }
}
#undef MF_FUNCTION

}
}
}
