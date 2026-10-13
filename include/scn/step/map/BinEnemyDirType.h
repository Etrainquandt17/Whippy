#ifndef SCN_STEP_MAP_BINENEMYDIRTYPE_H
#define SCN_STEP_MAP_BINENEMYDIRTYPE_H

namespace scn {
namespace step {
namespace map {

// TODO: 0 and 1. The names of the others say where enemy::aquarock::StateMove moves for each.
enum BinEnemyDirType {
    BinEnemyDirType_0,
    BinEnemyDirType_1,
    BinEnemyDirType_Left,
    BinEnemyDirType_Right,
    BinEnemyDirType_Up,
    BinEnemyDirType_Down,
    BinEnemyDirType_UpLeft,
    BinEnemyDirType_UpRight,
    BinEnemyDirType_DownLeft,
    BinEnemyDirType_DownRight,
};

}}}  // namespace scn::step::map

#endif
