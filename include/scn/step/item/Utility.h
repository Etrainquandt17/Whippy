#ifndef SCN_STEP_ITEM_UTILITY_H
#define SCN_STEP_ITEM_UTILITY_H

namespace g3d {

class ModelAccessor;

}

namespace scn {
namespace step {

class Component;

namespace chara {

class Effect;

}

namespace item {

class Item;

class Utility {
public:
    static void RequestEffectEnergySphere(Component& component, const g3d::ModelAccessor& model, chara::Effect& effect);
    static void RequestEffectShipParts(Component& component, const g3d::ModelAccessor& model, chara::Effect& effect);
    static bool IsWithLowper(Item& item);
    static bool IsInLand(Item& item);
};

}}}  // namespace scn::step::item

#endif
