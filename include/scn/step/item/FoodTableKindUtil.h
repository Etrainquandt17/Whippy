#ifndef SCN_STEP_ITEM_FOODTABLEKINDUTIL_H
#define SCN_STEP_ITEM_FOODTABLEKINDUTIL_H

#include "scn/step/item/FoodTableKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {

class FoodTableKindUtil {
public:
    // TODO: the result is the food's variation; whether it has a type of its own is not known.
    static u32 RandomFoodKind(FoodTableKind kind);
};

}}}  // namespace scn::step::item

#endif
