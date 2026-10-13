#ifndef SCN_STEP_CARRYITEM_MAPCOLL_H
#define SCN_STEP_CARRYITEM_MAPCOLL_H

#include "scn/step/chara/MapCollResult.h"
#include "types.h"

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

// TODO: members.
class MapColl {
public:
    MapColl(CarryItem& carryItem);

    void procMapColl();
    void setValid(bool isValid);
    void setPassInvisibleLand(bool isPass);
    void setIgnoreInvisibleRoof(bool isIgnore);
    void reset();
    chara::MapCollResult result() const;
    void drawDebug() const;
};

}}}  // namespace scn::step::carryitem

#endif
