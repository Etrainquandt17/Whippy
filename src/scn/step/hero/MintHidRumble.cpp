#include "scn/step/hero/MintHidRumble.h"

#include "hid/RumbleRequestor.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintHero.h"

namespace scn {
namespace step {
namespace hero {

namespace {

hid::RumbleRequestor& t_obj() {
    return MintHero::Obj().hidRumble();
}

}

namespace MintHidRumble {

void Start(int kind) {
    t_obj().start(kind);
}

void Stop() {
    t_obj().stop();
}

}
}
}
}
