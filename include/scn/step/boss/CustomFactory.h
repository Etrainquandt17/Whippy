#ifndef SCN_STEP_BOSS_CUSTOMFACTORY_H
#define SCN_STEP_BOSS_CUSTOMFACTORY_H

#include "mem/ExplicitScopedPtr.h"
#include "scn/step/boss/ICustom.h"

namespace scn {
namespace step {
namespace boss {

class Boss;

class CustomFactory {
public:
    static void Create(Boss& boss, mem::ExplicitScopedPtr<ICustom>& custom);
};

}}}  // namespace scn::step::boss

#endif
