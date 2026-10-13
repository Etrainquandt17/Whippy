#ifndef HEL_MINT_ADDONMATHDIRECTION3_H
#define HEL_MINT_ADDONMATHDIRECTION3_H

namespace mintvm {

class VMCore;

}

namespace hel {
namespace math {

class Direction3;
class Vector3;

}
}

namespace hel {
namespace mint {
namespace AddOnMathDirection3 {

void RegisterAll(mintvm::VMCore& core);
hel::math::Direction3 Get();
void Set(const hel::math::Direction3& value);
void LoadLeft();
void LoadUp();
void LoadFront();
void StoreLeft();
void StoreUp();
void StoreFront();
void SetBasis();
void SetFrontToRight();
void SetFrontToLeft();
void RestructFrontUp();
void RestructFrontLeft();
void RestructUpFront();
void RestructUpLeft();
void RestructLeftFront();
void RestructLeftUp();
hel::math::Direction3 Basis();
hel::math::Direction3 Create(const hel::math::Vector3& front, const hel::math::Vector3& up, const hel::math::Vector3& left);

}
}
}

#endif
