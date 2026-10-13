#ifndef SCN_STEP_ITEM_INDIVIUTIL_H
#define SCN_STEP_ITEM_INDIVIUTIL_H

#include "scn/step/map/BinItemKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {

}
class Component;
namespace chara {

class ModelDesc;

}
namespace item {

// TODO: the other functions.
class IndiviUtil {
public:
    static const chara::ModelDesc& ModelDesc(Component& comp, map::BinItemKind kind, u32 variation);
};

}}}  // namespace scn::step::item

#endif
