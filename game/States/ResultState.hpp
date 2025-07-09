#pragma once

#include "GameState.hpp"
#include "StateManager.hpp"

#include "stdexcept"

class ResultState : public GameState{
public:
    ResultState(StateManager& manager, int acertadas, int fallas);
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void render(Window& window) override;
    void handleEvents(EventHandler& eventHandler) override;

    StateManager& stateManager;
    int numAciertos;
    int numFallas;
private:

};