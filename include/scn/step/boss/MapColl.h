#ifndef SCN_STEP_BOSS_MAPCOLL_H
#define SCN_STEP_BOSS_MAPCOLL_H

#include "scn/step/chara/MapCollResult.h"
#include "types.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

// TODO: members.
class MapColl {
public:
    MapColl(Boss& boss);

    void initActor();
    void procMapColl();
    void reset();
    chara::MapCollResult result() const;
    void setActorSetting(f32, f32, f32);
    void setValid(bool isValid);
};

}}}  // namespace scn::step::boss

#endif
