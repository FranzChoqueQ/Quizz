#include "BotonRespuesta.hpp"

BotonRespuesta::BotonRespuesta(int x, int y, int w, int h,
                   SDL_Color colorNormal, SDL_Color colorHover,
                   SDL_Color colorCorrecto, SDL_Color colorIncorrecto, int idRespuesta)
                   : BotonRectangular(x, y, w, h, colorNormal, colorHover), 
                   colorCorrecto(colorCorrecto), 
                   colorIncorrecto(colorIncorrecto),
                   idRespuesta(idRespuesta) {
                    respondido = false;
                   }

int BotonRespuesta::getIdRespuesta() const {
    return idRespuesta;
}

void BotonRespuesta::isCorrect(){
    respondido = true;
    setColor(colorCorrecto);
}

void BotonRespuesta::isIncorrect(){
    respondido = true;
    setColor(colorIncorrecto);
}

void BotonRespuesta::handleEvents(const EventHandler& eventHandler){
    if (respondido) return;

    if (isMouseOver(eventHandler)) {
        setColor(colorHover);
    } else {
        setColor(colorNormal);
    }
}

void BotonRespuesta::reiniciarEstado(){
    respondido = false;
    setColor(colorNormal);
}
