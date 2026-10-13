#ifndef SCN_STEP_CORE_SCENECHANGER_H
#define SCN_STEP_CORE_SCENECHANGER_H

#include "scn/step/map/Kind.h"
#include "types.h"

namespace scn {
namespace step {
namespace core {

// TODO: members and the other functions.
class SceneChanger {
public:
    void changeBossClearArena();
    void changeBossClear();
    void changeShipRepairDemoMovie();
    void changeDoor(int, u32);
    void changeDoor(map::Kind kind, u32);
    void changeScrewSuper(int, u32);
};

}}}  // namespace scn::step::core

#endif
