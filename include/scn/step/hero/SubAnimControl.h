#ifndef SCN_STEP_HERO_SUBANIMCONTROL_H
#define SCN_STEP_HERO_SUBANIMCONTROL_H

namespace scn {
namespace step {
namespace hero {

class SubAnimControl {
public:
    void setLiftUpTwoHand(bool lift);
    void setLiftUpRHand(bool lift);
    bool isLiftUpRHand() const;
    void clearAll();
};

}}}  // namespace scn::step::hero

#endif
