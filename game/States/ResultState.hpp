#pragma once

#include "GameState.hpp"
#include "StateManager.hpp"

#include "stdexcept"

class ResultState : public GameState{
public:
    ResultState(StateManager& manager);
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void render(Window& window) override;
    void handleEvents(EventHandler& eventHandler) override;

    StateManager& stateManager;
private:

};