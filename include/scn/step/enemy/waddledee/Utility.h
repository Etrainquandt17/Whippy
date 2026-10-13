#ifndef SCN_STEP_ENEMY_WADDLEDEE_UTILITY_H
#define SCN_STEP_ENEMY_WADDLEDEE_UTILITY_H

#include "scn/step/map/BinEnemyVariation.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

namespace waddledee {
namespace Utility {

void Generate3Waddledee(Enemy& enemy, bool flag, map::BinEnemyVariation variation);
bool CommonBehaviorOnHitPointIsZero(Enemy& enemy, bool flag, map::BinEnemyVariation variation);

}}}}}  // namespace scn::step::enemy::waddledee::Utility

#endif
