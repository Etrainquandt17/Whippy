#ifndef SCN_STEP_EFFECT_REQUESTOR_H
#define SCN_STEP_EFFECT_REQUESTOR_H

#include "scn/step/core/DrawLayerKind.h"
#include "scn/step/effect/DrawPriority.h"
#include "types.h"

namespace effect {
class Requestor;
namespace detail {
class RequestArg;
}}  // namespace effect::detail

namespace scn {
namespace step {
namespace effect {

class Manager;

class Requestor {
public:
    Requestor(Manager& manager, DrawPriority priority);
    // TODO: implicit in the original (every unit that needs it emits a copy): the class holds an
    // ::effect::Requestor, whose size is not known yet.
    ~Requestor();

    void request(const ::effect::detail::RequestArg& arg);
    void changeLayer(core::DrawLayerKind kind);
    void release();
    void releaseAndVanish();
    void pauseInc();
    void pauseDec();
    ::effect::Requestor& native();

private:
    u32 _0[0x20 / 4];
};

}}}  // namespace scn::step::effect

#endif
