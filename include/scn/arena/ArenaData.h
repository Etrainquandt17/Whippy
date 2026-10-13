#ifndef SCN_ARENA_ARENADATA_H
#define SCN_ARENA_ARENADATA_H

#include "scn/step/hero/AbilityKind.h"
#include "scn/step/hero/Kind.h"
#include "seq/EntryInfo.h"
#include "storage/ArenaGameKind.h"
#include "types.h"

namespace scn {
namespace arena {

class ArenaData {
public:
    // TODO: name the values.
    enum ItemRemainder {
        ITEM_REMAINDER_0,
        ITEM_REMAINDER_1,
        ITEM_REMAINDER_2,
    };

    // TODO: name the values.
    enum BoxState {
        BOX_STATE_0,
        BOX_STATE_1,
        BOX_STATE_2,
        BOX_STATE_3,
    };

    class Player {
    public:
        struct Entry {
            bool mIsEntry;
            step::hero::Kind mKind;
            step::hero::AbilityKind mAbility;
        };

        static Player Create();

        void setEntryInfo(seq::EntryInfo info);
        seq::EntryInfo getEntryInfo();
        void reset(u32 index);

    private:
        u32 mNum;
        Entry mEntries[4];
    };

    class Item {
    public:
        static Item Create(storage::ArenaGameKind kind);

        void reset(storage::ArenaGameKind kind);
        void setTomatoRemainder(u32 index, ItemRemainder remainder);
        ItemRemainder getTomatoRemainder(u32 index) const;
        void updateTomatoRemainder(u32 index);
        void setBoxState(BoxState state);

    private:
        u32 mTomatoNum;
        ItemRemainder mTomatoRemainders[4];
        BoxState mBoxState;
    };

    class BossSet {
    public:
        struct Boss {
            int mBossId;
            int mMapKind;
            step::hero::AbilityKind mAbilities[2];
        };

        static BossSet Create(storage::ArenaGameKind kind);

        int mapKind() const;
        void next();
        bool isEnd() const;
        bool isNextEnd() const;
        bool isRoom2() const;
        bool isNextRoom2() const;
        int getBossId() const;
        step::hero::AbilityKind getAbilityKind(u32 index) const;
        step::hero::AbilityKind getNextAbilityKind(u32 index) const;
        void reset(storage::ArenaGameKind kind);
        step::hero::AbilityKind getNextAbility();
        void setAbility(step::hero::AbilityKind kind);
        bool useAbility(step::hero::AbilityKind kind);
        bool chkEnd(u32 index) const;
        bool chkRoom2(u32 index) const;

    private:
        u32 mNum;
        u32 mIndex;
        Boss mBosses[16];
        step::hero::AbilityKind mAbilities[6];
        u32 mAbilityIndex;
    };

    static ArenaData Create(storage::ArenaGameKind kind);

    void reset();
    storage::ArenaGameKind gameKind() const;
    void setTime(u32 time);
    u32 getTime() const;
    void incTime();
    void setHpRatio(u32 index, f32 ratio);
    f32 getHpRatio(u32 index);
    void setHp(step::hero::Kind kind, u32 hp);
    u32 getHp(step::hero::Kind kind);
    bool isHpReady();

private:
    Player mPlayer;
    Item mItem;
    BossSet mBossSet;
    storage::ArenaGameKind mGameKind;
    u32 mTime;
    u32 mHp[7];
    f32 mHpRatio[2];
};

}
}

#endif
