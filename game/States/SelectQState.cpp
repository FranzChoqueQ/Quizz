#include "SelectQState.hpp"

#include <stdexcept>

SelectQState::SelectQState(StateManager& manager): stateManager(manager){
    SDL_Color colorNormal = {0, 12, 102, 255};
    SDL_Color colorHover = {30, 64, 255, 255};

    temasQuizz = database.obtenerTemas();

    numeroDeTemas = temasQuizz.size();

    int buttonStartX[] = {50, 350, 650};
    int buttonStartY[] = {100, 200, 300};
    int buttonWidth = 250;
    int buttonHight = 80;

    for (int fila = 0; fila < 3; ++fila) {
        for (int col = 0; col < 3; ++col) {
            botonesEleccion.push_back(std::make_unique<BotonRectangular>(
                buttonStartX[col], buttonStartY[fila], buttonWidth, buttonHight, colorNormal, colorHover
            ));
        }
    }

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

    for (auto& boton : botonesEleccion){
        boton->render(window.getRenderer());
    }

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

    for(auto& botones : botonesEleccion){
        botones->handleEvents(eventHandler);
    }

    for(size_t i = 0; i<botonesEleccion.size(); i++){
        if (botonesEleccion[i]->isClicked(eventHandler)) {
            idTema = i + 1;
            stateManager.submitRequest(RequestChangeState{
                std::make_unique<PlayState>(stateManager, idTema)
            });
        }
    }
}
