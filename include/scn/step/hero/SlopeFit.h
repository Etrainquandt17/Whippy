#ifndef SCN_STEP_HERO_SLOPEFIT_H
#define SCN_STEP_HERO_SLOPEFIT_H

#include "types.h"

namespace scn {
namespace step {
namespace hero {

class SlopeFit {
public:
    void setValid(bool valid);
    void setIntpRate(f32 rate);
    void setAffectRate(f32 rate);
};

}}}  // namespace scn::step::hero

#endif
