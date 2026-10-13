#ifndef SCN_STEP_HERO_CAPTUREHERORECEIVER_H
#define SCN_STEP_HERO_CAPTUREHERORECEIVER_H

namespace scn {
namespace step {
namespace hero {

class CaptureHeroReceiver {
public:
    bool isCapture() const;
    void setCanCapture(bool canCapture);
};

}
}
}

#endif
