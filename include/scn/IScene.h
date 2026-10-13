#ifndef SCN_ISCENE_H
#define SCN_ISCENE_H

namespace hel {
namespace common {
class RuntimeTypeInfo;
}}  // namespace hel::common

namespace scn {

class DrawReqInfo;

class IScene {
public:
    virtual const hel::common::RuntimeTypeInfo& GetRuntimeTypeInfo() const;
    virtual ~IScene();
    virtual void updateMain() = 0;
    virtual void updateUseGPU() = 0;
    virtual void updateDebug() = 0;
    virtual void draw(const DrawReqInfo& info) = 0;
    virtual bool isSceneEnd() const = 0;
};

}  // namespace scn

#endif
