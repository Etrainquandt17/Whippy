#ifndef SCN_STEP_ITEM_GETINFO_H
#define SCN_STEP_ITEM_GETINFO_H

#include "scn/step/map/BinItemKind.h"
#include "types.h"

namespace scn {
namespace step {
namespace item {

class GetInfo {
public:
    GetInfo();
    GetInfo(map::BinItemKind kind, u32 subKind);

    u32 subKind() const;

private:
    u32 _0;
    u32 mSubKind;
};

}}}  // namespace scn::step::item

#endif
