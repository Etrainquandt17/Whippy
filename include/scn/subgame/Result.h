#ifndef SCN_SUBGAME_RESULT_H
#define SCN_SUBGAME_RESULT_H

#include "scn/subgame/Context.h"
#include "types.h"

namespace scn {
namespace subgame {

class Result {
public:
    // TODO: name the values.
    enum Seq {
        SEQ_0,
        SEQ_1,
        SEQ_2,
        SEQ_3,
        SEQ_4,
        SEQ_5,
        SEQ_6,
        SEQ_7,
        SEQ_8,
    };

    static Result Create(const Context& context);

    Context mContext;
    Seq mSeq;
};

}
}

#endif
