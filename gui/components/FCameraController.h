#ifndef __FCAMERA_CONTROLLER_H
#define __FCAMERA_CONTROLLER_H

#include <Qt3DExtras/QAbstractCameraController>
#include <Qt3DExtras/QOrbitCameraController>

#include "ForgeApplication.h"
#include "FModel.h"
#include "FOrigin.h"

class FCameraController : public Qt3DExtras::QAbstractCameraController {
private:

    FModel* m_focus;

    FOrigin* m_origin;

    inline float clampInputs(float input1, float input2)
    {
        float axisValue = input1 + input2;
        return (axisValue < -1) ? -1 : (axisValue > 1) ? 1 : axisValue;
    }

    void onSelection(FModel* t_model);

public:
    FCameraController();

    void moveCamera(const InputState& state, float dt) override;

};

#endif