#define HEL_COMMON_MUTABLEARRAY_ADD_IN_CLASS

#include "info/sequence/Sequence.h"

#include "hel/common/FixedString.h"
#include "info/sequence/Command.h"
#include "lyt/Layout.h"
#include "metafortress.h"
#include "std/tr1/bind.h"
#include "util/Delegate.h"
#include "util/FrameCounter.h"

namespace info {
namespace sequence {

class CommandAnim : public Command {
public:
    CommandAnim(lyt::Layout& layout, const char* name) : mLayout(layout), mName(name) {}
    virtual ~CommandAnim() {}
    virtual void start() { mLayout.play(mName); }
    virtual void proc() {
        if (mLayout.isAnimEnd()) {
            finish();
        }
    }

private:
    lyt::Layout& mLayout;
    hel::common::FixedString<384> mName;
};

class CommandAnimAsync : public Command {
public:
    CommandAnimAsync(lyt::Layout& layout, const char* name) : mLayout(layout), mName(name) {}
    virtual ~CommandAnimAsync() {}
    virtual void start() {
        mLayout.play(mName);
        finish();
    }

private:
    lyt::Layout& mLayout;
    hel::common::FixedString<384> mName;
};

class CommandBranch : public Command {
public:
    CommandBranch(const util::Delegate<bool(), 64>& condition, Sequence& onTrue, Sequence& onFalse)
        : mCondition(condition)
        , mOnTrue(onTrue)
        , mOnFalse(onFalse) {}
    virtual void start() {
        if (mCondition()) {
            mOnTrue.start();
        } else {
            mOnFalse.start();
        }
        finish();
    }

private:
    util::Delegate<bool(), 64> mCondition;
    Sequence& mOnTrue;
    Sequence& mOnFalse;
};

class CommandCall : public Command {
public:
    CommandCall(const util::Delegate<void(), 64>& function) : mFunction(function) {}
    virtual void start() {
        mFunction();
        finish();
    }

private:
    util::Delegate<void(), 64> mFunction;
};

class CommandCheckPoint : public Command {
public:
    CommandCheckPoint(const char* name) : mName(name) {}
    virtual void start() {}

private:
    const char* mName;
};

class CommandFlag : public Command {
public:
    CommandFlag(bool& flag) : mFlag(flag) {}
    virtual void start() {
        mFlag = true;
        finish();
    }

private:
    bool& mFlag;
};

}}  // namespace info::sequence

// Read here and not at the top: the order of the tables in .data depends on where util::Delegate<void (), 64>
// is first needed.
#include "util/IntervalTimer.h"

namespace info {
namespace sequence {

class CommandInterval : public Command {
public:
    CommandInterval(u32 interval, const util::Delegate<bool(), 64>& function) : mTimer(interval), mFunction(function) {}
    virtual void start() { mTimer.start(util::Delegate<void(), 64>()); }
    virtual void proc() {
        mTimer.update();
        if (mTimer.trigger() && mFunction()) {
            finish();
        }
    }

private:
    util::IntervalTimer mTimer;
    util::Delegate<bool(), 64> mFunction;
};

class CommandProc : public Command {
public:
    CommandProc(const util::Delegate<bool(), 64>& function) : mFunction(function) {}
    virtual void proc() {
        if (mFunction()) {
            finish();
        }
    }

private:
    util::Delegate<bool(), 64> mFunction;
};

class CommandRun : public Command {
public:
    CommandRun(Sequence& sequence) : mSequence(sequence) {}
    virtual void start() {
        mSequence.start();
        finish();
    }

private:
    Sequence& mSequence;
};

class CommandWait : public Command {
public:
    CommandWait(u32 frame) : mCounter(frame) {}
    virtual void start() { mCounter.reset(); }
    virtual void proc() {
        mCounter.advance();
        if (mCounter.isEnd()) {
            finish();
        }
    }

private:
    util::FrameCounter mCounter;
};

class CommandWaitAnimEnd : public Command {
public:
    CommandWaitAnimEnd(lyt::Layout& layout) : mLayout(layout) {}
    virtual ~CommandWaitAnimEnd() {}
    virtual void proc() {
        if (mLayout.isAnimEnd()) {
            finish();
        }
    }

private:
    lyt::Layout& mLayout;
};

Sequence::Sequence(mem::IAllocator& allocator)
    : mAllocator(allocator)
    , mIndex(-1)
    , mIsRunning(false) {
}

Sequence::~Sequence() {
    clear();
}

void Sequence::update() {
    if (mIsRunning) {
        Command* command = mCommands[mIndex];
        command->proc();
        if (command->isFinished()) {
            nextCommand();
        }
    }
}

#define MF_FUNCTION anim__Q34info8sequence8SequenceFRQ23lyt6LayoutPCc
Sequence& Sequence::anim(lyt::Layout& layout, const char* name) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 offset;
    volatile u32 addend;
    volatile u32 base;
    volatile u32 response;
    u32 i;
    u32 last;
    u32 limit;
    u32 hash;

