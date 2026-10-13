#ifndef STORAGE_UNLOCKSTATE_H
#define STORAGE_UNLOCKSTATE_H

namespace storage {

// TODO: there is at least one more state. theaterRoomOpened and its like test for it.
enum UnlockState {
    UNLOCK_STATE_LOCKED,
    UNLOCK_STATE_UNLOCKED,
    UNLOCK_STATE_2,
    UNLOCK_STATE_3,
};

}  // namespace storage

#endif
