#include "ResultState.hpp"

#include "MenuState.hpp"

ResultState::ResultState(StateManager& manager, int acertadas, int fallas) : stateManager(manager), numAciertos(acertadas), numFallas(fallas)  {}

void ResultState::enter() {
    if (!textRender.loadFont("assets/fonts/arial.ttf", 36)) {
        throw std::runtime_error("No se pudo cargar la fuente en PlayState");
    }
}

void ResultState::exit() {
    // Limpieza
}

void ResultState::update(float deltaTime) {
    // Lógica de actualización del menú
}

void ResultState::render(Window& window) {
    window.clear();

    const std::string menuText = "Presiona M para volver al menu";
    SDL_Color white = {50, 0, 0, 255};
    textRender.render(window.getRenderer(), menuText, 100, 100, white);

    const std::string textoAciertos = "Respuestas Acertadas: " + std::to_string(numAciertos);
    textRender.render(window.getRenderer(), textoAciertos, 100, 200, white);

    const std::string textoFallos = "Respuestas Erradas: " + std::to_string(numFallas);
    textRender.render(window.getRenderer(), textoFallos, 100, 300, white);
    
    window.present();
}

void ResultState::handleEvents(EventHandler& eventHandler) {
    if (eventHandler.isKeyPressed(SDL_SCANCODE_M)) {
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<MenuState>(stateManager)
        });
    }
}