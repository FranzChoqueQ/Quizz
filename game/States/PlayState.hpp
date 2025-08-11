#pragma once

#include <vector>

#include "GameState.hpp"
#include "engine/graphics/shapes/BotonRectangular.hpp"
#include "BotonRespuesta.hpp"
#include "game/Database/ExtraerDB.hpp"
#include "StateManager.hpp"

class PlayState : public GameState {
public:
    explicit PlayState(StateManager& manager, int idTema);
    
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void render(Window& window) override;
    void handleEvents(EventHandler& eventHandler) override;
    
private:
    StateManager& stateManager;

    std::unique_ptr<BotonRectangular> botonSiguientePregunta;
    std::unique_ptr<BotonRectangular> botonAnteriorPregunta;

    int punteroPreguntas;
    int preguntaActual;
    int respCorrectas;
    int respIncorrectas;
    bool firstResp; // control para primera respuesta

    int idTema;
    int idPregunta;
    std::vector<std::pair<std::string, bool>> respuestas;

    std::vector<int> historialResp;
    
    //QuestionBank preguntas;
    ExtraerDB database;
    std::vector<BotonRespuesta> opciones;

    SDL_Color colorCorrecto;

    bool siguientePregunta;
    bool anteriorPregunta;
};