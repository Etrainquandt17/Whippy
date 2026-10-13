#ifndef SCN_STEP_HERO_ABILITYCUSTOMBASE_H
#define SCN_STEP_HERO_ABILITYCUSTOMBASE_H

#include "hel/common/RuntimeTypeInfo.h"

namespace scn {
namespace step {
namespace hero {

class Hero;

class AbilityCustomBase {
public:
    AbilityCustomBase(Hero& hero);
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~AbilityCustomBase();

protected:
    Hero& mHero;
};

}
}
}

#endif
