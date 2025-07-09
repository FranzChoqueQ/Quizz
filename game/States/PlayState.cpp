#include "PlayState.hpp"
#include "StateManager.hpp"
#include "PauseState.hpp"  // Necesario para crear el estado de pausa
//#include "MenuState.hpp"   // Necesario para crear el estado de menú
#include "SelectQState.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "ResultState.hpp"

#include "iostream"

// Constructor
PlayState::PlayState(StateManager& manager) 
    : stateManager(manager) {
    // Inicialización de recursos específicos del estado
    SDL_Color colorNormal = {0, 12, 102, 255};
    SDL_Color colorHover = {30, 64, 255, 255};
    SDL_Color colorCorrecto = {0, 200, 0, 255};
    SDL_Color colorIncorrecto = {200, 0, 0, 255};
    
    //std::vector<BotonRespuesta> opciones;

    opciones.emplace_back(50, 200, 900, 100, colorNormal, colorHover, colorCorrecto,colorIncorrecto, 1);
    opciones.emplace_back(50, 310, 900, 100, colorNormal, colorHover, colorCorrecto,colorIncorrecto, 2);
    opciones.emplace_back(50, 420, 900, 100, colorNormal, colorHover, colorCorrecto,colorIncorrecto, 3);
    opciones.emplace_back(50, 530, 900, 100, colorNormal, colorHover, colorCorrecto,colorIncorrecto, 4);


    botonSiguientePregunta = std::make_unique<BotonRectangular>(
        800, 640, 80, 50, 
        colorNormal, colorHover
    );

    botonAnteriorPregunta = std::make_unique<BotonRectangular>(
        700, 640, 80, 50, 
        colorNormal, colorHover
    );

    punteroPreguntas = 0;
    preguntaActual = 1;
    respCorrectas = 0;
    respIncorrectas = 0;

    historialResp = {};
    first = true;
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
    if (siguientePregunta){
        punteroPreguntas += 6;
        siguientePregunta = false;
        preguntaActual += 1;
        first = true;
    }

    if (anteriorPregunta){
        punteroPreguntas -= 6;
        anteriorPregunta = false;
        preguntaActual -= 1;
        first = true;
    }
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
    const std::string totalPreguntas = std::to_string(preguntas.getTotalPreguntas()/6);
    const std::string currentCuestion = std::to_string(preguntaActual);

    textRender.render(window.getRenderer(), instruction1, 80, 20, black);
    textRender.render(window.getRenderer(), instruction2, 700, 20, black);
    textRender.render(window.getRenderer(), instruction3, 400, 20, black);
    textRender.render(window.getRenderer(), totalPreguntas, 900, 40, black);
    textRender.render(window.getRenderer(), currentCuestion, 860, 40, black);
    
    textRender.setFontSize(25);
    // Pregunta
    const std::string mensajePregunta = preguntas.obtenerElemento(punteroPreguntas);
    textRender.render(window.getRenderer(), mensajePregunta, 100, 100, black);

    // Botones respuestas
    for(auto& boton : opciones){
        boton.render(window.getRenderer());
    }

    botonSiguientePregunta->render(window.getRenderer());
    botonAnteriorPregunta->render(window.getRenderer());

    // Respuestas
    const std::string mensajeRespuesta1 = preguntas.obtenerElemento(punteroPreguntas + 1);
    textRender.render(window.getRenderer(), mensajeRespuesta1, 80, 210, white);
    
    const std::string mensajeRespuesta2 = preguntas.obtenerElemento(punteroPreguntas + 2);
    textRender.render(window.getRenderer(), mensajeRespuesta2, 80, 320, white);

    const std::string mensajeRespuesta3 = preguntas.obtenerElemento(punteroPreguntas + 3);
    textRender.render(window.getRenderer(), mensajeRespuesta3, 80, 430, white);

    const std::string mensajeRespuesta4 = preguntas.obtenerElemento(punteroPreguntas + 4);
    textRender.render(window.getRenderer(), mensajeRespuesta4, 80, 540, white);

    const std::string mensajeSiguiente = "S";
    textRender.render(window.getRenderer(), mensajeSiguiente, 826, 642, white);

    const std::string mensajeAnterior = "A";
    textRender.render(window.getRenderer(), mensajeAnterior, 726, 642, white);

    window.present();
}

void PlayState::handleEvents(EventHandler& eventHandler) {
    eventHandler.pollEvents();

    for(auto& boton : opciones){
        boton.handleEvents(eventHandler);
        if(boton.isClicked(eventHandler)){
            if(std::to_string(boton.getIdRespuesta()) == preguntas.obtenerElemento(punteroPreguntas+5)){
                boton.isCorrect();
                if(first){
                    respCorrectas += 1;
                    first = false;
                }
            } else {
                boton.isIncorrect();
                if(first){
                    respIncorrectas += 1;
                    first = false;
                }
            }
            std::cout<<boton.getIdRespuesta();
        }
    }

    botonSiguientePregunta->handleEvents(eventHandler);
    botonAnteriorPregunta->handleEvents(eventHandler);

    if (botonSiguientePregunta->isClicked(eventHandler)){
        if (punteroPreguntas+6 < preguntas.getTotalPreguntas()){
            siguientePregunta = true;
        }
        else {
            siguientePregunta = false;
            stateManager.submitRequest(StateRequest{
                RequestChangeState{std::make_unique<ResultState>(stateManager, respCorrectas, respIncorrectas)}
            });
        }
        for(auto& boton : opciones){
            boton.reiniciarEstado();
        }
    }

    if (botonAnteriorPregunta->isClicked(eventHandler)){
        if (punteroPreguntas != 0){
            anteriorPregunta = true;
        }
        else {
            anteriorPregunta = false;
        }
        for(auto& boton : opciones){
            boton.reiniciarEstado();
        }
    }

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
            RequestChangeState{std::make_unique<ResultState>(stateManager, respCorrectas, respIncorrectas)}  // Constructor correcto
        });
    }
}