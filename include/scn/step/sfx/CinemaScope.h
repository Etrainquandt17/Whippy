#ifndef SCN_STEP_SFX_CINEMASCOPE_H
#define SCN_STEP_SFX_CINEMASCOPE_H

#include "scn/step/sfx/CinemaScopeKind.h"

namespace scn {
namespace step {
namespace sfx {

class CinemaScope {
public:
    void start(CinemaScopeKind kind);
    void startNoAnim(CinemaScopeKind kind);
    void end();
};

}}}  // namespace scn::step::sfx

#endif
