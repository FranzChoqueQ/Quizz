#pragma once

#include "GameState.hpp"
#include "StateManager.hpp"
#include "PlayState.hpp"

#include "game/Database/ExtraerDB.hpp"

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

    std::unique_ptr<BotonRectangular> botonQ1;
    std::unique_ptr<BotonRectangular> botonQ2;
    std::unique_ptr<BotonRectangular> botonQ3;
    std::unique_ptr<BotonRectangular> botonQ4;
    std::unique_ptr<BotonRectangular> botonQ5;
    std::unique_ptr<BotonRectangular> botonQ6;
    std::unique_ptr<BotonRectangular> botonQ7;
    std::unique_ptr<BotonRectangular> botonQ8;
    std::unique_ptr<BotonRectangular> botonQ9;
    int idTema;
};