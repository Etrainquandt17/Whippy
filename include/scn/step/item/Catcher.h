#ifndef SCN_STEP_ITEM_CATCHER_H
#define SCN_STEP_ITEM_CATCHER_H

#include "hel/math/Vector2.h"
#include "scn/step/item/GetInfo.h"

namespace scn {
namespace step {
namespace item {

// TODO: members and the other functions.
class Catcher {
public:
    void addItem(const GetInfo& info);
    hel::math::Vector2 getPos() const;
};

}}}  // namespace scn::step::item

#endif
