#include "scn/step/hero/VacuumSoundCtrl.h"

#include "metafortress.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/SoundSE.h"

namespace scn {
namespace step {
namespace hero {

namespace {

// TODO: this is a function of a shared header: its constant argument lands in .sdata, as in the original.
template <typename T>
inline T t_min(const T& a, const T& b) {
    return a > b ? b : a;
}

}

VacuumSoundCtrl::VacuumSoundCtrl() {
}

VacuumSoundCtrl::~VacuumSoundCtrl() {
}

#define MF_FUNCTION registerObj__Q43scn4step4hero15VacuumSoundCtrlFQ24util35ObjRefHandle_Q43scn4step4hero4Hero_
void VacuumSoundCtrl::registerObj(util::ObjRefHandle<Hero> obj) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 word;
    u32 hash;

    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
        opword  0x3CAEAA80
    after1:
        mflr    r18
        lwz     r22, 0x4(r18)
        lwz     r16, 0x0(r18)
        add     r16, r16, r18
        stw     r16, start
        add     r22, r22, r16
        stw     r22, end
    }
    word = start;
    last = end;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash ^= *(u16*)word;
        hash *= 0x01000193;
    }
    cleanup();
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0xB4D3013D
    after2:
        mflr    r16
        lwz     r21, 0x0(r16)
        stw     r21, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected == 0) {
        if (obj.isNull()) {
            asm {
                b       done
            }
        }
        if (hash - expected == 0) {
            if (mObjs.isFull()) {
                asm {
                    b       done
                }
            }
            mObjs.add(obj);
            obj->soundSE()._2BC.setVolume(1.0f);
            updateVolume();
        }
    }
done:;
}
#undef MF_FUNCTION

#define MF_FUNCTION unregisterObj__Q43scn4step4hero15VacuumSoundCtrlFQ24util35ObjRefHandle_Q43scn4step4hero4Hero_
void VacuumSoundCtrl::unregisterObj(util::ObjRefHandle<Hero> obj) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 key;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x2801A080
    after1:
        mflr    r23
        lwz     r15, 0x0(r23)
        stw     r15, start
        bl      after2
        opword  0xC00C5E09
        opword  MF_WORD(0x48)
        opword  0xBCD75493
        opword  0xB094FB80
    after2:
        mflr    r23
        lwz     r15, 0x4(r23)
        stw     r15, end
    }
    cleanup();
    limit = end - start + 1;
    last = end;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash *= 193;
        hash += *(u16*)(last - 1 - i);
    }
    asm {
        bl      after3
        opword  MF_WORD(0xA8)
        opword  0x9E9998C8
    after3:
        mflr    r22
        lwz     r30, 0x0(r22)
        stw     r30, expected
    }
    if (hash == expected) {
        if (!obj.isNull()) {
            u32 count = mObjs.count();
            for (u32 n = 0; n < count; n++) {
                if (!mObjs[n].isNull() && mObjs[n].ref().padChan() == obj->padChan()) {
                    mObjs.removeAtIndex(n);
                    break;
                }
            }
            updateVolume();
        }
    } else {
        asm {
            bl      after4
            opword  0x007DCD80
            opword  0x4C8E0591
            opword  MF_WORD(0x158)
        after4:
            mflr    r18
            lwz     r20, 0x8(r18)
            stw     r20, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r20
            bl      after5
            opword  MF_WORD(0x17C)
            opword  0xF89D6390
            opword  0x1CE27580
            opword  MF_WORD(0x188)
        after5:
            mflr    r14
            lwz     r15, 0x0(r14)
            stw     r14, base
            lwz     r16, 0xc(r14)
            stw     r15, offset
            stw     r16, key
        }
        key = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    }
}
#undef MF_FUNCTION

void VacuumSoundCtrl::update() {
    updateVolume();
}

void VacuumSoundCtrl::updateVolume() {
    cleanup();
    bool isFirst = true;
    u32 count = mObjs.count();
    for (u32 i = 0; i < count; i++) {
        u32 index = count - i - 1;
        if (!mObjs[index].isNull()) {
            if (isFirst) {
                f32 volume = t_min(0.125f + mObjs[index].ref().soundSE()._2BC.volume(), 1.0f);
                mObjs[index].ref().soundSE()._2BC.setVolume(volume);
            } else {
                mObjs[index].ref().soundSE()._2BC.setVolume(0.2f);
            }
            isFirst = false;
        }
    }
}

void VacuumSoundCtrl::cleanup() {
    u32 count = mObjs.count();
    for (u32 i = 0; i < count; i++) {
        u32 index = count - i - 1;
        if (mObjs[index].isNull()) {
            mObjs.removeAtIndex(index);
        }
    }
}

}
}
}
