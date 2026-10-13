#ifndef SCN_STEP_GIMMICK_BLOCK_BLOCKINFO_H
#define SCN_STEP_GIMMICK_BLOCK_BLOCKINFO_H

#include "scn/step/GridPos.h"

namespace scn {
namespace step {
namespace gimmick {
namespace block {

class BlockInfo {
public:
    GridPos gridPos() const;
};

}}}}  // namespace scn::step::gimmick::block

#endif
