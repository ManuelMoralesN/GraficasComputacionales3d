// Manuel Morales GC3D

#include "BaseApp.h"

/**
 * @brief Ejecuta el ciclo principal de la aplicaci�n.
 * Inicializa, maneja eventos, actualiza y renderiza la ventana.
 * @return C�digo de salida, 0 si fue exitoso.
 */
int BaseApp::run()
{
    if (!initialize())
    {
        ERROR("BaseApp", "run", "initializes result on a false statement, check method validations");
    }

    initialize();
    while (m_window->isOpen())
    {
        m_window->handleEvents();
        deltaTime = clock.restart();
        update();
        render();
    }

    cleanup();
    return 0;
}

/**
 * @brief Inicializa la ventana y los actores.
 * @return true si la inicializaci�n fue exitosa, false en caso contrario.
 */
bool BaseApp::initialize()
{
    m_window = new Window(800, 600, "Graficas Computacionales 3D");
    if (!m_window)
    {
        MESSAGE("BaseApp", "initialize", "Error on window creation, vbar is null");
        return false;
    }

    // Inicializar el actor Circle
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);
        Circle->getComponent<ShapeFactory>()->setPosition(200.0f, 200.0f);
        Circle->getComponent<ShapeFactory>()->setFillColor(sf::Color::Blue);
    }

    // Definir los waypoints para el movimiento del c�rculo
    waypoints = {
        sf::Vector2f(100.0f, 100.0f),
        sf::Vector2f(400.0f, 100.0f),
        sf::Vector2f(400.0f, 400.0f),
        sf::Vector2f(100.0f, 400.0f),
        sf::Vector2f(250.0f, 250.0f)
    };

    currentWaypointIndex = 0; // Iniciar en el primer waypoint

    // Inicializar el actor Triangle
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
    }

    return true;
}

/**
 * @brief Actualiza el estado del juego en cada frame.
 */
void BaseApp::update()
{
    if (!Circle.isNull())
    {
        updateMovement(deltaTime.asSeconds(), Circle); // Mover el c�rculo entre los waypoints
    }
}

/**
 * @brief Renderiza los actores en la ventana.
 */
void BaseApp::render()
{
    m_window->clear();
    Circle->render(*m_window);
    Triangle->render(*m_window);
    m_window->display();
}

/**
 * @brief Limpia los recursos utilizados por la aplicaci�n.
 */
void BaseApp::cleanup()
{
    m_window->destroy();
    delete m_window;
}

/**
 * @brief Actualiza el movimiento del c�rculo hacia el siguiente waypoint.
 * @param deltaTime El tiempo transcurrido entre frames.
 * @param circle El actor del c�rculo que se mueve entre los waypoints.
 */
void BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle)
{
    // Obtener el waypoint actual
    sf::Vector2f target = waypoints[currentWaypointIndex];

    // Mover el c�rculo hacia el waypoint actual
    circle->getComponent<ShapeFactory>()->Seek(target, 200.0f, deltaTime, 10.0f);

    // Obtener la posici�n actual del c�rculo
    sf::Vector2f currentPos = circle->getComponent<ShapeFactory>()->getShape()->getPosition();

    // Calcular la distancia al waypoint actual
    float distance = std::sqrt(std::pow(target.x - currentPos.x, 2) + std::pow(target.y - currentPos.y, 2));

    // Si el c�rculo est� cerca del waypoint, avanzar al siguiente
    if (distance < 10.0f) {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size(); // Ciclar a trav�s de los waypoints
    }
}
