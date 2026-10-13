#ifndef SCN_STEP_HERO_GATHERITEM_H
#define SCN_STEP_HERO_GATHERITEM_H

#include "hel/geo/Rect.h"

namespace scn {
namespace step {
namespace hero {

class GatherItem {
public:
    void add(const hel::geo::Rect& rect);
    void clear();
};

}}}  // namespace scn::step::hero

#endif
