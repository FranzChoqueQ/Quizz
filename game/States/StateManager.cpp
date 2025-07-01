#include "StateManager.hpp"

// Colocar estado sin afectar el estado anterior
void StateManager::pushState(std::unique_ptr<GameState> state) {
    if (!states.empty()) {
        states.top()->exit();
    }
    states.push(std::move(state));
    states.top()->enter();
}
// Remover el estado que entro ultimo
void StateManager::popState() {
    if (!states.empty()) {
        states.top()->exit();
        states.pop();
    }
    if (!states.empty()) {
        states.top()->enter();
    }
}

// Reemplazar un estado por otro
void StateManager::changeState(std::unique_ptr<GameState> state) {
    while (!states.empty()) {
        popState();
    }
    pushState(std::move(state));
}

// Actualizar estado
void StateManager::update(float deltaTime) {
    if (!states.empty()) {
        states.top()->update(deltaTime);
    }
}

// Renderizado
void StateManager::render(Window& window) {
    if (!states.empty()) {
        states.top()->render(window);
    }
}

//Manejar eventos
void StateManager::handleEvents(EventHandler& eventHandler) {
    if (!states.empty()) {
        states.top()->handleEvents(eventHandler);
    }
}

// ¿Esta vacio?
bool StateManager::isEmpty() const {
    return states.empty();
}

// Pedir evento
void StateManager::submitRequest(StateRequest request) {
    requestHandler.handleRequest(std::move(request));
}

// Procesar evento
void StateManager::processRequests() {
    requestHandler.applyRequests(*this);
    
    // Opcional: limpieza de estados muertos
    while (!states.empty() && states.top() == nullptr) {
        states.pop();
    }
}