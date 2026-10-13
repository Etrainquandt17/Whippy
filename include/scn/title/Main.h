#ifndef SCN_TITLE_MAIN_H
#define SCN_TITLE_MAIN_H

#include "types.h"

namespace scn {
namespace title {

// TODO: members; the size is what scn::title::SceneTitle allocates.
class Main {
public:
    Main(bool);
    ~Main();

    void start();
    void updateMain();
    void updateUseGPU();
    void updateDebug();
    void draw();
    bool isSceneEnd() const;
    int result() const;

private:
    u32 _0[5];
};

}}  // namespace scn::title

#endif
