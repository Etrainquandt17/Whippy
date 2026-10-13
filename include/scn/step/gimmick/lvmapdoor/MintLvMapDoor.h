#ifndef SCN_STEP_GIMMICK_LVMAPDOOR_MINTLVMAPDOOR_H
#define SCN_STEP_GIMMICK_LVMAPDOOR_MINTLVMAPDOOR_H

namespace scn {
namespace step {
namespace gimmick {
namespace lvmapdoor {

class LvMapDoor;

class MintLvMapDoor {
public:
    static void Register(LvMapDoor& door);
    static void Unregister(LvMapDoor& door);
    static LvMapDoor& Obj();
};

}
}
}
}

#endif
