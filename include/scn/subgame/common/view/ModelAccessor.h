#ifndef SCN_SUBGAME_COMMON_VIEW_MODELACCESSOR_H
#define SCN_SUBGAME_COMMON_VIEW_MODELACCESSOR_H

#include "g3d/ModelAnimAccessor.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace common {
namespace view {

class ModelAccessor {
public:
    ModelAccessor();
    ~ModelAccessor();

    g3d::ModelAnimAccessor setAnim(const char* name);
    g3d::ModelAnimAccessor setAnim(u32 index, const char* name);
    void clearAnim();
    void clearAnim(u32 index);
    bool isVisible() const;
    void setVisibility(bool visible);

private:
    u8 _0[0x18];
};

}}}}  // namespace scn::subgame::common::view

#endif
