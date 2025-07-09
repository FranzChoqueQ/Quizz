#pragma once

#include <vector>

#include "GameState.hpp"
#include "engine/graphics/shapes/BotonRectangular.hpp"
#include "game/Database/QuestionBank.hpp"
#include "BotonRespuesta.hpp"

class StateManager;

class PlayState : public GameState {
public:
    explicit PlayState(StateManager& manager);
    
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void render(Window& window) override;
    void handleEvents(EventHandler& eventHandler) override;
    
private:
    StateManager& stateManager;
    // ... otros miembros ...
    std::unique_ptr<BotonRectangular> botonSiguientePregunta;
    std::unique_ptr<BotonRectangular> botonAnteriorPregunta;
    /*std::unique_ptr<BotonRectangular> botonRespuesta2;
    std::unique_ptr<BotonRectangular> botonRespuesta3;
    std::unique_ptr<BotonRectangular> botonRespuesta4;*/

    int punteroPreguntas;
    int preguntaActual;
    int respCorrectas;
    int respIncorrectas;
    bool first; // control para primera respuesta

    std::vector<int> historialResp;
    
    QuestionBank preguntas;
    std::vector<BotonRespuesta> opciones;

    SDL_Color colorCorrecto;

    bool siguientePregunta;
    bool anteriorPregunta;
};