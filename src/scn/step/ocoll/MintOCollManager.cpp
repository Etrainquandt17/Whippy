#include "scn/step/ocoll/MintOCollManager.h"

#include "hel/common/PointerWrapper.h"
#include "metafortress.h"
#include "types.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace ocoll {

namespace {

PointerWrapper< ::ocoll::Manager> t_manager;

}

namespace MintOCollManager {

#define MF_FUNCTION Register__Q43scn4step5ocoll16MintOCollManagerFRQ25ocoll7Manager
void Register(::ocoll::Manager& manager) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 subtrahend;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    u32 size;
    u32 i;
    u32 first;
    u32 hash;
    u32 same;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x185BC380
        opword  MF_WORD(0x2C)
    after1:
        mflr    r26
        lwz     r24, 0x8(r26)
        stw     r24, start
        lwz     r30, 0x0(r26)
        stw     r30, end
    }
    hash = 0x811C9DDB;
    first = start;
    size = end - first;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x01000193;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x8C)
        opword  0x66718106
    after2:
        mflr    r25
        lwz     r21, 0x0(r25)
        stw     r21, expected
    }
    same = (expected ^ hash) == 0;
    hash = same * 30;
    hash = same + hash;
    if (hash == 0) {
        t_manager.set(manager);
    } else {
        asm {
            bl      after3
            opword  0xBBC4BA05
            opword  MF_WORD(0xD0)
        after3:
            mflr    r24
            lwz     r25, 0x4(r24)
            stw     r25, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r25, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r25
            bl      after4
            opword  MF_WORD(0xF4)
            opword  0x44852404
            opword  0x08EC4581
            opword  MF_WORD(0x100)
        after4:
            mflr    r27
            lwz     r16, 0xC(r27)
            stw     r16, subtrahend
            lwz     r16, 0x0(r27)
            stw     r27, base
            stw     r16, offset
        }
        offset = offset + 0x9C;
        response = offset - subtrahend;
        response = response + base;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    }
}
#undef MF_FUNCTION

void Unregister(::ocoll::Manager&) {
    t_manager.reset();
}

::ocoll::Manager& Ref() {
    return t_manager.ref();
}

}}}}  // namespace scn::step::ocoll::MintOCollManager
