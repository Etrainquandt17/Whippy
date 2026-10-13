#include "scn/step/enemy/MintEnemy.h"

#include "hel/common/PointerWrapper.h"

namespace scn {
namespace step {
namespace enemy {

namespace {

hel::common::PointerWrapper<Enemy> t_obj;

}

void MintEnemy::Register(Enemy& enemy) {
    t_obj.set(enemy);
}

void MintEnemy::Unregister(Enemy&) {
    t_obj.reset();
}

Enemy* MintEnemy::Obj() {
    return &t_obj.ref();
}

}
}
}
