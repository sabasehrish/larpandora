#include "larpandora/LArPandoraInterface/Detectors/LArPandoraDetectorType.h"
#include "Objects/Cluster.h"

#include "larcore/Geometry/Geometry.h"

namespace lar_pandora{

    class DUNEFarDetVDThreeView : public LArPandoraDetectorType {
    public:
        DUNEFarDetVDThreeView();
        geo::View_t TargetViewU(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const override;
        geo::View_t TargetViewV(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const override;
        geo::View_t TargetViewW(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const override;
        float WirePitchU() const override;
        float WirePitchV() const override;
        float WirePitchW() const override;
        float WireAngleU(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const override;
        float WireAngleV(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const override;
        float WireAngleW(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const override;
        bool ShouldSwitchUV(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const override {return false; };
        bool CheckDetectorGapSize(const geo::Vector_t &gaps, const geo::Vector_t &deltas, const float maxDisplacement) const override;
    private:
        art::ServiceHandle<geo::Geometry> m_LArSoftGeometry;
        float WireAngleImpl(const geo::View_t view, const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const;
    };

    inline geo::View_t DUNEFarDetVDThreeView::TargetViewU(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const
    {
        return m_LArSoftGeometry->View(geo::PlaneID(cstat, tpc, 0));
    }

    inline geo::View_t DUNEFarDetVDThreeView::TargetViewV(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const
    {
        return m_LArSoftGeometry->View(geo::PlaneID(cstat, tpc, 1));
    }

    inline geo::View_t DUNEFarDetVDThreeView::TargetViewW(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const
    {
        return m_LArSoftGeometry->View(geo::PlaneID(cstat, tpc, 2));
    }

    inline float DUNEFarDetVDThreeView::WirePitchU() const
    {
        return m_LArSoftGeometry->WirePitch(this->TargetViewU(0,0));
    }

    inline float DUNEFarDetVDThreeView::WirePitchV() const
    {
        return m_LArSoftGeometry->WirePitch(this->TargetViewV(0,0));
    }

    inline float DUNEFarDetVDThreeView::WirePitchW() const
    {
        return m_LArSoftGeometry->WirePitch(this->TargetViewW(0,0));
    }

    inline float DUNEFarDetVDThreeView::WireAngleU(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const
    {
        return this->WireAngleImpl(this->TargetViewU(tpc, cstat), tpc, cstat);
    }

    inline float DUNEFarDetVDThreeView::WireAngleV(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const
    {
        //ATTN abs needed as this view should be kY
        return std::abs(this->WireAngleImpl(this->TargetViewV(tpc, cstat), tpc, cstat));
    }

    inline float DUNEFarDetVDThreeView::WireAngleW(const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const
    {
        return this->WireAngleImpl(this->TargetViewW(tpc, cstat), tpc, cstat);
    }

    inline float DUNEFarDetVDThreeView::WireAngleImpl(const geo::View_t view, const geo::TPCID::TPCID_t tpc, const geo::CryostatID::CryostatID_t cstat) const
    {
        return (0.5f * M_PI - m_LArSoftGeometry->WireAngleToVertical(view, tpc, cstat));
    }

    inline bool DUNEFarDetVDThreeView::CheckDetectorGapSize(const geo::Vector_t &gaps, const geo::Vector_t &deltas, const float maxDisplacement) const
    {
        if (gaps.X() < 0.f || gaps.X() > maxDisplacement || deltas.Y() > maxDisplacement || deltas.Z() > maxDisplacement)
            return false;
        return true;
    }
}
