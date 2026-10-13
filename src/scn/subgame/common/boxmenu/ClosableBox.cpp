#define UTIL_OBJREFHANDLE_ASSIGNMENT_IN_CLASS
#include "scn/subgame/common/boxmenu/ClosableBox.h"

#include "metafortress.h"
#include "util/ObjList.h"

// TODO: a stand-in: with it the copy of a Box calls GetNodeFromPointer as the original does.
template class util::ObjListNode<lyt::Layout, util::ObjListDummyType>;

namespace scn {
namespace subgame {
namespace common {
namespace boxmenu {

inline bool isOpening(int status) {
    return status == 2;
}

#define MF_FUNCTION __ct__Q53scn7subgame6common7boxmenu11ClosableBoxFQ53scn7subgame6common7boxmenu3BoxQ53scn7subgame6common7boxmenu3BoxPCcPCcPCcPCcPCcPCc
ClosableBox::ClosableBox(Box box, Box subBox, const char* openAnim, const char* closeAnim, const char* openedAnim, const char* closedAnim,
                         const char* subOpenAnim, const char* subCloseAnim)
    : mOpenAnim(openAnim)
    , mCloseAnim(closeAnim)
    , mOpenedAnim(openedAnim)
    , mClosedAnim(closedAnim)
    , mSubOpenAnim(subOpenAnim)
    , mSubCloseAnim(subCloseAnim)
    , mBox(box)
    , mSubBox(subBox)
    , mStatus(5)
    , _68(false)
    , _69(false)
    , mIsSuspend(false)
    , mOpenSE()
    , mCloseSE()
    , mOpenSELabel(0xFFFFFFFF)
    , mCloseSELabel(0xFFFFFFFF) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 response;
    volatile u32 base;
    u32 i;
    u32 word;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0xC0)
        opword  MF_WORD(0xC4)
        opword  0x00D70509
        opword  0x68AB8F80
    after1:
        mflr    r17
        lwz     r21, 0x4(r17)
        lwz     r28, 0x0(r17)
        add     r28, r28, r17
        stw     r28, start
        add     r21, r21, r28
        stw     r21, end
    }
    hash = 0x811C9E53;
    limit = end - start + 1;
    i = 1;
    word = end;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(word - 1 - i);
        hash *= 0x010001D1;
        i += 2;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x13C)
        opword  0x558AA0E8
    after2:
        mflr    r26
        lwz     r14, 0x0(r26)
        stw     r14, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected == 0) {
        initialize();
    } else {
        asm {
            bl      after3
            opword  0x9C7DB993
            opword  0x503B1892
            opword  0xABD79400
            opword  MF_WORD(0x1A4)
        after3:
            mflr    r24
            lwz     r16, 0xC(r24)
            stw     r16, -0x4(r1)
            stw     r24, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r24, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0x1C8)
            opword  0xCCFC4A90
            opword  MF_WORD(0x1D0)
        after4:
            mflr    r25
            lwz     r21, 0x8(r25)
            stw     r21, key
            lwz     r21, 0x0(r25)
            stw     r25, base
            stw     r21, offset
        }
        offset = offset ^ 0x10;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    }
}
#undef MF_FUNCTION

ClosableBox::~ClosableBox() {
}

int ClosableBox::is() const {
    return mStatus;
}

