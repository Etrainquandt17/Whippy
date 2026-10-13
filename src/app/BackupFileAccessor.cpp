#include "app/BackupFileAccessor.h"

#include "metafortress.h"
#include "storage/BackupFileData.h"

using storage::UNLOCK_STATE_LOCKED;
using storage::UNLOCK_STATE_UNLOCKED;

namespace app {

#define MF_FUNCTION updateUnlockState__Q23app18BackupFileAccessorFv
void BackupFileAccessor::updateUnlockState() {
    volatile u32 start;
    volatile u32 end;
    volatile u32 expected;
    u32 word;
    u32 last;
    u32 hash;

    asm {
        bl      after1
        opword  0xC0E0BF90
        opword  MF_WORD(0x28)
        opword  MF_WORD(0x2C)
    after1:
        mflr    r29
        lwz     r25, 0x8(r29)
        stw     r25, start
        lwz     r19, 0x4(r29)
        stw     r19, end
    }
    if (mData->theaterRoomData()._8 == 2 && theaterRoomState() == UNLOCK_STATE_LOCKED) {
        setTheaterRoomState(UNLOCK_STATE_UNLOCKED);
    }
    hash = 0;
    if (mMain.cleared()) {
        if (theArenaState() == UNLOCK_STATE_LOCKED) {
            setTheArenaState(UNLOCK_STATE_UNLOCKED);
        }
        if (soundRoomState() == UNLOCK_STATE_LOCKED) {
            setSoundRoomState(UNLOCK_STATE_UNLOCKED);
        }
        if (mMain.clearPercentage() >= 70 && extraModeState() == UNLOCK_STATE_LOCKED) {
            setExtraModeState(UNLOCK_STATE_UNLOCKED);
        }
    }
    last = end;
    word = start;
    if (mExtra.cleared() && theArenaExtraState() == UNLOCK_STATE_LOCKED) {
        setTheArenaExtraState(UNLOCK_STATE_UNLOCKED);
    }
    if (mExtra.completed() && soundRoomCompleteState() == UNLOCK_STATE_LOCKED) {
        setSoundRoomCompleteState(UNLOCK_STATE_UNLOCKED);
    }
    word -= 2;
    for (;;) {
        word += 2;
        if (word == last) {
            break;
        }
        hash *= 151;
        hash += *(u16*)word;
    }
    asm {
        bl      after2
        opword  MF_WORD(0x170)
        opword  0xB59B4C1F
    after2:
        mflr    r18
        lwz     r21, 0x0(r18)
        stw     r21, expected
    }
    if ((hash - expected != 0 || (mMain.completed() && mExtra.completed())) && theArenaCleared() && theArenaExtraCleared() &&
        theaterRoomCompleteState() == UNLOCK_STATE_LOCKED) {
        setTheaterRoomCompleteState(UNLOCK_STATE_UNLOCKED);
    }
}
#undef MF_FUNCTION

}
