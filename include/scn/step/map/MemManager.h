#ifndef SCN_STEP_MAP_MEMMANAGER_H
#define SCN_STEP_MAP_MEMMANAGER_H

namespace mem {
class IAllocator;
}

namespace scn {
namespace step {
namespace map {

class MemManager {
public:
    mem::IAllocator& allocator();
};

}}}  // namespace scn::step::map

#endif
