#include "scn/step/hero/MintStateChecker.h"

#include "scn/step/hero/Hero.h"
#include "scn/step/hero/MintHero.h"
#include "scn/step/hero/StateChecker.h"

namespace scn {
namespace step {
namespace hero {

namespace {

StateChecker& t_obj() {
    return MintHero::Obj().stateChecker();
}

}

namespace MintStateChecker {

bool IsRun() {
    return t_obj().isRun();
}

bool IsFloat() {
    return t_obj().isFloat();
}

bool IsCarryBombDanger() {
    return t_obj().isCarryBombDanger();
}

bool IsHover() {
    return t_obj().isHover();
}

}
}
}
}
