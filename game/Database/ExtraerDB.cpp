#include "ExtraerDB.hpp"

ExtraerDB::ExtraerDB() : db("dbquizz.db", SQLite::OPEN_READONLY) {}

int ExtraerDB::totalPreguntas(int idTema){
    SQLite::Statement totalP(db,
        "SELECT count(*) "
        "FROM preguntas "
        "WHERE id_tema = ? ");
    totalP.bind(1, idTema);
    return totalP.executeStep() ? totalP.getColumn(0).getInt() : 0;
}

std::string ExtraerDB::obtenerPregunta(int idTema, int indice) {
    SQLite::Statement query(db,
        "SELECT texto_pregunta "
        "FROM preguntas "
        "WHERE id_tema = ? "
        "LIMIT 1 "
        "OFFSET ?");
    query.bind(1, idTema);
    query.bind(2, indice);
    return query.executeStep() ? query.getColumn(0).getString() : "";;
}

int ExtraerDB::obteneridPregunta(int idTema, int indice) {
    SQLite::Statement query(db,
        "SELECT id_pregunta "
        "FROM preguntas "
        "WHERE id_tema = ? "
        "LIMIT 1 "
        "OFFSET ? ");
    query.bind(1, idTema);
    query.bind(2, indice);
    idPregunta = query.executeStep() ? query.getColumn(0).getInt() : -1;
    return idPregunta;
}

std::vector<std::pair<std::string, bool>> ExtraerDB::obtenerRespuestas(int idPregunta) {

    std::vector<std::pair<std::string, bool>> respuestas;
    SQLite::Statement query(db,
        "SELECT texto_respuesta, correcta "
        "FROM respuestas "
        "WHERE id_pregunta = ? ");
    query.bind(1, idPregunta);
    
    while(query.executeStep()){
        respuestas.emplace_back(
            query.getColumn(0).getString(),
            query.getColumn(1).getInt() != 0
        );
    }
    return respuestas;
}

std::vector<std::string> ExtraerDB::obtenerTemas(){
    std::vector<std::string> temas;
    SQLite::Statement query(db,
    "SELECT nombre_tema "
    "FROM temas ");
    
    while(query.executeStep()){
        temas.emplace_back(query.getColumn(0).getString());
    }

    return temas;
}
