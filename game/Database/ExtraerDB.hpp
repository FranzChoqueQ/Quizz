#pragma once

#include <iostream>
#include <vector>
#include "SQLiteCpp/SQLiteCpp.h"

class ExtraerDB{
public:
    ExtraerDB();
    
    int totalPreguntas(int idTema);
    std::string obtenerPregunta(int idTema, int indice);
    int obteneridPregunta(int idTema, int indice);
    std::vector<std::pair<std::string, bool>> obtenerRespuestas(int idPregunta);
    std::vector<std::string> obtenerTemas();

private:
    SQLite::Database db;
    int idPregunta;
};
