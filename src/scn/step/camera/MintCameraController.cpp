#include "scn/step/camera/MintCameraController.h"

#include "hel/common/PointerWrapper.h"
#include "metafortress.h"
#include "types.h"

using hel::common::PointerWrapper;

namespace scn {
namespace step {
namespace camera {

namespace {

PointerWrapper<CameraController> t_obj;

}

namespace MintCameraController {

#define MF_FUNCTION Register__Q43scn4step6camera20MintCameraControllerFRQ43scn4step6camera16CameraController
void Register(CameraController& obj) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 response;
    volatile u32 subtrahend;
    volatile u32 base;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x2295214D
    after1:
        mflr    r17
        lwz     r24, 0x0(r17)
        stw     r24, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  0x4C361093
        opword  MF_WORD(0x44)
        opword  MF_WORD(0x48)
    after2:
        mflr    r30
        lwz     r28, 0x8(r30)
        lwz     r29, 0x4(r30)
        stw     r29, end
        stw     r28, start
    }
    word = start;
    last = end;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xD4)
        after3:
            mflr    r24
            lwz     r25, 0x0(r24)
            stw     r25, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r25, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r25
            bl      after4
            opword  MF_WORD(0xF8)
            opword  0xE3FD300B
            opword  0x00AA3E91
            opword  MF_WORD(0x104)
        after4:
            mflr    r27
            stw     r27, base
            lwz     r15, 0x0(r27)
            stw     r15, offset
            lwz     r30, 0xC(r27)
            stw     r30, subtrahend
        }
        offset = offset ^ 0x42;
        response = offset - subtrahend;
        response = response + base;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    } else {
        t_obj.set(obj);
    }
}
#undef MF_FUNCTION

void Unregister(CameraController&) {
    t_obj.reset();
}

#define MF_FUNCTION Obj__Q43scn4step6camera20MintCameraControllerFv
CameraController& Obj() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 response;
    volatile u32 addend;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x7AB0036E
    after1:
        mflr    r28
        lwz     r25, 0x0(r28)
        stw     r25, expected
        bl      after2
        opword  MF_WORD(0x38)
        opword  MF_WORD(0x3C)
        opword  0x2C259F91
        opword  0x5400C680
    after2:
        mflr    r20
        lwz     r26, 0x4(r20)
        lwz     r17, 0x0(r20)
        add     r17, r17, r20
        stw     r17, start
        add     r26, r26, r17
        stw     r26, end
    }
    last = end;
    word = start;
    hash = 0xBF;
    for (;;) {
        if (word == last) {
            break;
        }
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
        word += 2;
    }
    hash -= expected;
    hash |= hash << 15;
    if (hash == 0) {
        return t_obj.ref();
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0xB8)
        after3:
            mflr    r28
            lwz     r23, 0x0(r28)
            stw     r23, -0x4(r1)
            stw     r28, 0x0(r1)
            stw     r23, -0x4(r1)
            stw     r28, -0x8(r1)
            mtlr    r23
            bl      after4
            opword  MF_WORD(0xDC)
            opword  0x17FC9400
            opword  MF_WORD(0xE4)
        after4:
            mflr    r16
            lwz     r24, 0x8(r16)
            stw     r24, addend
            lwz     r24, 0x0(r16)
            stw     r16, base
            stw     r24, offset
        }
        offset = offset ^ 0xC6;
        response = offset + addend;
        response = response + base;
        asm {
            lwz     r15, response
            mtlr    r15
            blr
        }
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::step::camera::MintCameraController
