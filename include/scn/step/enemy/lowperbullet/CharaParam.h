#ifndef SCN_STEP_ENEMY_LOWPERBULLET_CHARAPARAM_H
#define SCN_STEP_ENEMY_LOWPERBULLET_CHARAPARAM_H

#include "scn/step/enemy/CharaParam.h"

namespace scn {
namespace step {
namespace enemy {
namespace lowperbullet {
namespace CharaParam {

enemy::CharaParam CreateBase();
enemy::CharaParam CreateLv1();
enemy::CharaParam CreateLv2();
enemy::CharaParam CreateLv3();
enemy::CharaParam CreateLv4();

}}}}}  // namespace scn::step::enemy::lowperbullet::CharaParam

#endif
