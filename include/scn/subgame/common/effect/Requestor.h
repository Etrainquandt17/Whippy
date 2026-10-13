#ifndef SCN_SUBGAME_COMMON_EFFECT_REQUESTOR_H
#define SCN_SUBGAME_COMMON_EFFECT_REQUESTOR_H

#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace effect {

class Manager;

class Requestor {
public:
    Requestor(Manager& manager);
    ~Requestor();

    void changeGroup(u32 group);
    void release();
    void releaseAndVanish();
};

}}}}  // namespace scn::subgame::common::effect

#endif
