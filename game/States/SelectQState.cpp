#include "SelectQState.hpp"

#include <stdexcept>

SelectQState::SelectQState(StateManager& manager): stateManager(manager){

}
void SelectQState::enter(){
    if (!textRender.loadFont("assets/fonts/arial.ttf", 36)) {
        throw std::runtime_error("No se pudo cargar la fuente en PlayState");
    }
}

void SelectQState::exit() {
    // Limpieza
}

void SelectQState::update(float deltaTime) {
    // Lógica de actualización del menú
}

void SelectQState::render(Window& window) {
    window.clear();
    //textRender.loadFont("assets/fonts/arial.ttf", 36);
    // Renderizar texto "Aquí es el menú"
    const std::string menuText = "Presiona S para Play";
    SDL_Color white = {255, 100, 0, 255};
    //int textX = (screenWidth - textRenderer.getTextWidth(menuText)) / 2;
    //int textY = (screenHeight / 2) - 50;
    textRender.render(window.getRenderer(), menuText, 100, 280, white);
    
    window.present();
}

void SelectQState::handleEvents(EventHandler& eventHandler) {
    eventHandler.pollEvents();

    if (eventHandler.isKeyPressed(SDL_SCANCODE_S)) {
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager)
        });
    }
}

/*
SelectQState(StateManager& manager);
    void enter() override;
    void exit() override;
    void update(float deltaTime) override;
    void render(Window& window) override;
    void handleEvents(EventHandler& eventHandler) override;
*/