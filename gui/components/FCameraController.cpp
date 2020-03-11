#include "FCameraController.h"

FCameraController::FCameraController()
    : m_focus(nullptr)
    , m_origin(new FOrigin())
{
    auto app = ForgeApplication::instance();
    (void)app->connect(app, &ForgeApplication::selectionChanged, 
                       this, &FCameraController::onSelection);

    app->render(m_origin);
}

void FCameraController::moveCamera(const InputState& state, float dt) {
    auto cam = camera();

    if (cam == nullptr)
        return;

    const QVector3D up(0.0f, 0.0f, 1.0f);

    if (state.leftMouseButtonActive) {
        cam->translate(QVector3D(clampInputs(state.rxAxisValue, state.txAxisValue) * linearSpeed(),
                                 clampInputs(state.ryAxisValue, state.tyAxisValue) * linearSpeed(),
                                 0) * dt);
        return;
    }
    else if (state.rightMouseButtonActive) {
        cam->pan((state.rxAxisValue * lookSpeed()) * dt, up);
        cam->tilt((state.ryAxisValue * lookSpeed()) * dt);
    }

    cam->translate(QVector3D(clampInputs(0, state.txAxisValue) * linearSpeed(),
                             clampInputs(0, state.tyAxisValue) * linearSpeed(),
                             state.tzAxisValue * linearSpeed()) * dt);

}

void FCameraController::onSelection(FModel* t_model) {
    if (t_model != nullptr) {
        m_origin->transform()->setTranslation(
            t_model->transform()->translation());
    }
}