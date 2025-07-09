#pragma once

#include "BotonRectangular.hpp"

class BotonRespuesta : public BotonRectangular{
public:
    BotonRespuesta(int x, int y, int w, int h,
                   SDL_Color colorNormal, SDL_Color colorHover,
                   SDL_Color colorCorrecto, SDL_Color colorIncorrecto, int idRespuesta);

    int getIdRespuesta() const;
    void isCorrect();
    void isIncorrect();

    void handleEvents(const EventHandler& eventHandler) override;
    void reiniciarEstado();

    SDL_Color colorCorrecto;
    SDL_Color colorIncorrecto;

    //using BotonRectangular::render;
private:
    int idRespuesta;
    bool respondido;
};
