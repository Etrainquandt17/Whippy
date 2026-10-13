#ifndef SCN_WMAP_UTIL_H
#define SCN_WMAP_UTIL_H

#include "scn/step/LevelKind.h"
#include "scn/wmap/ItemKind.h"
#include "scn/wmap/MapKind.h"
#include "types.h"

namespace scn {
namespace wmap {

class Util {
public:
    static step::LevelKind GetLevelKindFromItemKind(ItemKind kind);
    static MapKind GetMapKindFromItemKind(ItemKind kind);
    static ItemKind GetItemKindFromLevelKind(step::LevelKind kind);
    static MapKind GetMapKind(ItemKind kind);
    // TODO: the result is a route kind, 27 for none.
    static int GetRoute(ItemKind from, ItemKind to);
};

}}  // namespace scn::wmap

#endif
