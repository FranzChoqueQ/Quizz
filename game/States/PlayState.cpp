#include "PlayState.hpp"
#include "StateManager.hpp"
#include "PauseState.hpp"  // Necesario para crear el estado de pausa
//#include "MenuState.hpp"   // Necesario para crear el estado de menú
#include "SelectQState.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "ResultState.hpp"

// Constructor
PlayState::PlayState(StateManager& manager) 
    : stateManager(manager) {
    // Inicialización de recursos específicos del estado
    SDL_Color colorNormal = {0, 12, 102, 255};
    SDL_Color colorHover = {30, 64, 255, 255};

    botonRespuesta1 = std::make_unique<BotonRectangular>(
        50, 200, 900, 100, 
        colorNormal, colorHover
    );

    botonRespuesta2 = std::make_unique<BotonRectangular>(
        50, 310, 900, 100, 
        colorNormal, colorHover
    );
    
    botonRespuesta3 = std::make_unique<BotonRectangular>(
        50, 420, 900, 100, 
        colorNormal, colorHover
    );

    botonRespuesta4 = std::make_unique<BotonRectangular>(
        50, 530, 900, 100, 
        colorNormal, colorHover
    );
}

void PlayState::enter() {
    // Cargar recursos al entrar al estado
    if (!textRender.loadFont("assets/fonts/times.ttf", 20)) {
        throw std::runtime_error("No se pudo cargar la fuente en PlayState");
    }
}

void PlayState::exit() {
    // Liberar recursos específicos del estado
}

void PlayState::update(float deltaTime) {
    // Lógica de actualización del juego
}

void PlayState::render(Window& window) {
    window.clear();

    textRender.setFontSize(20);
    
    // Renderizar elementos del juego
    SDL_Color black = {0, 0, 0, 255}; // Negro
    SDL_Color white = {255, 255, 255, 255}; // Negro
    
    // Obtener dimensiones de la ventana para centrar texto
    int screenWidth, screenHeight;
    SDL_GetWindowSize(window.getSDLWindow(), &screenWidth, &screenHeight);
    
    // Renderizar instrucciones
    const std::string instruction1 = "Presiona P para pausar";
    const std::string instruction2 = "Presiona F para Return";
    const std::string instruction3 = "Presiona T para ir END";

    textRender.render(window.getRenderer(), instruction1, 80, 20, black);
    textRender.render(window.getRenderer(), instruction2, 700, 20, black);
    textRender.render(window.getRenderer(), instruction3, 400, 20, black);

    textRender.setFontSize(40);
    // Pregunta
    const std::string mensajePregunta = "PREGUNTAS EJEMPLO";
    textRender.render(window.getRenderer(), mensajePregunta, 100, 100, black);

    // Botones respuestas
    botonRespuesta1->render(window.getRenderer());
    botonRespuesta2->render(window.getRenderer());
    botonRespuesta3->render(window.getRenderer());
    botonRespuesta4->render(window.getRenderer());

    // Respuestas
    const std::string mensajeRespuesta1 = "RESPUESTA 1 EJEMPLO";
    textRender.render(window.getRenderer(), mensajeRespuesta1, 80, 210, white);
    
    const std::string mensajeRespuesta2 = "RESPUESTA 2 EJEMPLO";
    textRender.render(window.getRenderer(), mensajeRespuesta1, 80, 320, white);

    const std::string mensajeRespuesta3 = "RESPUESTA 3 EJEMPLO";
    textRender.render(window.getRenderer(), mensajeRespuesta1, 80, 430, white);

    const std::string mensajeRespuesta4 = "RESPUESTA 4 EJEMPLO";
    textRender.render(window.getRenderer(), mensajeRespuesta1, 80, 540, white);

    window.present();
}

void PlayState::handleEvents(EventHandler& eventHandler) {
    eventHandler.pollEvents();

    botonRespuesta1->handleEvents(eventHandler);
    botonRespuesta2->handleEvents(eventHandler);
    botonRespuesta3->handleEvents(eventHandler);
    botonRespuesta4->handleEvents(eventHandler);

    if (eventHandler.isKeyPressed(SDL_SCANCODE_P)) {
        stateManager.submitRequest(StateRequest{
            RequestPushState{std::make_unique<PauseState>(stateManager)}  // Constructor correcto
        });
    }
    
    if (eventHandler.isKeyPressed(SDL_SCANCODE_F)) {
        stateManager.submitRequest(StateRequest{
            RequestChangeState{std::make_unique<SelectQState>(stateManager)}  // Constructor correcto
        });
    }

    if (eventHandler.isKeyPressed(SDL_SCANCODE_T)) {
        stateManager.submitRequest(StateRequest{
            RequestChangeState{std::make_unique<ResultState>(stateManager)}  // Constructor correcto
        });
    }
}