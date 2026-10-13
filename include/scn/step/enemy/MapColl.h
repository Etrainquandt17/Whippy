#ifndef SCN_STEP_ENEMY_MAPCOLL_H
#define SCN_STEP_ENEMY_MAPCOLL_H

#include "hel/math/Vector2.h"
#include "scn/step/chara/MapCollResult.h"

namespace mcoll {
namespace detail {

class ShapeDiamondContext;

}}  // namespace mcoll::detail

namespace scn {
namespace step {
namespace enemy {

class Enemy;

// TODO: members.
class MapColl {
public:
    MapColl(Enemy& enemy);

    chara::MapCollResult result() const;
    bool isHitAll() const;
    void setValid(bool isValid);
    hel::math::Vector2 floorNormal() const;
    void setPassInvisibleLand(bool flag);
    void setPassThroughLandState(bool flag);
    void reset();
    void changeActorShape(const mcoll::detail::ShapeDiamondContext& shape);
};

}}}  // namespace scn::step::enemy

#endif
