#ifndef SCN_STEP_HERO_OBJSTOP_H
#define SCN_STEP_HERO_OBJSTOP_H

namespace scn {
namespace step {
namespace hero {

// TODO: members.
class ObjStop {
public:
    void setSpecial();
    void unsetSpecial();
    bool isSpecial() const;
};

}}}  // namespace scn::step::hero

#endif