    hash = 0;
    asm {
        bl      after1
        opword  MF_WORD(0x30)
        opword  0x8AD287AA
    after1:
        mflr    r20
        lwz     r21, 0x0(r20)
        stw     r21, expected
        bl      after2
        opword  MF_WORD(0x48)
        opword  MF_WORD(0x4C)
        opword  0xE92EF605
        opword  0xACDC7081
    after2:
        mflr    r25
        lwz     r15, 0x0(r25)
        add     r15, r15, r25
        stw     r15, start
        lwz     r21, 0x4(r25)
        add     r15, r15, r21
        stw     r15, end
    }
    mCommands.add(new (alloc<CommandAnim>()) CommandAnim(layout, name));
    limit = end - start + 1;
    i = 1;
    last = end - 1;
    for (;;) {
        if (i == limit) {
            break;
        }
        hash *= 37;
        hash += *(u16*)(last - i);
        i += 2;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    if (hash - expected == 0) {
        return *this;
    }
    asm {
        bl      after3
        opword  0x9ED5DC01
        opword  MF_WORD(0x140)
    after3:
        mflr    r26
        lwz     r27, 0x4(r26)
        stw     r27, -0x4(r1)
        stw     r26, 0x0(r1)
        stw     r27, -0x4(r1)
        stw     r26, -0x8(r1)
        mtlr    r27
        bl      after4
        opword  MF_WORD(0x164)
        opword  MF_WORD(0x168)
    after4:
        mflr    r23
        stw     r23, base
        lwz     r29, 0x0(r23)
        stw     r29, offset
        lwz     r26, 0x4(r23)
        stw     r26, addend
    }
    offset = offset + 0xB3;
    response = offset ^ addend;
    response = response + base;
    asm {
        lwz     r22, response
        mtlr    r22
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION animAsync__Q34info8sequence8SequenceFRQ23lyt6LayoutPCc
Sequence& Sequence::animAsync(lyt::Layout& layout, const char* name) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 addend;
    volatile u32 offset;
    volatile u32 response;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0xE8B87891
        opword  0xD0AA0E80
        opword  MF_WORD(0x38)
        opword  0xCC556481
    after1:
        mflr    r15
        lwz     r18, 0x0(r15)
        lwz     r22, 0xc(r15)
        add     r22, r18, r22
        stw     r18, start
        stw     r22, end
    }
    hash = 0x811C9E53;
    asm {
        bl      after2
        opword  MF_WORD(0x64)
        opword  0x3E888DBD
    after2:
        mflr    r29
        lwz     r18, 0x0(r29)
        stw     r18, expected
    }
    mCommands.add(new (alloc<CommandAnimAsync>()) CommandAnimAsync(layout, name));
    last = end;
    word = start;
    word -= 2;
    while (word != last - 2) {
        word += 2;
        hash ^= *(u16*)word;
        hash *= 0x010001D1;
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    hash ^= expected;
    if (hash == 0) {
        return *this;
    }
    asm {
        bl      after3
        opword  MF_WORD(0x138)
        opword  0x7724320A
        opword  0x40C56381
    after3:
        mflr    r30
        addi    r14, r30, 0x18
        mtlr    r14
        lwz     r21, 0x0(r30)
        stw     r21, -0x4(r1)
        stw     r14, 0x0(r1)
        stw     r30, 0x4(r1)
        blrl
        bl      after4
        opword  MF_WORD(0x168)
        opword  MF_WORD(0x16C)
    after4:
        mflr    r18
        lwz     r23, 0x0(r18)
        stw     r18, base
        lwz     r26, 0x4(r18)
        stw     r23, offset
        stw     r26, addend
    }
    offset = offset + 0x65;
    response = offset - addend;
    response = response + base;
    asm {
        lwz     r20, response
        mtlr    r20
        blr
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION wait__Q34info8sequence8SequenceFUl
Sequence& Sequence::wait(u32 frame) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 response;
    volatile u32 addend;
    volatile u32 offset;
    volatile u32 base;
    u32 last;
    u32 i;
    u32 limit;
    u32 hash;

    asm {
        bl      after1
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
        opword  0xF069C790
        opword  0x54D89692
    after1:
        mflr    r17
        lwz     r27, 0x0(r17)
        add     r27, r27, r17
        stw     r27, start
        lwz     r29, 0x4(r17)
        add     r27, r27, r29
        stw     r27, end
    }
    limit = end - start + 1;
    last = end;
    asm {
        bl      after2
        opword  MF_WORD(0x6C)
        opword  0x782AFA42
    after2:
        mflr    r24
        lwz     r27, 0x0(r24)
        stw     r27, expected
    }
    mCommands.add(new (alloc<CommandWait>()) CommandWait(frame));
    hash = 0x811C9E07;
    i = -1;
    last--;
    for (;;) {
        i += 2;
        if (i == limit) {
            break;
        }
        hash ^= *(u16*)(last - i);
        hash *= 0x010001A7;
    }
    hash ^= expected;
    if (hash != 0) {
        asm {
            bl      after3
            opword  MF_WORD(0x120)
            opword  0xC4265980
            opword  0x28B86A81
            opword  0x64B79191
        after3:
            mflr    r28
            addi    r14, r28, 0x1c
            mtlr    r14
            lwz     r19, 0x0(r28)
            stw     r19, -0x4(r1)
            stw     r14, 0x0(r1)
            stw     r28, 0x4(r1)
            blrl
            bl      after4
            opword  MF_WORD(0x154)
            opword  0x44F78390
            opword  MF_WORD(0x15C)
        after4:
            mflr    r18
            stw     r18, base
            lwz     r27, 0x0(r18)
            stw     r27, offset
            lwz     r28, 0x8(r18)
            stw     r28, addend
        }
        offset = offset + 0x32;
        addend = 0;
        response = offset;
        response = response + base;
        asm {
            lwz     r15, response
            mtlr    r15
            blr
        }
    } else {
        return *this;
    }
}
#undef MF_FUNCTION

#define MF_FUNCTION wait__Q34info8sequence8SequenceFRCQ33std3tr114function_Fv_b_
Sequence& Sequence::wait(const std::tr1::function<bool()>& function) {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 base;
    volatile u32 response;
    volatile u32 offset;
    volatile u32 addend;
    u16* word;
    u16* last;
    u32 hash;

    hash = 0xB3;
    asm {
        bl      after1
        opword  MF_WORD(0x2C)
        opword  0x2DBDE198
    after1:
        mflr    r27
        lwz     r19, 0x0(r27)
        stw     r19, expected
        bl      after2
        opword  0x2C053507
        opword  MF_WORD(0x48)
    after2:
        mflr    r21
        lwz     r14, 0x4(r21)
        stw     r14, end
        bl      after3
        opword  0x1DA5EF02
        opword  MF_WORD(0x60)
        opword  0x70301A81
        opword  0x18E4B380
    after3:
        mflr    r21
        lwz     r14, 0x4(r21)
        stw     r14, start
    }
    last = (u16*)end;
    word = (u16*)start;
    mCommands.add(new (alloc<CommandProc>()) CommandProc(function));
    word--;
    for (;;) {
        word++;
        if (word == last) {
            break;
        }
        hash = *word ^ ((hash << 4) ^ (hash >> 28));
    }
    hash += hash << 13;
    hash ^= hash >> 7;
    hash += hash << 3;
    hash ^= hash >> 17;
    hash += hash << 5;
    if (hash == expected) {
        return *this;
    }
    asm {
        bl      after4
        opword  0xAEF7350C
        opword  0xF8ED9493
        opword  0xF8342B90
        opword  MF_WORD(0x150)
    after4:
        mflr    r27
        lwz     r20, 0xc(r27)
        stw     r20, -0x4(r1)
        stw     r27, 0x0(r1)
        stw     r20, -0x4(r1)
        stw     r27, -0x8(r1)
        mtlr    r20
        bl      after5
        opword  MF_WORD(0x174)
        opword  MF_WORD(0x178)
    after5:
        mflr    r14
        lwz     r18, 0x4(r14)
        stw     r18, addend
        lwz     r18, 0x0(r14)
        stw     r14, base
        stw     r18, offset
    }
    response = offset - addend;
    response = response + base;
    asm {
        lwz     r17, response
        mtlr    r17
        blr
    }
}
#undef MF_FUNCTION

Sequence& Sequence::waitAnimEnd(lyt::Layout& layout) {
    mCommands.add(new (alloc<CommandWaitAnimEnd>()) CommandWaitAnimEnd(layout));
    return *this;
}

Sequence& Sequence::call(const std::tr1::function<void()>& function) {
    mCommands.add(new (alloc<CommandCall>()) CommandCall(function));
    return *this;
}

Sequence& Sequence::flag(bool& flag) {
    mCommands.add(new (alloc<CommandFlag>()) CommandFlag(flag));
    return *this;
}

Sequence& Sequence::proc(const std::tr1::function<bool()>& function) {
    mCommands.add(new (alloc<CommandProc>()) CommandProc(function));
    return *this;
}

Sequence& Sequence::interval(u32 interval, const std::tr1::function<bool()>& function) {
    mCommands.add(new (alloc<CommandInterval>()) CommandInterval(interval, function));
    return *this;
}

Sequence& Sequence::checkPoint(const char* name) {
    mCommands.add(new (alloc<CommandCheckPoint>()) CommandCheckPoint(name));
    return *this;
}

Sequence& Sequence::run(Sequence& sequence) {
    mCommands.add(new (alloc<CommandRun>()) CommandRun(sequence));
    return *this;
}

Sequence& Sequence::branch(const std::tr1::function<bool()>& function, Sequence& onTrue, Sequence& onFalse) {
    mCommands.add(new (alloc<CommandBranch>()) CommandBranch(function, onTrue, onFalse));
    return *this;
}

#define MF_FUNCTION start__Q34info8sequence8SequenceFv
void Sequence::start() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 i;
    u32 base;
    u32 limit;
    u32 hash;

    hash = 0xBF;
    mIndex = -1;
    asm {
        bl      after1
        opword  0x8FEAF405
        opword  MF_WORD(0x2C)
        opword  0x40A27891
        opword  0xEC67AF0C
        opword  MF_WORD(0x38)
        opword  0xDF0B5701
    after1:
        mflr    r19
        lwz     r24, 0x4(r19)
        lwz     r15, 0x10(r19)
        stw     r15, end
        stw     r24, start
        bl      after2
        opword  MF_WORD(0x58)
        opword  0x046F153A
    after2:
        mflr    r24
        lwz     r23, 0x0(r24)
        stw     r23, expected
    }
    limit = end - start + 1;
    i = 1;
    base = start;
    mCommands.forEach(std::tr1::bind(&Command::reset, std::tr1::placeholders::_1));
    for (; i != limit; i += 2) {
        hash = ((hash << 4) ^ (hash >> 28)) ^ *(u16*)(base + i - 1);
    }
    hash += hash << 3;
    hash ^= hash >> 11;
    hash += hash << 15;
    mIsRunning = hash - expected == 0;
    nextCommand();
}
#undef MF_FUNCTION

void Sequence::stop() {
    mIsRunning = false;
}

bool Sequence::running() const {
    return mIsRunning;
}

bool Sequence::isEnd() const {
    return !mIsRunning;
}

void Sequence::clear() {
    stop();
    for (u32 i = 0; i < mCommands.count(); i++) {
        mCommands[i]->~Command();
        mAllocator.allocatorFree(mCommands[i]);
    }
    mCommands.clear();
}

void Sequence::nextCommand() {
    Command* command;
    do {
        mIndex++;
        if (mIndex == mCommands.count()) {
            stop();
            break;
        }
        command = mCommands[mIndex];
        command->start();
    } while (command->isFinished());
}

}}  // namespace info::sequence