#define MF_FUNCTION open__Q53scn7subgame6common7boxmenu11ClosableBoxFv
void ClosableBox::open() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 key;
    volatile u32 offset;
    volatile u32 response;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  0xC484FA93
        opword  MF_WORD(0x28)
        opword  0xB091E50F
        opword  0xD8C13C81
        opword  MF_WORD(0x34)
        opword  0xFAA5BD0C
        opword  0xFAE39003
    after1:
        mflr    r18
        lwz     r21, 0x4(r18)
        lwz     r22, 0x10(r18)
        add     r22, r21, r22
        stw     r21, start
        stw     r22, end
    }
    word = start;
    last = end;
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x68)
        opword  0xDE2570C4
    after2:
        mflr    r30
        lwz     r23, 0x0(r30)
        stw     r23, expected
    }
    for (;;) {
        if (word == last) {
            break;
        }
        hash += *(u16*)word;
        hash += hash << 10;
        hash ^= hash >> 6;
        word += 2;
    }
    hash ^= hash >> 10;
    hash ^= hash << 20;
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  0x981D3281
            opword  0xD4DA8C91
            opword  MF_WORD(0xD0)
        after3:
            mflr    r20
            lwz     r16, 0x8(r20)
            stw     r16, -0x4(r1)
            stw     r20, 0x0(r1)
            stw     r16, -0x4(r1)
            stw     r20, -0x8(r1)
            mtlr    r16
            bl      after4
            opword  MF_WORD(0xF4)
            opword  0x3C94EC80
            opword  MF_WORD(0xFC)
        after4:
            mflr    r21
            stw     r21, base
            lwz     r26, 0x0(r21)
            stw     r26, offset
            lwz     r15, 0x8(r21)
            stw     r15, key
        }
        offset = offset + 0x7F;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r23, response
            mtlr    r23
            blr
        }
    } else {
        if (isClosed()) {
            if (_68 || !isSuspend()) {
                if (!AbstractSuspendableTree::isExclusivelyResume()) {
                    if (!mSubBox.isEmpty()) {
                        mSubBox.setAnimByName(mSubOpenAnim);
                        mSubBox.start(false);
                        mStatus = 1;
                    } else {
                        setStatusOnOpening();
                    }
                }
            }
        }
    }
}
#undef MF_FUNCTION

bool ClosableBox::isClosed() const {
    return mStatus == 0;
}

#define MF_FUNCTION close__Q53scn7subgame6common7boxmenu11ClosableBoxFv
void ClosableBox::close() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 last;
    u32 word;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  MF_WORD(0x28)
    after1:
        mflr    r15
        lwz     r17, 0x0(r15)
        add     r17, r17, r15
        stw     r17, start
        lwz     r19, 0x4(r15)
        add     r17, r17, r19
        stw     r17, end
    }
    last = end;
    word = start;
    hash = 0xB5;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash = *(u16*)word ^ ((hash << 4) ^ (hash >> 28));
    }
    asm {
        bl      after2
        opword  MF_WORD(0x84)
        opword  0xE5373719
    after2:
        mflr    r29
        lwz     r15, 0x0(r29)
        stw     r15, expected
    }
    if (hash - expected != 0 || !isOpened()) {
        return;
    }
    if (hash - expected != 0 || (!_69 && isSuspend())) {
        return;
    }
    if (hash - expected != 0 || AbstractSuspendableTree::isExclusivelyResume()) {
        return;
    }
    setStatusOnClosing();
}
#undef MF_FUNCTION

bool ClosableBox::isOpened() const {
    return mStatus == 3;
}

