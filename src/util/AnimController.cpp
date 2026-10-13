#include "util/AnimController.h"

#include "metafortress.h"

namespace util {

AnimController::AnimController(f32 totalFrame)
    : mTotalFrame(totalFrame)
    , mFrame(0.0f)
    , mFrameRate(1.0f)
    , mDoLoop(false)
    , mIsAnimating(false)
    , mIsLooped(false) {}

f32 AnimController::totalFrame() const {
    return mTotalFrame;
}

#define MF_FUNCTION setFrameToHead__Q24util14AnimControllerFv
void AnimController::setFrameToHead() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;
    u32 first;

    asm {
        bl      after1
        opword  0x34425280
        opword  MF_WORD(0x28)
        opword  0x7055F591
    after1:
        mflr    r25
        lwz     r24, 0x4(r25)
        stw     r24, start
        bl      after2
        opword  0x30B8C590
        opword  MF_WORD(0x44)
        opword  0xDBE8110A
        opword  0xA4FA7D81
    after2:
        mflr    r25
        lwz     r30, 0x4(r25)
        add     r30, r30, r24
        stw     r30, end
    }
    limit = end - start;
    base = start;
    hash = 0x811C9E53;
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash ^= *(u16*)(base + i - 1);
        hash *= 0x010001D1;
    }
    hash ^= hash >> 10;
    asm {
        bl      after3
        opword  MF_WORD(0xB4)
        opword  0xC50E7E94
    after3:
        mflr    r29
        lwz     r23, 0x0(r29)
        stw     r23, expected
    }
    hash ^= hash << 20;
    first = (u32)__cntlzw(hash - expected) >> 5;
    hash = first | (first << 13);
    if (hash == 0) {
        volatile u32 base2;
        volatile u32 response;
        volatile u32 addend;
        volatile u32 offset;

        asm {
            bl      after4
            opword  MF_WORD(0xF4)
        after4:
            mflr    r18
            lwz     r27, 0x0(r18)
            stw     r27, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r27, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r27
            bl      after5
            opword  MF_WORD(0x118)
            opword  0x98117891
            opword  MF_WORD(0x120)
        after5:
            mflr    r28
            lwz     r14, 0x0(r28)
            lwz     r19, 0x8(r28)
            stw     r19, addend
            stw     r14, offset
            stw     r28, base2
        }
        offset = offset - 0x43;
        response = offset + addend;
        response = response + base2;
        asm {
            lwz     r17, response
            mtlr    r17
            blr
        }
    } else {
        mFrame = 0.0f;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setFrameToTail__Q24util14AnimControllerFv
void AnimController::setFrameToTail() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
        opword  0xBEF88F0C
        opword  0x28278B80
    after1:
        mflr    r18
        lwz     r29, 0x0(r18)
        add     r29, r29, r18
        stw     r29, start
        lwz     r25, 0x4(r18)
        add     r29, r29, r25
        stw     r29, end
    }
    hash = 0;
    limit = end - start + 1;
    i = 1;
    base = start;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 193;
        hash += *(u16*)(base + i - 1);
        i += 2;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x90)
        opword  0x5241613E
    after2:
        mflr    r22
        lwz     r30, 0x0(r22)
        stw     r30, expected
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash ^= expected;
    if (hash == 0) {
        setFrame(totalFrame());
    } else {
        volatile u32 subtrahend;
        volatile u32 offset;
        volatile u32 response;
        volatile u32 base2;

        asm {
            bl      after3
            opword  MF_WORD(0xD8)
        after3:
            mflr    r26
            addi    r22, r26, 0x10
            mtlr    r22
            lwz     r16, 0x0(r26)
            stw     r16, -0x4(r1)
            stw     r22, 0x0(r1)
            stw     r26, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x100)
            opword  MF_WORD(0x104)
        after4:
            mflr    r30
            lwz     r28, 0x0(r30)
            lwz     r21, 0x4(r30)
            stw     r21, subtrahend
            stw     r28, offset
            stw     r30, base2
        }
        offset = offset - 0xC0;
        response = offset - subtrahend;
        response = response + base2;
        asm {
            lwz     r28, response
            mtlr    r28
            blr
        }
    }
}
#undef MF_FUNCTION

void AnimController::updateFrame() {
    if (!mIsAnimating) {
        return;
    }
    f32 totalFrame;
    f32 frame = mFrame + mFrameRate;
    mIsLooped = false;
    if (mDoLoop && mFrameRate != 0.0f) {
        totalFrame = mTotalFrame;
        if (0.0f < mFrameRate) {
            if (totalFrame <= frame) {
                mIsLooped = true;
                while (totalFrame <= frame) {
                    frame -= totalFrame;
                }
            }
        } else if (frame < 0.0f) {
            mIsLooped = true;
            while (frame < 0.0f) {
                frame += totalFrame;
            }
        }
    }
    mFrame = frame;
    checkAnimEnd();
}

void AnimController::start(bool doLoop) {
    mDoLoop = doLoop;
    mIsAnimating = true;
    mIsLooped = false;
    checkAnimEnd();
}

void AnimController::stop() {
    if (!mIsAnimating) {
        return;
    }
    mIsAnimating = false;
}

bool AnimController::isAnimEnd() const {
    if (mDoLoop) {
        return false;
    }
    if (0.0f < mFrameRate) {
        return mTotalFrame <= mFrame;
    }
    if (mFrameRate < 0.0f) {
        return mFrame <= 0.0f;
    }
    return false;
}

#define MF_FUNCTION changeDoLoop__Q24util14AnimControllerFb
void AnimController::changeDoLoop(bool doLoop) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u16* word;
    u16* last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x20)
        opword  0x21269CF5
    after1:
        mflr    r25
        lwz     r27, 0x0(r25)
        stw     r27, expected
        bl      after2
        opword  0xB4744681
        opword  MF_WORD(0x3C)
        opword  MF_WORD(0x40)
    after2:
        mflr    r14
        lwz     r17, 0x8(r14)
        stw     r17, start
        lwz     r18, 0x4(r14)
        stw     r18, end
    }
    hash = 0x811C9DDB;
    word = (u16*)start;
    last = (u16*)end;
    for (; word != last; word++) {
        hash ^= *word;
        hash *= 0x01000193;
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    while (hash - expected != 0) {
    }
    mDoLoop = doLoop;
}
#undef MF_FUNCTION

f32 AnimController::frame() const {
    return mFrame;
}

void AnimController::setFrame(f32 frame) {
    mFrame = frame;
}

void AnimController::checkAnimEnd() {
    if (isAnimEnd()) {
        mIsAnimating = false;
    }
}

}
