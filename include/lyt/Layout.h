#ifndef LYT_LAYOUT_H
#define LYT_LAYOUT_H

#include "lyt/PaneAccessor.h"
#include "types.h"

namespace lyt {

class LayoutContext;

class Layout {
public:
    Layout(const LayoutContext& context);
    ~Layout();

    PaneAccessor rootPane();
    PaneAccessor pane(const char* name);
    PaneAccessor paneByName(const char* name);
    bool hasPane(const char* name);
    bool wasSetAnim() const;
    void clearAnim();
    void setAnimByName(const char* name);
    void play(const char* name);
    void play(const char* name, const char* other);
    f32 frame() const;
    f32 totalFrame() const;
    void setFrame(f32 frame);
    void setFrameNoReflectToAnim(f32 frame);
    void setFrameToHead();
    void setFrameToTail();
    void updateFrame();
    void reflectFrameToAnim();
    f32 frameRate() const;
    void setFrameRate(f32 rate);
    void start(bool doLoop);
    void stop();
    bool isAnimating() const;
    bool isAnimEnd() const;
    void changeDoLoop(bool doLoop);
    bool wasSetParent() const;
    void setParent(const PaneAccessor& parent);
    void unsetParent();
    PaneAccessor parent() const;
    void updateMatrix();
    void draw() const;

private:
    u32 _0[0x64];
};

}

#endif
