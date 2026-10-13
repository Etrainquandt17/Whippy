#include "scn/step/gimmick/shipevent/ShipEvent.h"

#include "metafortress.h"

namespace scn {
namespace step {
namespace gimmick {
namespace shipevent {

void ShipEvent::SEFadeRequester::request(u32 id) {
    if (!_0) {
        mfRequestCommon(id);
    }
}

#define MF_FUNCTION mfRequestCommon__Q63scn4step7gimmick9shipevent9ShipEvent15SEFadeRequesterFUl
void ShipEvent::SEFadeRequester::mfRequestCommon(u32 id) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 p;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0xEFAE36A1
    after1:
        mflr    r26
        lwz     r15, 0x0(r26)
        stw     r15, expected
        bl      after2
        opword  0x4873E280
        opword  0x84C61591
        opword  MF_WORD(0x40)
        opword  MF_WORD(0x44)
        opword  0x9C999490
        opword  0xAC869E90
    after2:
        mflr    r26
        lwz     r17, 0x8(r26)
        lwz     r21, 0xc(r26)
        add     r21, r17, r21
        stw     r17, start
        stw     r21, end
    }
    mSE.start(id);
    p = start;
    last = end;
    hash = 0xB5;
    _0 = true;
    p -= 2;
    for (;;) {
        p += 2;
        if (p == last) {
            break;
        }
        hash = *(u16*)p ^ (hash << 4 ^ hash >> 28);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    _1 = expected != hash;
    mSE.setVolume(1.0f);
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::gimmick::shipevent
