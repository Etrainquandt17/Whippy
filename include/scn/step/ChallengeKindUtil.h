#ifndef SCN_STEP_CHALLENGEKINDUTIL_H
#define SCN_STEP_CHALLENGEKINDUTIL_H

#include "hel/common/FixedString.h"
#include "lyt/LayoutContext.h"
#include "scn/step/ChallengeKind.h"
#include "scn/step/SphereUnlockKind.h"
#include "scn/step/hero/AbilityKind.h"
#include "scn/step/map/Kind.h"
#include "types.h"

namespace scn {
namespace step {

class ChallengeKindUtil {
public:
    static hero::AbilityKind AbilityKind(ChallengeKind kind);
    static ChallengeKind AbilityKindToChallengeKind(hero::AbilityKind kind);
    static hel::common::FixedString<64> TutorialDNPath(ChallengeKind kind);
    static const char* ChallengeName(ChallengeKind kind);
    static const char* AbilityName(ChallengeKind kind);
    static map::Kind MapKind(ChallengeKind kind);
    static u32 PortalNo(ChallengeKind kind);
    static ChallengeKind ToChallengeKind(map::Kind kind);
    static bool IsChallengePortal(u32 portalNo);
    static ChallengeKind PortalToChallengeKind(u32 portalNo);
    static SphereUnlockKind ToSphereUnlockKind(ChallengeKind kind);
    static ChallengeKind SphereUnlockKindToChallengeKind(SphereUnlockKind kind);
    static lyt::LayoutContext TitleLayoutContext(ChallengeKind kind, mem::IAllocator& allocator);
};

}}  // namespace scn::step

#endif
