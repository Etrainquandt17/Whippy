#ifndef SCN_SUBGAME_SETSUNA_INFO_MATCHRESULT_H
#define SCN_SUBGAME_SETSUNA_INFO_MATCHRESULT_H

#include "scn/subgame/setsuna/chara/ShootResult.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace setsuna {
namespace info {

struct MatchResult {
    static MatchResult Create(const chara::ShootResult& shootResult);
    static MatchResult Create();

    u32 addedJustBonusScore() const;
    u32 addedAllBonusScore() const;

    bool _0;
    u32 _4;
    bool _8;
    u32 _C;
    bool _10;
};

}
}
}
}

#endif