#define MF_FUNCTION openImmediate__Q53scn7subgame6common7boxmenu11ClosableBoxFv
void ClosableBox::openImmediate() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 base;
    u32 hash;
    u32 i;
    u32 last;
    u32 limit;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0x1DAA31E5
    after1:
        mflr    r21
        lwz     r15, 0x0(r21)
        stw     r15, expected
    }
    hash = 0;
    asm {
        bl      after2
        opword  MF_WORD(0x40)
        opword  0x8462D892
        opword  MF_WORD(0x48)
        opword  0x0B58B204
    after2:
        mflr    r26
        lwz     r16, 0x8(r26)
        lwz     r15, 0x0(r26)
        add     r16, r15, r16
        stw     r16, end
        stw     r15, start
    }
    i = 1;
    last = end;
    limit = last - start + 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 107;
        hash += *(u16*)(last - 1 - i);
        i += 2;
    }
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0xB4)
        after3:
            mflr    r28
            addi    r14, r28, 0x10
            mtlr    r14
            lwz     r29, 0x0(r28)
            stw     r29, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r28, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0xDC)
            opword  MF_WORD(0xE0)
        after4:
            mflr    r14
            lwz     r21, 0x0(r14)
            lwz     r30, 0x4(r14)
            stw     r30, key
            stw     r21, offset
            stw     r14, base
        }
        offset = offset + 0x69;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r27, response
            mtlr    r27
            blr
        }
    } else {
        if (!isSuspend() && !AbstractSuspendableTree::isExclusivelyResume()) {
            mBox.setAnimByName(mOpenAnim);
            mBox.setFrameToTail();
            if (mOpenedAnim != 0) {
                mBox.setAnimByName(mOpenedAnim);
                mBox.start(true);
            }
            mStatus = 3;
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION closeImmediate__Q53scn7subgame6common7boxmenu11ClosableBoxFv
void ClosableBox::closeImmediate() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 key;
    volatile u32 offset;
    volatile u32 response;
    u32 i;
    u32 hash;
    u32 last;
    u32 size;

    hash = 0x811C9E07;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xF6B53F08
        opword  MF_WORD(0x34)
        opword  0xED94F801
        opword  0x90975081
    after1:
        mflr    r20
        lwz     r27, 0x0(r20)
        lwz     r24, 0x8(r20)
        add     r27, r27, r20
        add     r24, r24, r27
        stw     r27, start
        stw     r24, end
    }
    last = end;
    size = last - start;
    i = -1;
    while (i != size - 1) {
        i += 2;
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001A7;
    }
    hash += hash << 13;
    asm {
        bl      after2
        opword  MF_WORD(0xA8)
        opword  0x78A8DD31
    after2:
        mflr    r29
        lwz     r14, 0x0(r29)
        stw     r14, expected
    }
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash == expected) {
        if (!isSuspend() && !AbstractSuspendableTree::isExclusivelyResume()) {
            if (mCloseAnim != 0) {
                mBox.setAnimByName(mCloseAnim);
                mBox.setFrameToTail();
            } else if (mOpenAnim != 0) {
                mBox.setAnimByName(mOpenAnim);
                mBox.setFrameToHead();
            }
            if (mClosedAnim != 0) {
                mBox.setAnimByName(mClosedAnim);
                mBox.start(true);
            }
            mStatus = 0;
        }
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x180)
        after3:
            mflr    r18
            lwz     r22, 0x0(r18)
            stw     r22, -0x4(r1)
            stw     r18, 0x0(r1)
            stw     r22, -0x4(r1)
            stw     r18, -0x8(r1)
            mtlr    r22
            bl      after4
            opword  MF_WORD(0x1A4)
            opword  0xCCF39391
            opword  0xD4DDBB91
            opword  MF_WORD(0x1B0)
        after4:
            mflr    r26
            lwz     r18, 0x0(r26)
            lwz     r14, 0xC(r26)
            stw     r14, key
            stw     r18, offset
            stw     r26, base
        }
        offset = offset + 1;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r15, response
            mtlr    r15
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION fixToBeOpened__Q53scn7subgame6common7boxmenu11ClosableBoxFv
void ClosableBox::fixToBeOpened() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 limit;
    u32 i;
    u32 first;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x1C)
        opword  0xD8CFBD25
    after1:
        mflr    r23
        lwz     r20, 0x0(r23)
        stw     r20, expected
        bl      after2
        opword  0x38529092
        opword  0x983A1E02
        opword  MF_WORD(0x3C)
        opword  0xF027A080
        opword  0x847D1B81
        opword  MF_WORD(0x48)
        opword  0x00950C81
        opword  0x9F46DE00
    after2:
        mflr    r27
        lwz     r28, 0x8(r27)
        lwz     r29, 0x14(r27)
        stw     r28, start
        add     r29, r28, r29
        stw     r29, end
    }
    hash = 0xBF;
    limit = end - start;
    first = start;
    i = -1;
    while (i != limit - 1) {
        i += 2;
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(first + i - 1);
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash - expected != 0 || isOpened()) {
        return;
    }
    if (hash - expected != 0 || isOpening(mStatus)) {
        return;
    }
    if (hash - expected != 0 || isClosed()) {
        open();
        return;
    }
    while (hash - expected != 0) {
    }
    if (hash - expected != 0 || _68) {
        return;
    }
    _68 = expected == hash;
}
#undef MF_FUNCTION

