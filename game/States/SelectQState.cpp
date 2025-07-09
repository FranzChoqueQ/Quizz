#include "SelectQState.hpp"

#include <stdexcept>

SelectQState::SelectQState(StateManager& manager): stateManager(manager){
    SDL_Color colorNormal = {0, 12, 102, 255};
    SDL_Color colorHover = {30, 64, 255, 255};

    botonQ1 = std::make_unique<BotonRectangular>(
        50, 100, 250, 80, 
        colorNormal, colorHover
    );

    botonQ2 = std::make_unique<BotonRectangular>(
        50, 200, 250, 80, 
        colorNormal, colorHover
    );
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

    botonQ1->render(window.getRenderer());
    botonQ2->render(window.getRenderer());

    const std::string menuText = "Presiona S para Play";
    SDL_Color white = {255, 100, 0, 255};
    textRender.render(window.getRenderer(), menuText, 100, 280, white);
    
    window.present();
}

void SelectQState::handleEvents(EventHandler& eventHandler) {
    eventHandler.pollEvents();

    botonQ1->handleEvents(eventHandler);
    botonQ2->handleEvents(eventHandler);

    if (botonQ1->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_S)) {
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager)
        });
    }
}
