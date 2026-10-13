#ifndef SCN_STEP_HERO_SPARK_SPARK_H
#define SCN_STEP_HERO_SPARK_SPARK_H

#include "scn/step/hero/AbilityBase.h"
#include "types.h"

namespace scn {
namespace step {
namespace hero {
namespace spark {

class Spark : public AbilityBase {
public:
    Spark(Component& component, Hero& hero);
    virtual ~Spark();

private:
    u32 _C[(0x290 - 0xC) / 4];
};

}}}}  // namespace scn::step::hero::spark

#endif
