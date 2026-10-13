#ifndef EFFECT_DETAIL_REQUESTARG_H
#define EFFECT_DETAIL_REQUESTARG_H

#include "effect/detail/RequestArgOption.h"
#include "hel/common/FixedString.h"
#include "types.h"

namespace effect {
namespace detail {

class RequestArg {
public:
    RequestArg();
    RequestArg(u32 id, const RequestArgOption& option);
    ~RequestArg();

private:
    u32 mKind;
    u32 mId;
    hel::common::FixedString<36> mName;
    RequestArgOption mOption;
};

}}  // namespace effect::detail

#endif
