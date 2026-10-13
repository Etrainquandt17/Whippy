#ifndef SCN_STEP_ITEM_MAPCOLL_H
#define SCN_STEP_ITEM_MAPCOLL_H

#include "hel/math/Vector2.h"
#include "scn/step/chara/MapCollResult.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {

class Item;

// TODO: members and the other functions.
class MapColl {
public:
    MapColl(Item& item);

    void setValid(bool isValid);
    bool isHit() const;
    hel::math::Vector2 normal() const;
    bool isOnCliffEdge() const;
    bool isCliffEdgeRight() const;
    bool isDead() const;
    void drawDebug() const;
};

}}}  // namespace scn::step::item

#endif
