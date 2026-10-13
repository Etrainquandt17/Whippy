#ifndef STORAGE_ARENAGAMEDATA_H
#define STORAGE_ARENAGAMEDATA_H

#include "scn/step/hero/Kind.h"
#include "types.h"

namespace storage {

class ArenaGameData {
public:
    enum ArenaPlayMode {
        PLAY_MODE_NUM = 2,
    };

    enum ArenaRank {
        RANK_NUM = 3,
    };

    struct ArenaOneRecord {
        u32 playerNum;
        u32 round;
        u32 time;
        scn::step::hero::Kind kinds[4];
    };

    void init();
    bool isCleared();
    void setTime(ArenaPlayMode mode, ArenaRank rank, u32 round, u32 time, scn::step::hero::Kind kind0, scn::step::hero::Kind kind1, scn::step::hero::Kind kind2,
                 scn::step::hero::Kind kind3);
    int setTime(ArenaPlayMode mode, u32 round, u32 time, scn::step::hero::Kind kind0, scn::step::hero::Kind kind1, scn::step::hero::Kind kind2,
                scn::step::hero::Kind kind3);
    u32 getRound(ArenaPlayMode mode, ArenaRank rank);
    u32 getTime(ArenaPlayMode mode, ArenaRank rank);
    scn::step::hero::Kind getKind(ArenaPlayMode mode, ArenaRank rank, int index);
    void setRecord(ArenaPlayMode mode, ArenaRank rank, ArenaOneRecord record);
    ArenaOneRecord getRecord(ArenaPlayMode mode, ArenaRank rank);

private:
    u32 _0;
    int mState;
    ArenaOneRecord mRecords[PLAY_MODE_NUM][RANK_NUM];
};

}

#endif
