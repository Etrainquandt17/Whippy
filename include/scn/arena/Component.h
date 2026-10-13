#ifndef SCN_ARENA_COMPONENT_H
#define SCN_ARENA_COMPONENT_H

#include "scn/arena/ArenaState.h"
#include "scn/arena/MenuState.h"
#include "types.h"

namespace scn {
namespace arena {

class ContextArena;

namespace select {
class ChoseData;
}

class Component {
public:
    ArenaState getState();
    ContextArena& context();
    select::ChoseData& chose();
    void setMenuState(MenuState state);
    bool getNoTitleAnimFlag();
};

}}  // namespace scn::arena

#endif