void ClosableBox::fixToBeClosed() {
    if (isClosed()) {
        return;
    }
    if (mStatus == 4) {
        return;
    }
    if (isOpened()) {
        close();
        return;
    }
    if (_69) {
        return;
    }
    _69 = true;
}

bool ClosableBox::isSuspend() const {
    return mIsSuspend;
}

void ClosableBox::suspend() {
    if (isOpened()) {
        AbstractSuspendableTree::suspend();
    }
    mIsSuspend = true;
}

void ClosableBox::resume() {
    mIsSuspend = false;
    if (isOpened()) {
        AbstractSuspendableTree::resume();
    }
}

bool ClosableBox::isExclusivelyResume() const {
    return !isClosed() || AbstractSuspendableTree::isExclusivelyResume();
}

void ClosableBox::updateMain() {
    if (mStatus == 4 && mBox.isAnimEnd()) {
        mStatus = 0;
        if (_68) {
            _68 = false;
            open();
        } else if (mClosedAnim != 0) {
            mBox.setAnimByName(mClosedAnim);
            mBox.start(true);
        }
    } else if (mStatus == 2 && mBox.isAnimEnd()) {
        if (!mIsSuspend) {
            AbstractSuspendableTree::resume();
        }
        mStatus = 3;
        if (_69) {
            _69 = false;
            close();
        } else if (mOpenedAnim != 0) {
            mBox.setAnimByName(mOpenedAnim);
            mBox.start(true);
        }
    } else if (mStatus == 1 && mSubBox.isAnimEnd()) {
        setStatusOnOpening();
    }
}

#define MF_FUNCTION setOpenSELabel__Q53scn7subgame6common7boxmenu11ClosableBoxFUl
void ClosableBox::setOpenSELabel(unsigned long label) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 key;
    u32 hash;
    u32 i;
    u32 first;
    u32 limit;

    hash = 0x811C9DDB;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  MF_WORD(0x34)
    after1:
        mflr    r23
        lwz     r18, 0x0(r23)
        lwz     r15, 0x4(r23)
        add     r18, r18, r23
        add     r15, r15, r18
        stw     r18, start
        stw     r15, end
    }
    limit = end - start + 1;
    first = start;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x01000193;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x98)
        opword  0x8BD8AD60
    after2:
        mflr    r28
        lwz     r27, 0x0(r28)
        stw     r27, expected
    }
    hash ^= expected;
    if (hash == 0) {
        mOpenSELabel = label;
    } else {
        asm {
            bl      after3
            opword  0x4503C102
            opword  0x3CE79093
            opword  MF_WORD(0xD0)
        after3:
            mflr    r23
            lwz     r28, 0x8(r23)
            stw     r28, -0x4(r1)
            stw     r23, 0x0(r1)
            stw     r28, -0x4(r1)
            stw     r23, -0x8(r1)
            mtlr    r28
            bl      after4
            opword  MF_WORD(0xF4)
            opword  0x3CFE1A80
            opword  MF_WORD(0xFC)
        after4:
            mflr    r14
            lwz     r15, 0x8(r14)
            stw     r15, key
            lwz     r15, 0x0(r14)
            stw     r14, base
            stw     r15, offset
        }
        offset = offset - 0x3C;
        response = offset ^ key;
        response = response + base;
        asm {
            lwz     r16, response
            mtlr    r16
            blr
        }
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setCloseSELabel__Q53scn7subgame6common7boxmenu11ClosableBoxFUl
void ClosableBox::setCloseSELabel(unsigned long label) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 key;
    u32 hash;
    u32 word;
    u32 last;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  0xE701537F
    after1:
        mflr    r21
        lwz     r23, 0x0(r21)
        stw     r23, expected
        bl      after2
        opword  0x20D4A780
        opword  MF_WORD(0x44)
        opword  MF_WORD(0x48)
        opword  0x88789292
    after2:
        mflr    r16
        lwz     r26, 0x4(r16)
        stw     r26, end
        lwz     r26, 0x8(r16)
        stw     r26, start
    }
    last = end;
    word = start;
    hash = 0x811C9E53;
    for (; word != last; word += 2) {
        hash ^= *(u16*)word;
        hash *= 0x010001D1;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash -= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  0x28EC0090
            opword  0x10526F80
            opword  MF_WORD(0xCC)
        after3:
            mflr    r19
            lwz     r14, 0x8(r19)
            stw     r14, -0x4(r1)
            stw     r19, 0x0(r1)
            stw     r14, -0x4(r1)
            stw     r19, -0x8(r1)
            mtlr    r14
            bl      after4
            opword  MF_WORD(0xF0)
            opword  0xC09E1081
            opword  MF_WORD(0xF8)
        after4:
            mflr    r28
            lwz     r29, 0x8(r28)
            stw     r29, key
            lwz     r29, 0x0(r28)
            stw     r28, base
            stw     r29, offset
        }
        offset = offset ^ 0xF8;
        response = offset - key;
        response = response + base;
        asm {
            lwz     r14, response
            mtlr    r14
            blr
        }
    } else {
        mCloseSELabel = label;
    }
}
#undef MF_FUNCTION

