#ifndef SCN_STEP_WEAPON_MAPCOLL_H
#define SCN_STEP_WEAPON_MAPCOLL_H

#include "hel/math/Vector2.h"
#include "mcoll/detail/ShapeDiamondContext.h"
#include "scn/step/chara/MapCollResult.h"
#include "types.h"

namespace scn {
namespace step {
namespace weapon {

class Weapon;

// TODO: members and the other functions.
class MapColl {
public:
    MapColl(Weapon& weapon);

    void procMapColl();
    void setValid(bool isValid);
    void reset();
    bool isDamageField() const;
    void setFixFlag(bool flag);
    void initActor();
    void setGroundMode(bool isGroundMode);
    bool isHit() const;
    void setValidLandConstraint(bool isValid);
    void changeActorShape(const mcoll::detail::ShapeDiamondContext& shape);
    chara::MapCollResult result() const;
    hel::math::Vector2 normal() const;
    hel::math::Vector2 intersectPos() const;
};

}
}
}

#endif
