#ifndef APP_BACKUPFILEACCESSOR_H
#define APP_BACKUPFILEACCESSOR_H

#include "app/SaveInfo.h"
#include "storage/SubGameKind.h"
#include "storage/UnlockState.h"
#include "types.h"

namespace storage {
class BackupFileData;
}

namespace app {

class BackupFileAccessor {
public:
    class GameMode {
    public:
        u32 clearPercentage() const;
        bool cleared() const;
        bool completed() const;

    private:
        u8 _0[0x10];
    };

    static void Save(SaveInfoLayoutKind kind);

    BackupFileAccessor();
    BackupFileAccessor(u32 file);

    bool completed() const;
    bool isBlank() const;
    bool extraModeOpened() const;
    bool theArenaOpened() const;
    bool theArenaExtraOpened() const;
    storage::UnlockState subGameState(storage::SubGameKind kind) const;
    bool theArenaCleared() const;
    bool theArenaExtraCleared() const;
    storage::UnlockState extraModeState() const;
    void setExtraModeState(storage::UnlockState state);
    storage::UnlockState theArenaState() const;
    void setTheArenaState(storage::UnlockState state);
    storage::UnlockState theArenaExtraState() const;
    void setTheArenaExtraState(storage::UnlockState state);
    storage::UnlockState theArenaCharaState() const;
    storage::UnlockState theArenaExtraCharaState() const;
    storage::UnlockState soundRoomState() const;
    void setSoundRoomState(storage::UnlockState state);
    storage::UnlockState soundRoomCompleteState() const;
    void setSoundRoomCompleteState(storage::UnlockState state);
    storage::UnlockState theaterRoomState() const;
    void setTheaterRoomState(storage::UnlockState state);
    storage::UnlockState theaterRoomCompleteState() const;
    void setTheaterRoomCompleteState(storage::UnlockState state);
    void updateUnlockState();

private:
    storage::BackupFileData* mData;
    u32 _4;
    GameMode mMain;
    GameMode mExtra;
};

}

#endif
