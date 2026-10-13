#ifndef SCN_STEP_CORE_PRELOADREQ_H
#define SCN_STEP_CORE_PRELOADREQ_H

#include "scn/step/map/Kind.h"
#include "types.h"

namespace scn {
namespace step {

class Component;

namespace gimmick {
class StepMoveInfo;
namespace lvmapdoor {
class Result;
}
namespace shipdoor {
class Result;
}}  // namespace gimmick::shipdoor

namespace core {

class PreLoadReq {
public:
    static void Request(Component& component, const gimmick::StepMoveInfo& info);
    static void Request(Component& component, const gimmick::shipdoor::Result& result);

    PreLoadReq(Component& component);

    void request(const gimmick::StepMoveInfo& info);
    void request(const gimmick::lvmapdoor::Result& result);
    void request(const gimmick::shipdoor::Result& result);
    void request(map::Kind kind);
    bool isRequested() const;
    bool checkRequest();

private:
    Component& mComponent;
    bool mIsRequested;
};

}}}  // namespace scn::step::core

#endif
