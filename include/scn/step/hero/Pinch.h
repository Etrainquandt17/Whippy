#ifndef SCN_STEP_HERO_PINCH_H
#define SCN_STEP_HERO_PINCH_H

namespace scn {
namespace step {
namespace hero {

class Pinch {
public:
    bool isPinch() const;
    void setForbidNotifyInfo(bool flag);
};

}}}  // namespace scn::step::hero

#endif
