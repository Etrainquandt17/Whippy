#ifndef SCN_STEP_CHARA_CLIFFCHECKER_H
#define SCN_STEP_CHARA_CLIFFCHECKER_H

#include "types.h"

namespace scn {
namespace step {
namespace chara {

// TODO: members.
class CliffChecker {
public:
    void update();
    bool isCliff() const;
    void setValid(bool isValid);
    void changeFrontDist(f32 dist);
};

}}}  // namespace scn::step::chara

#endif
