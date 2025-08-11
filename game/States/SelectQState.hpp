#pragma once

#include "GameState.hpp"
#include "StateManager.hpp"
#include "PlayState.hpp"

#include "game/Database/ExtraerDB.hpp"

#include <vector>
#include <memory>

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

    std::vector<std::string> temasQuizz;
    ExtraerDB database;
    int numeroDeTemas;

    std::vector<std::unique_ptr<BotonRectangular>> botonesEleccion;

    size_t idTema;
};