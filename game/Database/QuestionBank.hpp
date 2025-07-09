#pragma once

#include <vector>
#include <string>

class QuestionBank{
public:
    QuestionBank();
    int getTotalPreguntas();
    std::string obtenerElemento(int indice);
private:
    std::vector<std::string> preguntas;
};


