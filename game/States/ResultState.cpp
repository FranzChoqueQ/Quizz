#include "ResultState.hpp"

#include "MenuState.hpp"

ResultState::ResultState(StateManager& manager) : stateManager(manager) {}

void ResultState::enter() {
    // Inicialización específica del menú
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
    //textRender.loadFont("assets/fonts/arial.ttf", 36);
    // Renderizar texto "Aquí es el menú"
    const std::string menuText = "Presiona M para volver al menu";
    SDL_Color white = {255, 100, 255, 255};
    //int textX = (screenWidth - textRenderer.getTextWidth(menuText)) / 2;
    //int textY = (screenHeight / 2) - 50;
    textRender.render(window.getRenderer(), menuText, 100, 280, white);
    
    window.present();
}

void ResultState::handleEvents(EventHandler& eventHandler) {
    eventHandler.pollEvents();

    if (eventHandler.isKeyPressed(SDL_SCANCODE_M)) {
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<MenuState>(stateManager)
        });
    }
}