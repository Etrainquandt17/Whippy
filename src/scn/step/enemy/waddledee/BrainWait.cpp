#include "scn/step/enemy/waddledee/BrainWait.h"

#include "gobj/Anim.h"
#include "gobj/Target.h"
#include "hel/math/Vector2.h"
#include "metafortress.h"
#include "scn/step/chara/Location.h"
#include "scn/step/chara/Model.h"
#include "scn/step/enemy/Enemy.h"
#include "scn/step/enemy/Utility.h"
#include "scn/step/enemy/waddledee/StateWait.h"
#include "types.h"

using hel::math::Vector2;

namespace scn {
namespace step {
namespace enemy {
namespace waddledee {

BrainWait::BrainWait(Enemy& enemy) : BrainBase(enemy), mFrame(0) {}

#define MF_FUNCTION onStart__Q53scn4step5enemy9waddledee9BrainWaitFv
bool BrainWait::onStart() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    hash = 0x811C9DC5;
    asm {
        bl      after1
        opword  0xE0579693
        opword  MF_WORD(0x30)
        opword  0x7C7BDC91
        opword  0x8CF66192
        opword  MF_WORD(0x3C)
        opword  0x64AD0592
    after1:
        mflr    r24
        lwz     r27, 0x4(r24)
        lwz     r20, 0x10(r24)
        stw     r27, start
        stw     r20, end
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0x083B376A
    after2:
        mflr    r19
        lwz     r22, 0x0(r19)
        stw     r22, expected
    }
    obj().stateChanger().setNextState<StateWait, Enemy*>(&obj());
    i = 1;
    base = start;
    limit = end - base + 1;
    while (i != limit) {
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x01000181;
        i += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    base = (u32)__cntlzw(hash - expected) >> 5;
    hash = base - (base >> 2);
    if (hash == 0) {
        volatile u32 key;
        volatile u32 response;
        volatile u32 offset;
        volatile u32 base2;

        asm {
            bl      after3
            opword  0x7C85DF80
            opword  MF_WORD(0x138)
        after3:
            mflr    r26
            lwz     r17, 0x4(r26)
            stw     r17, -0x4(r1)
            stw     r26, 0x0(r1)
            stw     r17, -0x4(r1)
            stw     r26, -0x8(r1)
            mtlr    r17
            bl      after4
            opword  MF_WORD(0x15C)
            opword  MF_WORD(0x160)
        after4:
            mflr    r26
            lwz     r19, 0x0(r26)
            stw     r26, base2
            lwz     r18, 0x4(r26)
            stw     r19, offset
            stw     r18, key
        }
        offset = offset ^ 0x96;
        response = offset ^ key;
        response = response + base2;
        asm {
            lwz     r25, response
            mtlr    r25
            blr
        }
    } else {
        return true;
    }
}
#undef MF_FUNCTION

void BrainWait::update() {
    if (!Utility::IsFixDirType(obj()) && obj().model().anim().currentG3DAnimIndex() == 0) {
        Vector2 playerPos = Utility::GetNearestPlayerPos(obj());
        bool isRight = playerPos.x > obj().location().pos().x;
        if (isRight != obj().target().isRightDir()) {
            mFrame++;
            if (mFrame == 30) {
                obj().target().setIsRightDir(isRight);
            }
        } else {
            mFrame = 0;
        }
    }
}

}}}}  // namespace scn::step::enemy::waddledee
