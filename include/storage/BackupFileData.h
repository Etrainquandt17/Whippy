#ifndef STORAGE_BACKUPFILEDATA_H
#define STORAGE_BACKUPFILEDATA_H

#include "storage/StoryMode.h"
#include "types.h"

namespace storage {

class StoryData;

struct TheaterRoomData {
    u32 _0;
    u32 _4;
    int _8;
};

class BackupFileData {
public:
    TheaterRoomData& theaterRoomData();
    StoryData& storyData(StoryMode mode);
};

}

#endif
