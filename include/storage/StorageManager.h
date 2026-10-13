#ifndef STORAGE_STORAGEMANAGER_H
#define STORAGE_STORAGEMANAGER_H

#include "types.h"

namespace storage {

class BackupFileData;
class VolatileData;

class StorageManager {
public:
    BackupFileData& selectedBackupFileData();
    void onSoftReset();
    VolatileData& volatileData();

private:
    u8 _0[0x10];
};

}  // namespace storage

#endif
