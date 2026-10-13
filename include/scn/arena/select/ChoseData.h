#ifndef SCN_ARENA_SELECT_CHOSEDATA_H
#define SCN_ARENA_SELECT_CHOSEDATA_H

#include "hel/common/Array.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/Kind.h"
#include "types.h"

namespace scn {
namespace arena {

class ArenaData;

namespace select {

class ChoseData {
public:
    struct PlayerData {
        void initKind(step::hero::Kind kind);
        void initPlayer(u32 player);
        void init();

        bool mIsEntry;
        bool mIsNG;
        step::hero::Kind mDecide;
        step::hero::Kind mSelect;
    };

    // TODO: this is most likely scn::arena::ArenaData::Player, which setArenaDataPlayer reads from the front
    // of the ArenaData.
    struct ArenaDataPlayer {
        struct Entry {
            bool mIsEntry;
            step::hero::Kind mKind;
            step::hero::AbilityKind mAbility;
        };

        u32 mNum;
        Entry mEntries[4];
    };

    void init();
    void init(u32 player);
    void setArenaDataPlayer(const ArenaData& data);
    ArenaDataPlayer getArenaDataPlayer();
    u32 entryNum();
    u32 entryBit();
    void entry(u32 player);
    bool isEntry(u32 player);
    step::hero::Kind getSelect(u32 player);
    void prev(u32 player);
    void next(u32 player);
    void decide(u32 player);
    void cancel(u32 player);
    step::hero::Kind getDecide(u32 player);
    bool isDecide(u32 player);
    bool isAllDecide();
    bool isNG(u32 player);
    bool isRetire(u32 player);
    void checkData();
    u32 getSelectIdx(u32 player);
    u32 getKindToIdx(step::hero::Kind kind);
    step::hero::Kind getIdxToKind(u32 player, u32 idx);
    bool chkAllKind(u32 player, step::hero::Kind kind);

private:
    u32 mEntryNum;
    u32 _4;
    PlayerData mPlayers[4];
};

}}}  // namespace scn::arena::select

#endif
