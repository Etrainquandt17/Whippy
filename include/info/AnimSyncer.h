#ifndef INFO_ANIMSYNCER_H
#define INFO_ANIMSYNCER_H

#include "hel/common/MutableArray.h"
#include "hel/common/NonCopyable.h"
#include "types.h"

namespace lyt {
class Layout;
}

namespace info {

class AnimSyncer : private hel::common::NonCopyable {
public:
    void add(lyt::Layout& layout);
    void remove(lyt::Layout& layout);
    void update();

private:
    hel::common::MutableArray<lyt::Layout*, 32> mLayouts;
};

}  // namespace info

#endif
