#ifndef SCN_STEP_ITEM_GETINFO_H
#define SCN_STEP_ITEM_GETINFO_H

#include "types.h"

namespace scn {
namespace step {
namespace item {

class GetInfo {
public:
    GetInfo();

    u32 subKind() const;

private:
    u32 _0;
    u32 mSubKind;
};

}}}  // namespace scn::step::item

#endif
