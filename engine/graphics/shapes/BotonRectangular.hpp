#pragma once

#include "Rectangle.hpp"
//#include <functional>

class BotonRectangular : public Rectangle {
public:
    // Constructor con función de callback para el click
    BotonRectangular(int x, int y, int w, int h, 
                    SDL_Color colorNormal, 
                    SDL_Color colorHover);
    
    void render(SDL_Renderer* renderer) const override;
    virtual void handleEvents(const EventHandler& eventHandler);

    SDL_Color colorNormal;
    SDL_Color colorHover;
private:
    
    //std::function<void()> onClick;
};
