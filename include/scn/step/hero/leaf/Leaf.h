#ifndef SCN_STEP_HERO_LEAF_LEAF_H
#define SCN_STEP_HERO_LEAF_LEAF_H

#include "dynamics/Desc.h"
#include "scn/step/hero/AbilityBase.h"

namespace scn {
namespace step {
namespace hero {
namespace leaf {

class Leaf : public AbilityBase {
public:
    Leaf(Component& component, Hero& hero);
    virtual ~Leaf();
    virtual void setup();
    virtual bool tryToChangeState();
    virtual bool tryToChangeStateOnInterval();

private:
    bool mIsSetup;
    dynamics::Desc _10;
    dynamics::Desc _F4;
};

}}}}  // namespace scn::step::hero::leaf

#endif
