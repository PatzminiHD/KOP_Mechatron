#include "uss.h"
#include "../vars/constants.h"

class sensors
{
    private:
    uss Front      = uss(constants::pins::uss::Front_Sens,      constants::pins::uss::Trigger);
    uss FrontLeft  = uss(constants::pins::uss::FrontLeft_Sens,  constants::pins::uss::Trigger);
    uss BackLeft   = uss(constants::pins::uss::BackLeft_Sens,   constants::pins::uss::Trigger);
    uss Back       = uss(constants::pins::uss::Back_Sens,       constants::pins::uss::Trigger);
    uss BackRight  = uss(constants::pins::uss::BackRight_Sens,  constants::pins::uss::Trigger);
    uss FrontRight = uss(constants::pins::uss::FrontRight_Sens, constants::pins::uss::Trigger);

    public:
    bool CanGoFront()
    {
        return Front.MeasureDistance() > constants::uss::FrontBack_Min_Distance;
    }
    bool CanGoFrontLeft()
    {
        return FrontLeft.MeasureDistance() > constants::uss::Side_Min_Distance;
    }
    bool CanGoBackLeft()
    {
        return BackLeft.MeasureDistance() > constants::uss::Side_Min_Distance;
    }
    bool CanGoBack()
    {
        return Back.MeasureDistance() > constants::uss::FrontBack_Min_Distance;
    }
    bool CanGoBackRight()
    {
        return BackRight.MeasureDistance() > constants::uss::Side_Min_Distance;
    }
    bool CanGoFrontRight()
    {
        return FrontRight.MeasureDistance() > constants::uss::Side_Min_Distance;
    }
};