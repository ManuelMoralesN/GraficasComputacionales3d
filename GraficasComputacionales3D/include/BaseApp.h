//Manuel Morales GC3D
#pragma once
#include "Prerequisites.h"
#include "Window.h"
#include "ShapeFactory.h"
#include "Actor.h"

class BaseApp
{
public:
    BaseApp() = default;
    ~BaseApp() = default;

    //Funcion encargada de ejecutar la aplicacion en main
    int run();

    //Funcion de inicializacion 
    bool 
    initialize();

    //Funcion que se actualiza por frame
    void 
    update();

    //Funcion de renderizado
    void 
    render();

    // Limpiar recursos
    void 
    cleanup();

    // Actualizar el movimiento del círculo entre waypoints
    void 
    updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle);

private:
    sf::Clock clock;
    sf::Time deltaTime;
    Window* m_window;
    EngineUtilities::TSharedPointer<Actor> Triangle;
    EngineUtilities::TSharedPointer<Actor> Circle;

    // Variables para waypoints
    std::vector<sf::Vector2f> waypoints;  // Puntos de referencia
    size_t currentWaypointIndex = 0;      // Índice del waypoint actual
};
