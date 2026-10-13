#ifndef SCN_WMAP_EFFECT_MANAGER_H
#define SCN_WMAP_EFFECT_MANAGER_H

#include "scn/wmap/DrawLayerKind.h"

namespace effect {
class Group;
class Manager;
}

namespace scn {
namespace wmap {
namespace effect {

// TODO: only what scn::wmap::MapModelRouteEffect calls.
class Manager {
public:
    ::effect::Manager& native();
    ::effect::Group& group(DrawLayerKind kind);
};

}}}  // namespace scn::wmap::effect

#endif
