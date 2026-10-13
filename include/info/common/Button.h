#ifndef INFO_COMMON_BUTTON_H
#define INFO_COMMON_BUTTON_H

#include "types.h"

namespace info {
namespace common {

// TODO: members.
class Button {
public:
    ~Button();

    void updateFrame();

private:
    u32 _0[0x67];
};

}}  // namespace info::common

#endif
