#include "storage/ArenaGameData.h"

#include "metafortress.h"

using scn::step::hero::Kind;

namespace storage {

void ArenaGameData::init() {
    for (int mode = 0; mode < PLAY_MODE_NUM; mode++) {
        for (int rank = 0; rank < RANK_NUM; rank++) {
            mRecords[mode][rank].playerNum = 0;
            mRecords[mode][rank].round = 0;
            mRecords[mode][rank].time = 0;
            for (int i = 0; i < 4; i++) {
                mRecords[mode][rank].kinds[i] = scn::step::hero::KIND_NONE;
            }
        }
    }
}

#define MF_FUNCTION isCleared__Q27storage13ArenaGameDataFv
bool ArenaGameData::isCleared() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    volatile u32 subtrahend;
    volatile u32 offset;
    volatile u32 base;
    volatile u32 response;

    asm {
        bl      ranged
        opword  0xAC894491
        opword  0xA0612493
        opword  MF_WORD(0x2C)
        opword  0x30EECA80
        opword  0x20BEFF80
        opword  MF_WORD(0x38)
        opword  0xD6BAE407
        opword  0x3E4A4406
    ranged:
        mflr    r21
        lwz     r28, 0x14(r21)
        lwz     r20, 0x8(r21)
        stw     r20, end
        stw     r28, start
        li      r27, 1
        lwz     r25, start
        lwz     r26, end
        subf    r26, r25, r26
        addi    r24, r26, 1
        li      r31, 0
    next:
        cmplw   cr4, r27, r24
        beq     cr4, summed
        mulli   r31, r31, 61
        add     r26, r25, r27
        lhz     r26, -1(r26)
        add     r31, r31, r26
        addi    r27, r27, 2
        b       next
    summed:
        bl      stored
        opword  MF_WORD(0x94)
        opword  0xD0E2A8DF
    stored:
        mflr    r28
        lwz     r29, 0(r28)
        stw     r29, expected
        slwi    r26, r31, 3
        add     r31, r31, r26
        srwi    r26, r31, 11
        xor     r31, r31, r26
        slwi    r26, r31, 15
        add     r31, r31, r26
        lwz     r26, expected
        andc    r26, r31, r26
        lwz     r27, expected
        andc    r27, r27, r31
        or      r27, r26, r27
        cntlzw  r31, r27
        srwi    r27, r31, 5
        slwi    r31, r27, 4
        add     r31, r27, r31
        cmpwi   cr4, r31, 0
        bne     cr4, intact
        bl      smashed
        opword  0xAC719B80
        opword  0x90B24D0D
    smashed:
        mflr    r29
        lwz     r23, 4(r29)
        stw     r23, -4(r1)
        stw     r29, 0(r1)
        stw     r23, -4(r1)
        stw     r29, -8(r1)
        mtlr    r23
        bl      located
        opword  MF_WORD(0x118)
        opword  0xF407DB93
        opword  0x40B93993
        opword  0x000A06BD
    located:
        mflr    r20
        lwz     r16, 0(r20)
        lwz     r15, 0xC(r20)
        stw     r15, subtrahend
        stw     r16, offset
        stw     r20, base
    }
    offset = offset - 41;
    response = offset - subtrahend;
    response = response + base;
    asm {
        lwz     r20, response
        mtlr    r20
        blr
    }
    goto done;
intact:
    return mState == 3;
done:;
}
#undef MF_FUNCTION

void ArenaGameData::setTime(ArenaPlayMode mode, ArenaRank rank, u32 round, u32 time, Kind kind0, Kind kind1, Kind kind2, Kind kind3) {
    if (time > 359999) {
        time = 359999;
    }
    int playerNum = 0;
    if (kind0 < scn::step::hero::KIND_NONE) {
        playerNum++;
    }
    if (kind1 < scn::step::hero::KIND_NONE) {
        playerNum++;
    }
    if (kind2 < scn::step::hero::KIND_NONE) {
        playerNum++;
    }
    if (kind3 < scn::step::hero::KIND_NONE) {
        playerNum++;
    }
    mRecords[mode][rank].playerNum = playerNum;
    mRecords[mode][rank].round = round;
    mRecords[mode][rank].time = time;
    mRecords[mode][rank].kinds[0] = kind0;
    mRecords[mode][rank].kinds[1] = kind1;
    mRecords[mode][rank].kinds[2] = kind2;
    mRecords[mode][rank].kinds[3] = kind3;
}

int ArenaGameData::setTime(ArenaPlayMode mode, u32 round, u32 time, Kind kind0, Kind kind1, Kind kind2, Kind kind3) {
    if (time > 359999) {
        time = 359999;
    }
    int result = RANK_NUM;
    int rank = RANK_NUM;
    if (time != 0) {
        if (mState == 0) {
            mState = 1;
        }
        for (rank = 0; rank < RANK_NUM; rank++) {
            if (mRecords[mode][rank].round == 0 || round > mRecords[mode][rank].round || mRecords[mode][rank].time == 0 || time < mRecords[mode][rank].time) {
                break;
            }
        }
    } else if (round != 0) {
        for (rank = 0; rank < RANK_NUM; rank++) {
            if (mRecords[mode][rank].round == 0 || round > mRecords[mode][rank].round) {
                break;
            }
        }
    }
    if (rank < RANK_NUM) {
        for (int i = RANK_NUM - 1; i > rank; i--) {
            setRecord(mode, ArenaRank(i), getRecord(mode, ArenaRank(i - 1)));
        }
        setTime(mode, ArenaRank(rank), round, time, kind0, kind1, kind2, kind3);
        result = rank;
    }
    return result;
}

u32 ArenaGameData::getRound(ArenaPlayMode mode, ArenaRank rank) {
    return mRecords[mode][rank].round;
}

u32 ArenaGameData::getTime(ArenaPlayMode mode, ArenaRank rank) {
    return mRecords[mode][rank].time;
}

Kind ArenaGameData::getKind(ArenaPlayMode mode, ArenaRank rank, int index) {
    return mRecords[mode][rank].kinds[index];
}

void ArenaGameData::setRecord(ArenaPlayMode mode, ArenaRank rank, ArenaOneRecord record) {
    mRecords[mode][rank] = record;
}

ArenaGameData::ArenaOneRecord ArenaGameData::getRecord(ArenaPlayMode mode, ArenaRank rank) {
    return mRecords[mode][rank];
}

}  // namespace storage
