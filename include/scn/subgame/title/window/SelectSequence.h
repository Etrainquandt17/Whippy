#ifndef SCN_SUBGAME_TITLE_WINDOW_SELECTSEQUENCE_H
#define SCN_SUBGAME_TITLE_WINDOW_SELECTSEQUENCE_H

#include "lyt/Layout.h"
#include "scn/subgame/Context.h"
#include "scn/subgame/common/boxmenu/SelectUnit.h"
#include "scn/subgame/common/pause/CursorContainedButtons.h"
#include "types.h"

namespace scn {
namespace subgame {
namespace title {
namespace window {

class SelectSequence {
public:
    class Context {
    public:
        static Context Create(scn::subgame::Context::Kind kind);

        u32 _0;
        u32 mCount;
        int _8[3];
        const char* _14[6];
        const char* _2C[3];
        u32 _38[8];
        const char* _58;
        u32 _5C[3];
        u32 _68[3];
        u32 _74[3];
    };

    SelectSequence(Context context, lyt::Layout& layout, common::pause::CursorContainedButtons& buttons);
    ~SelectSequence();

    void start();
    void reset();
    void hide();
    void enter();
    void back();
    void up();
    void down();
    void select(const common::boxmenu::SelectableBox* box);
    void updateMain();
    void updateDebug();
    bool isEnd() const;
    bool isFixed() const;
    int nextSeq() const;

private:
    u8 _0[0xC];
    int _C[3];
    u8 _18[0x850];
    common::boxmenu::SelectUnit mSelectUnit;
    u8 _8AC[0x2A0];
};

}}}}  // namespace scn::subgame::title::window

#endif
