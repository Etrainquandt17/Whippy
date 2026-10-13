#ifndef SCN_STEP_ENEMY_CUSTOMFACTORY_H
#define SCN_STEP_ENEMY_CUSTOMFACTORY_H

#include "mem/ExplicitScopedPtr.h"
#include "scn/step/enemy/ICustom.h"

namespace scn {
namespace step {
namespace enemy {

class Enemy;

class CustomFactory {
public:
    static void Create(Enemy& enemy, mem::ExplicitScopedPtr<ICustom>& custom);
};

}
}
}

#endif
