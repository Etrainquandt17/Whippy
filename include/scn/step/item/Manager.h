#ifndef SCN_STEP_ITEM_MANAGER_H
#define SCN_STEP_ITEM_MANAGER_H

#include "scn/step/item/Desc.h"
#include "types.h"
#include "util/ObjRefHandle.h"

namespace hel {
namespace geo {

class Rect;

}}  // namespace hel::geo

namespace scn {
namespace step {
namespace item {

class Item;

// TODO: members and the other functions.
class Manager {
public:
    util::ObjRefHandle<Item> request(const Desc& desc);
    util::ObjRefHandle<Item> searchItem(u32 itemUID);
    util::ObjRefHandle<Item> searchItemByKind(map::BinItemKind kind, const hel::geo::Rect& rect);
    f32 getRotGlobal(f32 x) const;
};

}}}  // namespace scn::step::item

#endif
