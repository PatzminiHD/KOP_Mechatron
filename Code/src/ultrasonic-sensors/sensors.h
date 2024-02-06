#include "uss.h"
#include "../vars/constants.h"

class Sensors
{
    private:
    uss Front = uss(constants::pins::uss::Front_Sens, constants::pins::uss::Trigger);
    uss Back  = uss(constants::pins::uss::Back_Sens,  constants::pins::uss::Trigger);
    uss Left  = uss(constants::pins::uss::Left_Sens,  constants::pins::uss::Trigger);
    uss Right = uss(constants::pins::uss::Right_Sens, constants::pins::uss::Trigger);

    public:
    bool CanGoFront()
    {
        return Front.MeasureDistance() > constants::uss::FrontBack_Min_Distance;
    }
    bool CanGoBack()
    {
        return Back.MeasureDistance() > constants::uss::FrontBack_Min_Distance;
    }
    bool CanGoLeft()
    {
        return Left.MeasureDistance() > constants::uss::Side_Min_Distance;
    }
    bool CanGoRight()
    {
        return Right.MeasureDistance() > constants::uss::Side_Min_Distance;
    }
};