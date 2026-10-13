#include "scn/step/hero/MintClearDanceSync.h"

#include "scn/step/Component.h"
#include "scn/step/hero/ClearDanceSync.h"
#include "scn/step/hero/Hero.h"
#include "scn/step/hero/Manager.h"
#include "scn/step/hero/MintHero.h"

namespace scn {
namespace step {
namespace hero {

namespace {

ClearDanceSync& t_obj() {
    return MintHero::Obj().comp().heroManager().clearDanceSync();
}

}

namespace MintClearDanceSync {

bool IsSync() {
    return t_obj().isSync();
}

int FirstAnim() {
    return t_obj().firstAnim();
}

int SecondAnim() {
    return t_obj().secondAnim();
}

int ThirdAnim() {
    return t_obj().thirdAnim();
}

int FinishAnim() {
    return t_obj().finishAnim();
}

}
}
}
}
