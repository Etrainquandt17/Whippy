#ifndef MCOLL_DETAIL_MOVEGRIDGROUPID_H
#define MCOLL_DETAIL_MOVEGRIDGROUPID_H

#include "types.h"

namespace mcoll {
namespace detail {

class MoveGridGroupId {
public:
    // The copy constructor and the assignment are the implicit ones: the class is returned in a register, and a unit
    // that copies it twice emits them.
    // TODO: a guess; hero::MapCollResult::groupFloor() needs a way from its result to this class.
    MoveGridGroupId(u32 no)
        : _0(no) {}

    static MoveGridGroupId CreateWithNo(u32 no);

    bool isValid() const;
    u32 no() const;
    u32 index() const;

private:
    u32 _0;
};

}}  // namespace mcoll::detail

#endif
