#ifndef SCN_STEP_CORE_PAUSETRIGGER_H
#define SCN_STEP_CORE_PAUSETRIGGER_H

namespace scn {
namespace step {
namespace core {

// TODO: members and the other functions.
class PauseTrigger {
public:
    // TODO: name the kinds.
    enum EnableKind {
        ENABLE_KIND_0,
        ENABLE_KIND_8 = 8,
    };

    void setIsEnable(EnableKind kind, bool isEnable);
};

}}}  // namespace scn::step::core

#endif
