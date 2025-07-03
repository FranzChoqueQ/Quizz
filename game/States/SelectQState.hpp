#pragma once

#include "GameState.hpp"
#include "StateManager.hpp"
#include "PlayState.hpp"

class SelectQState : public GameState{
public:
    SelectQState(StateManager& manager);
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void render(Window& window) override;
    void handleEvents(EventHandler& eventHandler) override;

    StateManager& stateManager;
private:
    std::unique_ptr<BotonRectangular> botonQ1;
    std::unique_ptr<BotonRectangular> botonQ2;
};