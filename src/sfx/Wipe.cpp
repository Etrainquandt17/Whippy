#include "sfx/Wipe.h"

#include "hel/math/Vector2.h"
#include "metafortress.h"

using hel::math::Vector2;

namespace sfx {

Wipe::Wipe()
    : mCounter()
    , mModel("Wipe") {
}

Wipe::~Wipe() {
}

void Wipe::requestWipeIn(const char* name, unsigned long wait, unsigned long frame) {
    mCounter.reset(wait);
    modelSetup(name, frame);
    mModel.setFrameToTail();
    mModel.setFrameRate(-1.0f * mModel.frameRate());
    checkAnimStart();
}

void Wipe::requestWipeOut(const char* name, unsigned long wait, unsigned long frame) {
    mCounter.reset(wait);
    modelSetup(name, frame);
    mModel.setVisibility(false);
    checkAnimStart();
}

bool Wipe::isAnimEnd() const {
    return mCounter.isEnd() && mModel.isExistModel() && mModel.isAnimEnd();
}

bool Wipe::isNeedToDraw() const {
    return mModel.isExistModel();
}

void Wipe::setLayoutPos(const Vector2& pos) {
    mModel.setLayoutPos(pos);
}

void Wipe::updateMain() {
    if (mModel.isExistModel()) {
        if (mCounter.isEnd()) {
            mModel.updateFrame();
        } else {
            mCounter.advance();
            checkAnimStart();
        }
    }
    mModel.updateMain();
}

void Wipe::updateUseGPU() {
    mModel.updateUseGPU();
}

void Wipe::draw() {
    mModel.draw();
}

#define MF_FUNCTION checkAnimStart__Q23sfx4WipeFv
void Wipe::checkAnimStart() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    register u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xFC561981
        opword  MF_WORD(0x2C)
    after1:
        mflr    r19
        lwz     r29, 0x0(r19)
        lwz     r25, 0x8(r19)
        stw     r29, start
        stw     r25, end
        lwz     r28, start
        lwz     r27, end
        subf    r27, r28, r27
        addi    r23, r27, 1
        li      r26, 1
        lwz     r24, start
        lis     r27, 0x811D
        subi    hash, r27, 0x61D7
        lis     r28, 0x100
        addi    r28, r28, 0x1AB
        b       test
    next:
        add     r27, r24, r26
        lhz     r27, -0x1(r27)
        xor     hash, hash, r27
        mullw   hash, hash, r28
        addi    r26, r26, 2
    test:
        cmplw   cr4, r26, r23
        bne     cr4, next
        bl      after2
        opword  MF_WORD(0x90)
        opword  0xAE0D22A3
    after2:
        mflr    r18
        lwz     r25, 0x0(r18)
        stw     r25, expected
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0 || mCounter.isEnd()) {
        mModel.start(false);
        mModel.setVisibility(true);
    }
}
#undef MF_FUNCTION


#define MF_FUNCTION modelSetup__Q23sfx4WipeFPCcUl
void Wipe::modelSetup(const char* name, unsigned long frame) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 response;
    volatile u32 key;
    u32 hash;
    u32 t;
    u32 i;
    u32 first;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xF7FCEA7A
    after1:
        mflr    r18
        lwz     r22, 0x0(r18)
        stw     r22, expected
    }
    hash = 0x811C9E53;
    mModel.setModel(name);
    asm {
        bl      after2
        opword  MF_WORD(0x58)
        opword  MF_WORD(0x5C)
        opword  0xACE38790
    after2:
        mflr    r18
        lwz     r23, 0x0(r18)
        add     r23, r23, r18
        lwz     r25, 0x4(r18)
        stw     r23, start
        add     r25, r25, r23
        stw     r25, end
    }
    i = 1;
    first = start;
    limit = end - first + 1;
    for (; i != limit; i += 2) {
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x010001D1;
    }
    mModel.setAnim("TopL");
    t = hash >> 10;
    hash ^= t;
    t = hash << 20;
    hash ^= t;
    t = expected;
    if (hash == t) {
        if (frame != 0) {
            mModel.setFrameRate(mModel.totalFrame() / static_cast<f32>(frame));
        }
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x120)
        after3:
            mflr    r14
            lwz     r20, 0x0(r14)
            stw     r20, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r20, -0x4(r1)
            stw     r14, -0x8(r1)
            mtlr    r20
            bl      after4
            opword  MF_WORD(0x144)
            opword  0x4418670C
            opword  0x03B18E05
            opword  MF_WORD(0x150)
        after4:
            mflr    r29
            lwz     r14, 0xC(r29)
            stw     r14, key
            lwz     r14, 0x0(r29)
            stw     r29, base
            stw     r14, offset
        }
        offset = offset + 0xBF;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r19, response
            mtlr    r19
            blr
        }
    }
}
#undef MF_FUNCTION

}  // namespace sfx
