#ifndef SCN_STEP_HERO_PARAM_H
#define SCN_STEP_HERO_PARAM_H

namespace scn {
namespace step {
namespace hero {

// TODO: members.
struct IndiviParam;
struct CommonParam;
struct NinjaParam;
struct RideParam;
struct SleepParam;
struct CrashParam;
struct MikeParam;
struct TornadoParam;
struct LeafParam;
struct CutterParam;
struct InterferenceParam;
struct SuperParam;
struct SuperSwordParam;
struct SuperFireParam;
struct SuperBeamParam;
struct SuperHammerParam;
struct SuperIceParam;
struct NeedleParam;
struct FireParam;
struct HighjumpParam;
struct BombParam;
struct SwordParam;
struct BeamParam;
struct SparkParam;
struct WingParam;
struct StoneParam;
struct HammerParam;
struct ParasolParam;
struct WhipParam;
struct CapturedWhispyParam;
struct CapturedGrandLowperParam;
struct CapturedFattyBufferParam;
struct CapturedDoubterParam;
struct CapturedWaterGalborosParam;
struct CapturedHRD3Param;
struct CapturedGalactaKnightParam;
struct MetaParam;
struct FighterParam;
struct SpearParam;
struct DeeParam;
struct IceParam;
struct WaterParam;
struct LandiaParam;
struct DededeParam;

// TODO: the enumerators; ice::Ice passes 3.
enum ParamReplKind {
    PARAM_REPL_KIND_ICE = 3
};

// TODO: members and the other functions.
class Param {
public:
    const IndiviParam& indiviKirby() const;
    const IndiviParam& indiviMeta() const;
    const IndiviParam& indiviDedede() const;
    const IndiviParam& indiviDee() const;
    const CommonParam& common() const;
    const NinjaParam& ninja() const;
    const RideParam& ride() const;
    const SleepParam& sleep() const;
    const CrashParam& crash() const;
    const MikeParam& mike() const;
    const TornadoParam& tornado() const;
    const LeafParam& leaf() const;
    const CutterParam& cutter() const;
    const InterferenceParam& interference() const;
    const SuperParam& super() const;
    const SuperSwordParam& superSword() const;
    const SuperFireParam& superFire() const;
    const SuperBeamParam& superBeam() const;
    const SuperHammerParam& superHammer() const;
    const SuperIceParam& superIce() const;
    const NeedleParam& needle() const;
    const FireParam& fire() const;
    const HighjumpParam& highjump() const;
    const BombParam& bomb() const;
    const SwordParam& sword() const;
    const BeamParam& beam() const;
    const SparkParam& spark() const;
    const WingParam& wing() const;
    const StoneParam& stone() const;
    const HammerParam& hammer() const;
    const ParasolParam& parasol() const;
    const WhipParam& whip() const;
    const CapturedWhispyParam& capturedWhispy() const;
    const CapturedGrandLowperParam& capturedGrandLowper() const;
    const CapturedFattyBufferParam& capturedFattyBuffer() const;
    const CapturedDoubterParam& capturedDoubter() const;
    const CapturedWaterGalborosParam& capturedWaterGalboros() const;
    const CapturedHRD3Param& capturedHRD3() const;
    const CapturedGalactaKnightParam& capturedGalactaKnight() const;
    const MetaParam& meta() const;
    const FighterParam& fighter() const;
    const SpearParam& spear() const;
    const DeeParam& dee() const;
    const IceParam& ice() const;
    const WaterParam& water() const;
    const LandiaParam& landia() const;
    const DededeParam& dedede() const;
    void replaceCommonParam(ParamReplKind kind);
    void restoreCommonParam(ParamReplKind kind);
};

}
}
}

#endif
