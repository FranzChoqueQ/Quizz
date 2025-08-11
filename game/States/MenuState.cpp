#include "MenuState.hpp"
#include "SelectQState.hpp"
#include "PlayState.hpp"
#include "StateManager.hpp"
#include "PauseState.hpp" 
#include <SDL2/SDL_ttf.h>
#include <stdexcept>
#include <iostream>

MenuState::MenuState(StateManager& manager) : stateManager(manager) {
    SDL_Color colorNormal = {0, 12, 102, 255};
    SDL_Color colorHover = {30, 64, 255, 255};

    botonInicio = std::make_unique<BotonRectangular>(
        300, 300, 400, 100, 
        colorNormal, colorHover
    );

    botonSalir = std::make_unique<BotonRectangular>(
        300, 500, 400, 100, 
        colorNormal, colorHover
    );    
}

void MenuState::enter() {
    if (!textRender.loadFont("assets/fonts/times.ttf", 90)) {
        throw std::runtime_error("No se pudo cargar la fuente en PlayState");
    }
}

void MenuState::exit() {
    // Limpieza
}

void MenuState::update(float deltaTime) {
    // Lógica de actualización del menú
}

void MenuState::render(Window& window) {
    window.clear();

    textRender.setFontSize(90);

    botonInicio->render(window.getRenderer());
    botonSalir->render(window.getRenderer());

    // Texto Inciar Escalado para las dimensiones del Boton Iniciar
    const std::string inicioText = "INICIAR";
    SDL_Color blanco = {255, 255, 255, 255};
    SDL_Rect buttInicioDimensiones = botonInicio->getRect();

    int textInicioX = buttInicioDimensiones.x + ((buttInicioDimensiones.w - textRender.getTextWidth(inicioText)) / 2);
    int textInicioY = buttInicioDimensiones.y + ((buttInicioDimensiones.h - textRender.getTextHeight(inicioText)) / 2);

    textRender.render(window.getRenderer(), inicioText, textInicioX, textInicioY, blanco);

    // Texto Salir Escalado para las dimensiones del Boton Iniciar
    const std::string salirText = "SALIR";
    SDL_Rect buttSalirDimensiones = botonSalir->getRect();

    int textSalirX = buttSalirDimensiones.x + ((buttSalirDimensiones.w - textRender.getTextWidth(salirText)) / 2);
    int textSalirY = buttSalirDimensiones.y + ((buttSalirDimensiones.h - textRender.getTextHeight(salirText)) / 2);

    textRender.render(window.getRenderer(), salirText, textSalirX, textSalirY, blanco);

    // Titulo
    const std::string textTitle = "QUIZZ";
    SDL_Color blue = {0, 51, 102, 255};
    textRender.render(window.getRenderer(), textTitle, 350, 100, blue);

    // Mensaje de inicio
    textRender.setFontSize(30);
    const std::string menuText = "Press K Iniciar";
    SDL_Color black = {0, 0, 0, 255};
    textRender.render(window.getRenderer(), menuText, 100, 650, black);

    const std::string mensajeSalir = "ESC para Salir";
    textRender.render(window.getRenderer(), mensajeSalir, 750, 650, black);
    
    window.present();
}

void MenuState::handleEvents(EventHandler& eventHandler) {
    botonInicio->handleEvents(eventHandler);
    botonSalir->handleEvents(eventHandler);

    if (botonInicio->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_K)) {
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<SelectQState>(stateManager)
        });
    }

    if (botonSalir->isClicked(eventHandler)){
        eventHandler.salir();
    }
}