void ClosableBox::stopOpenSE() {
    mOpenSE.stop();
}

#define MF_FUNCTION initialize__Q53scn7subgame6common7boxmenu11ClosableBoxFv
void ClosableBox::initialize() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 key;
    volatile u32 base;
    volatile u32 response;
    u32 first;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x24)
        opword  0xFBEB7A2A
    after1:
        mflr    r24
        lwz     r21, 0x0(r24)
        stw     r21, expected
        bl      after2
        opword  0xF0D91C92
        opword  MF_WORD(0x40)
        opword  0x24A77381
        opword  0x4495A880
    after2:
        mflr    r14
        lwz     r27, 0x4(r14)
        stw     r27, end
        bl      after3
        opword  0x60628F93
        opword  MF_WORD(0x60)
        opword  0xACC23693
        opword  0x68F68F80
    after3:
        mflr    r14
        lwz     r27, 0x4(r14)
        stw     r27, start
    }
    first = start;
    limit = end - first + 1;
    hash = 0x811C9E07;
    closeImmediate();
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(first + i - 1);
        hash *= 0x010001A7;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected != 0) {
        asm {
            bl      after4
            opword  0x38888803
            opword  MF_WORD(0xF4)
        after4:
            mflr    r17
            lwz     r21, 0x4(r17)
            stw     r21, -0x4(r1)
            stw     r17, 0x0(r1)
            stw     r21, -0x4(r1)
            stw     r17, -0x8(r1)
            mtlr    r21
            bl      after5
            opword  MF_WORD(0x118)
            opword  0x0B68FB07
            opword  MF_WORD(0x120)
        after5:
            mflr    r19
            lwz     r23, 0x8(r19)
            stw     r23, key
            lwz     r23, 0x0(r19)
            stw     r19, base
            stw     r23, offset
        }
        response = offset + key;
        response = response + base;
        asm {
            lwz     r22, response
            mtlr    r22
            blr
        }
    }
}
#undef MF_FUNCTION

