#ifndef SCN_STEP_CARRYITEM_MANAGER_H
#define SCN_STEP_CARRYITEM_MANAGER_H

#include "scn/step/map/BinCarryItemKind.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace hel {
namespace geo {
class Rect;
}
namespace math {
class Vector2;
}}  // namespace hel::math

namespace scn {
namespace step {
namespace carryitem {

class CarryItem;

class Manager {
public:
    bool isExistObj(map::BinCarryItemKind kind, u32);
    util::ObjRefHandle<CarryItem> chkCollideSwitch(const hel::math::Vector2& pos);
    util::ObjRefHandle<CarryItem> chkCollide(const hel::math::Vector2& pos, u64 uid);
    u32 countExistObjInRect(const hel::geo::Rect& rect);
    void killAllObj();
};

}}}  // namespace scn::step::carryitem

#endif
