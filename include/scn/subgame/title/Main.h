#ifndef SCN_SUBGAME_TITLE_MAIN_H
#define SCN_SUBGAME_TITLE_MAIN_H

#include "scn/subgame/Context.h"
#include "scn/subgame/Result.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace title {

class Main {
public:
    Main(const Context& context, const Result::Seq& seq);
    ~Main();

    bool isBack() const;
    Result::Seq nextSeq() const;
    void updateMain();
    void updateUseGPU();
    void updateDebug();
    void draw();
    bool isSceneEnd() const;

private:
    u32 _0[0x18];
};

}}}  // namespace scn::subgame::title

#endif