// TODO: one register differs: the original keeps `expected & ~hash` in r29 (the label's), this puts it in r31.
#define MF_FUNCTION setStatusOnOpening__Q53scn7subgame6common7boxmenu11ClosableBoxFv
void ClosableBox::setStatusOnOpening() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 key;
    volatile u32 base;
    volatile u32 offset;
    volatile u32 response;
    u32 hash;
    u32 label;
    u32 i;
    u32 last;
    u32 limit;

    hash = 0x811C9E07;
    asm {
        bl      after1
        opword  0x8D617607
        opword  0x45FD3B04
        opword  MF_WORD(0x34)
    after1:
        mflr    r22
        lwz     r20, 0x8(r22)
        stw     r20, start
        bl      after2
        opword  MF_WORD(0x48)
    after2:
        mflr    r22
        lwz     r20, 0x0(r22)
        stw     r20, end
    }
    mBox.setAnimByName(mOpenAnim);
    limit = end - start + 1;
    last = end;
    i = -1;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - 1 - i);
        hash *= 0x010001A7;
    }
    mBox.start(false);
    asm {
        bl      after3
        opword  MF_WORD(0xB8)
        opword  0x4ACFD832
    after3:
        mflr    r22
        lwz     r14, 0x0(r22)
        stw     r14, expected
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    label = mOpenSELabel;
    if (label != 0xFFFFFFFF) {
        mOpenSE.start(label);
    }
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    label = (hash & ~expected) | (expected & ~hash);
    hash = __cntlzw(label);
    label = hash >> 5;
    hash = label >> 5;
    hash = label - hash;
    if (hash == 0) {
        asm {
            stw     r18, -0x4(r1)
            bl      after4
            opword  MF_WORD(0x144)
            opword  0x5C0B3481
        after4:
            mflr    r18
            lwz     r25, 0x0(r18)
            stw     r25, 0x0(r1)
            stw     r18, 0x4(r1)
            mtlr    r25
            bl      after5
            opword  MF_WORD(0x164)
            opword  MF_WORD(0x168)
        after5:
            mflr    r19
            stw     r19, base
            lwz     r25, 0x0(r19)
            stw     r25, offset
            lwz     r27, 0x4(r19)
            stw     r27, key
        }
        offset = offset ^ 0x3A;
        response = offset + key;
        response = response + base;
        asm {
            lwz     r26, response
            mtlr    r26
            blr
        }
    } else {
        mStatus = 2;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION setStatusOnClosing__Q53scn7subgame6common7boxmenu11ClosableBoxFv
void ClosableBox::setStatusOnClosing() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 key;
    volatile u32 base;
    volatile u32 offset;
    u32 hash;
    u32 i;
    u32 last;
    u32 limit;

    hash = 0;
    asm {
        bl      after1
        opword  0x94F38293
        opword  0x30331281
        opword  MF_WORD(0x30)
        opword  MF_WORD(0x34)
        opword  0xB870A580
        opword  0x6476AF93
    after1:
        mflr    r25
        lwz     r21, 0x8(r25)
        lwz     r22, 0xC(r25)
        stw     r21, start
        stw     r22, end
    }
    if (isOpened()) {
        AbstractSuspendableTree::suspend();
    }
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
    if (!mSubBox.isEmpty()) {
        mSubBox.setAnimByName(mSubCloseAnim);
        mSubBox.start(true);
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    if (mCloseAnim != 0) {
        mBox.setAnimByName(mCloseAnim);
        mBox.start(false);
    } else if (mOpenAnim != 0) {
        mBox.setAnimByName(mOpenAnim);
        mBox.setFrameRate(-1.0f);
        mBox.start(false);
    }
    hash += hash << 3;
    hash ^= hash >> 17;
    if (mCloseSELabel != 0xFFFFFFFF) {
        mCloseSE.start(mCloseSELabel);
    }
    asm {
        bl      after2
        opword  MF_WORD(0x168)
        opword  0xF430E510
    after2:
        mflr    r27
        lwz     r19, 0x0(r27)
        stw     r19, expected
    }
    hash += hash << 5;
    hash -= expected;
    if (hash == 0) {
        mStatus = 4;
    } else {
        asm {
            bl      after3
            opword  MF_WORD(0x1A4)
            opword  0x7D117505
            opword  0xBC9E0490
            opword  0x542CF990
        after3:
            mflr    r20
            addi    r28, r20, 0x1C
            mtlr    r28
            lwz     r15, 0x0(r20)
            stw     r15, -0x4(r1)
            stw     r28, 0x0(r1)
            stw     r20, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x1D8)
            opword  MF_WORD(0x1DC)
        after4:
            mflr    r17
            lwz     r30, 0x0(r17)
            lwz     r16, 0x4(r17)
            stw     r16, key
            stw     r30, offset
            stw     r17, base
        }
        key = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r30, response
            mtlr    r30
            blr
        }
    }
}
#undef MF_FUNCTION

}}}}  // namespace scn::subgame::common::boxmenu
