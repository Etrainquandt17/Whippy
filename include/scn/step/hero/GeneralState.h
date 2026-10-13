#ifndef SCN_STEP_HERO_GENERALSTATE_H
#define SCN_STEP_HERO_GENERALSTATE_H

namespace scn {
namespace step {
namespace hero {

class GeneralState {
public:
    // TODO: names.
    enum SuperFinishType {
        SUPER_FINISH_TYPE_0,
        SUPER_FINISH_TYPE_1,
        SUPER_FINISH_TYPE_2,
    };

    GeneralState();

    void setSuperFinishType(SuperFinishType type);
    void unsetSuperFinishType();
};

}}}  // namespace scn::step::hero

#endif
