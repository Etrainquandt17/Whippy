#include "scn/subgame/gunshoot/chara/PlayerController.h"

#include "hel/math/Vector3.h"
#include "metafortress.h"
#include "nw4r/math/math_geometry.h"
#include "scn/subgame/common/coll/CollisionNode.h"

using hel::math::Vector3;

namespace scn {
namespace subgame {
namespace gunshoot {
namespace chara {

#define MF_FUNCTION shot__Q53scn7subgame8gunshoot5chara16PlayerControllerFb
void PlayerController::shot(bool charged) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  MF_WORD(0x24)
        opword  0x488BB580
    after1:
        mflr    r18
        lwz     r16, 0x0(r18)
        lwz     r14, 0x4(r18)
        add     r16, r16, r18
        add     r14, r14, r16
        stw     r16, start
        stw     r14, end
    }
    hash = 0;
    mPlayer.shot(charged);
    asm {
        bl      after2
        opword  MF_WORD(0x5C)
        opword  0xF963D5E1
    after2:
        mflr    r19
        lwz     r29, 0x0(r19)
        stw     r29, expected
    }
    const u32& size = end - start;
    base = start;
    playSound(mShotSoundLabel[charged]);
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash += *(u16*)(base + i - 1);
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    if (!(hash - expected != 0 || mEnemy.isDead())) {
        nw4r::math::SEGMENT3 segment;
        if (isBulletFromGun()) {
            const nw4r::math::VEC3& pos = _320;
            segment.P0 = segment.P1 = pos;
            segment.P1 += _314;
        } else {
            common::coll::CollisionNode::Result::ViewSegmentDPD(segment, mStage.currentCamera(), mInput.dpdPos());
        }
        for (Bullet** it = mBullets.begin(); it != mBullets.end(); ++it) {
            if (!(*it)->isSet()) {
                (*it)->set(Vector3(segment.P0), segment, charged);
                _310 = *it;
                return;
            }
        }
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::subgame::gunshoot::chara
