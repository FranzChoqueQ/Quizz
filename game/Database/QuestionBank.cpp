#include "QuestionBank.hpp"

#include <iostream>

QuestionBank::QuestionBank(){
    preguntas = {
            // Fútbol
            "Cuantos jugadores tiene un equipo de futbol en cancha",
            "9", "10", "11", "12", "3",
            "Que seleccion ha ganado mas mundiales",
            "Alemania", "Argentina", "Italia", "Brasil", "4",
            "Que jugador tiene mas balones de oro",
            "Cristiano Ronaldo", "Lionel Messi", "Pelé", "Maradona", "2",
            "Que pais gano el primer mundial",
            "Uruguay", "Brasil", "Argentina", "Italia", "1",
            "En que año se jugo el primer mundial de futbol",
            "1928", "1930", "1932", "1934", "2",
            "Que equipo ha ganado mas Champions League",
            "Barcelona", "Liverpool", "Real Madrid", "Bayern Munich", "3",
            "Cual es el apodo de la seleccion de Brasil",
            "La Roja", "La Verdeamarela", "Los Cafeteros", "Los Charruas", "2",
            "Quien es el maximo goleador de los mundiales",
            "Pelé", "Ronaldo Nazario", "Klose", "Maradona", "3",
            "Que equipo de la Premier League tiene mas titulos",
            "Liverpool", "Arsenal", "Manchester United", "Chelsea", "3",
            "Cual es el clasico de España",
            "Sevilla vs Betis", "Barcelona vs Real Madrid", "Atletico vs Real Madrid", "Valencia vs Villarreal", "2",
        
            // Electrónica
            "Que mide un multimetro",
            "Resistencia", "Voltaje", "Corriente", "Todas las anteriores", "4",
            "Cual es la unidad de resistencia",
            "Voltio", "Ohm", "Amperio", "Faradio", "2",
            "Que significa LED",
            "Low Energy Device", "Light Emitting Diode", "Linear Electric Display", "Light Energy Distribution", "2",
            "Que componente almacena carga electrica",
            "Transistor", "Resistor", "Capacitor", "Diodo", "3",
            "Que tipo de corriente es usada en baterias",
            "Corriente alterna", "Corriente directa", "Ambas", "Ninguna", "2",
            "Cual es la funcion de un transformador",
            "Almacenar energia", "Convertir voltaje", "Reducir corriente", "Generar electrones", "2",
            "Que tipo de transistor es mas comun",
            "PNP", "NPN", "MOSFET", "FET", "2",
            "Que significa PCB en electronica",
            "Printed Circuit Board", "Power Control Board", "Parallel Chip Base", "Processing Central Box", "1",
            "Cual es la unidad de capacitancia",
            "Voltio", "Ohm", "Faradio", "Amperio", "3",
            "Cual es el uso principal de un osciloscopio",
            "Medir voltaje", "Medir frecuencia", "Observar señales electricas", "Producir ondas", "3"
        };
}

int QuestionBank::getTotalPreguntas(){
    return preguntas.size();
}

std::string QuestionBank::obtenerElemento(int indice){
    if(indice >= 0 && indice < getTotalPreguntas()){
        return preguntas[indice];
    } else {
        throw std::out_of_range("Índice fuera de rango.");
    }
}
