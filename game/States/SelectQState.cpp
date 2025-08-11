#include "SelectQState.hpp"

#include <stdexcept>

SelectQState::SelectQState(StateManager& manager): stateManager(manager){
    SDL_Color colorNormal = {0, 12, 102, 255};
    SDL_Color colorHover = {30, 64, 255, 255};

    temasQuizz = database.obtenerTemas();

    numeroDeTemas = temasQuizz.size();

    botonQ1 = std::make_unique<BotonRectangular>(
        50, 100, 250, 80, 
        colorNormal, colorHover
    );

    botonQ2 = std::make_unique<BotonRectangular>(
        350, 100, 250, 80, 
        colorNormal, colorHover
    );

    botonQ3 = std::make_unique<BotonRectangular>(
        650, 100, 250, 80, 
        colorNormal, colorHover
    );

    botonQ4 = std::make_unique<BotonRectangular>(
        50, 200, 250, 80, 
        colorNormal, colorHover
    );

    botonQ5 = std::make_unique<BotonRectangular>(
        350, 200, 250, 80, 
        colorNormal, colorHover
    );

    botonQ6 = std::make_unique<BotonRectangular>(
        650, 200, 250, 80, 
        colorNormal, colorHover
    );

    botonQ7 = std::make_unique<BotonRectangular>(
        50, 300, 250, 80, 
        colorNormal, colorHover
    );

    botonQ8 = std::make_unique<BotonRectangular>(
        350, 300, 250, 80, 
        colorNormal, colorHover
    );

    botonQ9 = std::make_unique<BotonRectangular>(
        650, 300, 250, 80, 
        colorNormal, colorHover
    );
}

void SelectQState::enter(){
    if (!textRender.loadFont("assets/fonts/arial.ttf", 40)) {
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
    botonQ3->render(window.getRenderer());
    botonQ4->render(window.getRenderer());
    botonQ5->render(window.getRenderer());
    botonQ6->render(window.getRenderer());
    botonQ7->render(window.getRenderer());
    botonQ8->render(window.getRenderer());
    botonQ9->render(window.getRenderer());

    const std::string menuText = "Presiona S para Play";
    SDL_Color white = {255, 255, 255, 255};
    SDL_Color black = {0, 0, 0, 255};
    textRender.render(window.getRenderer(), menuText, 10, 10, black);
    
    int count = 0;
    int filaX = 60;
    int colY = 110;

    for(auto& tema : temasQuizz){
        count += 1;

        textRender.render(window.getRenderer(), tema, filaX, colY, white);

        filaX += 300;

        if(count == 3){
            filaX = 60;
            colY += 100;
            count = 0;
        }
    }


    window.present();
}

void SelectQState::handleEvents(EventHandler& eventHandler) {

    botonQ1->handleEvents(eventHandler);
    botonQ2->handleEvents(eventHandler);
    botonQ3->handleEvents(eventHandler);
    botonQ4->handleEvents(eventHandler);
    botonQ5->handleEvents(eventHandler);
    botonQ6->handleEvents(eventHandler);
    botonQ7->handleEvents(eventHandler);
    botonQ8->handleEvents(eventHandler);
    botonQ9->handleEvents(eventHandler);

    if (botonQ1->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_S)) {
        idTema = 1;
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager, idTema)
        });
    }

    if (botonQ2->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_A)) {
        idTema = 2;
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager, idTema)
        });
    }

    if (botonQ3->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_S)) {
        idTema = 3;
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager, idTema)
        });
    }

    if (botonQ4->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_A)) {
        idTema = 4;
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager, idTema)
        });
    }
    if (botonQ5->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_S)) {
        idTema = 5;
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager, idTema)
        });
    }

    if (botonQ6->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_A)) {
        idTema = 6;
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager, idTema)
        });
    }
    if (botonQ7->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_S)) {
        idTema = 7;
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager, idTema)
        });
    }

    if (botonQ8->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_A)) {
        idTema = 8;
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager, idTema)
        });
    }

    if (botonQ9->isClicked(eventHandler) | eventHandler.isKeyPressed(SDL_SCANCODE_A)) {
        idTema = 9;
        stateManager.submitRequest(RequestChangeState{
            std::make_unique<PlayState>(stateManager, idTema)
        });
    }
}
