#ifndef __FCAMERA_CONTROLLER_H
#define __FCAMERA_CONTROLLER_H

#include <Qt3DExtras/QAbstractCameraController>

#include "ForgeApplication.h"
#include "FOrigin.h"
#include "Defines.h"

class FCameraController : public QtAbstractController {
private:

    FOrigin* m_origin;  /*!< The origin symbol to display (x/y/z lines)*/

    inline float clampInputs(float input1, float input2)
    {
        float axisValue = input1 + input2;
        return (axisValue < -1) ? -1 : (axisValue > 1) ? 1 : axisValue;
    }

public:
    FCameraController();

    void moveCamera(const InputState& state, float dt) override;

};

#endif