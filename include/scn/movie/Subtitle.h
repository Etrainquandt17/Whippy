#ifndef SCN_MOVIE_SUBTITLE_H
#define SCN_MOVIE_SUBTITLE_H

#include "lyt/Layout.h"
#include "mov/MovieKind.h"
#include "types.h"

namespace mem {
class IAllocator;
}

namespace scn {
namespace movie {

class Subtitle {
public:
    Subtitle(mem::IAllocator& allocator, mov::MovieKind kind);

private:
    lyt::Layout mLayout;
    mov::MovieKind mKind;
};

}}  // namespace scn::movie

#endif
