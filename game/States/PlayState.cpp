#include "PlayState.hpp"
#include "StateManager.hpp"
#include "PauseState.hpp" 
#include "SelectQState.hpp"
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include "ResultState.hpp"

#include "iostream"

// Constructor
PlayState::PlayState(StateManager& manager, int idTema) 
    : stateManager(manager), idTema(idTema) {
    // Inicialización de recursos específicos del estado
    SDL_Color colorNormal = {0, 12, 102, 255};
    SDL_Color colorHover = {30, 64, 255, 255};
    SDL_Color colorCorrecto = {0, 200, 0, 255};
    SDL_Color colorIncorrecto = {200, 0, 0, 255};

    // Botones de opciones
    int buttonStartX = 50;
    int buttonStartY[] = {200, 310, 420, 530};
    int buttonWidth = 900;
    int buttonHight = 100;

    for(int fila = 0; fila < 4; ++fila){
        opciones.emplace_back(buttonStartX, buttonStartY[fila], buttonWidth, buttonHight, colorNormal, colorHover, colorCorrecto, colorIncorrecto, fila+1);
    }

    // Botones para desplazamiento entre preguntas
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
    firstResp = true;
}

void PlayState::enter() {
    // Cargar recursos al entrar al estado
    if (!textRender.loadFont("assets/fonts/timesbd.ttf", 20)) {
        throw std::runtime_error("No se pudo cargar la fuente en PlayState");
    }
}

void PlayState::exit() {
    // Liberar recursos específicos del estado
}

void PlayState::update(float deltaTime) {
    // Lógica de actualización del juego
    if (siguientePregunta){
        punteroPreguntas += 1;
        siguientePregunta = false;
        preguntaActual += 1;
        firstResp = true;
    }

    if (anteriorPregunta){
        punteroPreguntas -= 1;
        anteriorPregunta = false;
        preguntaActual -= 1;
        firstResp = true;
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
    //const std::string totalPreguntas = std::to_string(preguntas.getTotalPreguntas()/6);
    //const std::string currentCuestion = std::to_string(preguntaActual);
    const std::string totalPreguntas = std::to_string(database.totalPreguntas(idTema));
    const std::string currentCuestion = std::to_string(preguntaActual);

    textRender.render(window.getRenderer(), instruction1, 80, 20, black);
    textRender.render(window.getRenderer(), instruction2, 700, 20, black);
    textRender.render(window.getRenderer(), instruction3, 400, 20, black);
    textRender.render(window.getRenderer(), totalPreguntas, 900, 40, black);
    textRender.render(window.getRenderer(), currentCuestion, 860, 40, black);
    
    textRender.setFontSize(25);
    // Pregunta
    const std::string mensajePregunta = database.obtenerPregunta(idTema, punteroPreguntas);
    textRender.render(window.getRenderer(), mensajePregunta, 40, 100, black);

    // Botones respuestas
    for(auto& boton : opciones){
        boton.render(window.getRenderer());
    }

    botonSiguientePregunta->render(window.getRenderer());
    botonAnteriorPregunta->render(window.getRenderer());

    idPregunta = database.obteneridPregunta(idTema, punteroPreguntas);

    respuestas = database.obtenerRespuestas(idPregunta);

    // Respuestas
    const std::string mensajeRespuesta1 = respuestas[0].first;
    textRender.render(window.getRenderer(), mensajeRespuesta1, 80, 210, white);
    
    const std::string mensajeRespuesta2 = respuestas[1].first;
    textRender.render(window.getRenderer(), mensajeRespuesta2, 80, 320, white);

    const std::string mensajeRespuesta3 = respuestas[2].first;
    textRender.render(window.getRenderer(), mensajeRespuesta3, 80, 430, white);

    const std::string mensajeRespuesta4 = respuestas[3].first;
    textRender.render(window.getRenderer(), mensajeRespuesta4, 80, 540, white);

    const std::string mensajeSiguiente = "S";
    textRender.render(window.getRenderer(), mensajeSiguiente, 826, 642, white);

    const std::string mensajeAnterior = "A";
    textRender.render(window.getRenderer(), mensajeAnterior, 726, 642, white);

    window.present();
}

void PlayState::handleEvents(EventHandler& eventHandler) {
    for(auto& boton : opciones){
        boton.handleEvents(eventHandler);
        if(boton.isClicked(eventHandler)){
            if(respuestas[boton.getIdRespuesta()-1].second){
                boton.isCorrect();
                if(firstResp){
                    respCorrectas += 1;
                    firstResp = false;
                }
            } else {
                boton.isIncorrect();
                if(firstResp){
                    respIncorrectas += 1;
                    firstResp = false;
                }
            }
            //std::cout<<boton.getIdRespuesta();
        }
    }

    botonSiguientePregunta->handleEvents(eventHandler);
    botonAnteriorPregunta->handleEvents(eventHandler);

    if (botonSiguientePregunta->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_RIGHT)){
        if (punteroPreguntas+1 < database.totalPreguntas(idTema)){
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

    if (botonAnteriorPregunta->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_LEFT)){
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