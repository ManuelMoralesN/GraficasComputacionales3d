// Manuel Morales GC3D

#include "BaseApp.h"
#include "Services\NotificationService.h"

/**
 * @brief Ejecuta el ciclo principal de la aplicación.
 * Inicializa, maneja eventos, actualiza y renderiza la ventana.
 * @return Código de salida, 0 si fue exitoso.
 */
int selectedActorIndex = -1; // Índice del actor seleccionado


BaseApp::~BaseApp()
{
    NotificationService& notifier = NotificationService::getInstance();
    notifier.saveMessagesToFile("LogData.txt");
}

int 
BaseApp::run()
{
    NotificationService& notifier = NotificationService::getInstance();

    if (!initialize()) {
        notifier.addMessage(ConsolErrorType::ERROR, "Initializes result on a false statemente, check method validations");
        notifier.saveMessagesToFile("LogData.txt");
        ERROR("BaseApp", "run", "Initializes result on a false statemente, check method validations");
    }
    else {
        notifier.addMessage(ConsolErrorType::INFO, "All programs were initialized correctly");
    }

    m_GUI.init();
   
    while (m_window->isOpen())
    {
        m_window->handleEvents();
        //deltaTime = clock.restart();
        update();
        render();
    }

    cleanup();
    return 0;
}

/**
 * @brief Inicializa la ventana y los actores.
 * @return true si la inicialización fue exitosa, false en caso contrario.
 */
bool 
BaseApp::initialize()
{
    m_window = new Window(1920, 1080, "Graficas Computacionales 3D");
    if (!m_window)
    {
        MESSAGE("BaseApp", "initialize", "Error on window creation, vbar is null");
        return false;
    }

    // Track Actor
    Track = EngineUtilities::MakeShared<Actor>("Track");
    if (!Track.isNull()) {
        Track->getComponent<ShapeFactory>()->createShape(ShapeType::RECTANGLE);
        //Circle->getComponent<ShapeFactory>()->setFillColor(sf::Color::Blue);

        // Establecer posición, rotación y escala desde Transform
        Track->getComponent<Transform>()->setPosition(sf::Vector2f(0.0f, 0.0f));
        Track->getComponent<Transform>()->setRotation(sf::Vector2f(0.0f, 0.0f));
        Track->getComponent<Transform>()->setScale(sf::Vector2f(8.0f, 12.0f));

        if (!texture.loadFromFile("Circuit.png")) {
            std::cout << "Error de carga de textura" << std::endl;
            return -1; // Manejar error de carga
        }
        Track->getComponent<ShapeFactory>()->getShape()->setTexture(&texture);
    }
    m_actors.push_back(Track);

    // Inicializar el actor Circle
    Circle = EngineUtilities::MakeShared<Actor>("Circle");
    if (!Circle.isNull()) {
        Circle->getComponent<ShapeFactory>()->createShape(ShapeType::CIRCLE);

        Circle->getComponent<Transform>()->setPosition(sf::Vector2f(200.0f, 200.0f));
        Circle->getComponent<Transform>()->setScale(sf::Vector2f(1.0f, 1.0f));
        Circle->getComponent<Transform>()->setRotation(sf::Vector2f(200.0f, 200.0f));

        if (!Yoshi.loadFromFile("Yoshi.png")) {
            std::cout << "Error de carga de textura" << std::endl;
            return -1; // Manejar error de carga
        }
        Circle->getComponent<ShapeFactory>()->getShape()->setTexture(&Yoshi);
    }
    m_actors.push_back(Circle);
    // Definir los waypoints para el movimiento del círculo
    waypoints = {
    sf::Vector2f(420.0f, 40.0f),  // Primera curva en el norte
    sf::Vector2f(600.0f, 150.0f),  // Esquina noreste
    sf::Vector2f(780.0f, 300.0f),  // Esquina este
    sf::Vector2f(600.0f, 500.0f),  // Curva sureste
    sf::Vector2f(250.0f, 500.0f),  // Curva sur
    sf::Vector2f(100.0f, 450.0f),  // Curva suroeste
    sf::Vector2f(100.0f, 250.0f),  // Esquina noroeste
    sf::Vector2f(220.0f, 90.0f)   // De vuelta al inicio
    };

    currentWaypointIndex = 0; // Iniciar en el primer waypoint

    // Inicializar el actor Triangle
    Triangle = EngineUtilities::MakeShared<Actor>("Triangle");
    if (!Triangle.isNull()) {
        Triangle->getComponent<ShapeFactory>()->createShape(ShapeType::TRIANGLE);
    }
    m_actors.push_back(Triangle);
    return true;
}

/**
 * @brief Actualiza el estado del juego en cada frame.
 */
void 
BaseApp::update()
{
    m_window->update();

    sf::Vector2i mousePosition = sf::Mouse::getPosition(*m_window->getWindow());
    sf::Vector2f mousePosF(static_cast<float>(mousePosition.x), 
        static_cast<float>(mousePosition.y));
    //if (!Track.isNull()) {
    //    Track->update(m_window->deltaTime.asSeconds());
    //}
    //if (!Circle.isNull()) {
    //    Circle->update(m_window->deltaTime.asSeconds());
    //    updateMovement(m_window->deltaTime.asSeconds(), Circle); // Mover el círculo entre los waypoints
    //}
    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->update(m_window->deltaTime.asSeconds());
            if (actor->getName() == "Circle") {
                updateMovement(m_window->deltaTime.asSeconds(), actor);
            }
        }
    }
}

/**
 * @brief Renderiza los actores en la ventana.
 */
void BaseApp::render()
{
    NotificationService& notifier = NotificationService::getInstance();


    m_window->clear();
    for (auto& actor : m_actors) {
        if (!actor.isNull()) {
            actor->render(*m_window);
        }
    }
    /*if (!Track.isNull()) {
        Track->render(*m_window);
    }
    if (!Circle.isNull()) {
        Circle->render(*m_window);
    }
    if (Triangle.isNull()) {
        Triangle->render(*m_window);
    }*/

    m_window->renderToTexture();
    m_window->showInImGui();
    m_GUI.OutLiner(m_actors, selectedActorIndex);
    m_GUI.console(notifier.getNotifications());
    // Si hay un actor seleccionado, mostrar el inspector
    if (selectedActorIndex >= 0 && selectedActorIndex < m_actors.size()) {
        m_GUI.inspector(m_actors[selectedActorIndex]);
    }
    m_GUI.ActorCreationPanel(m_actors);
    m_window->render();
    m_window->display();
}

/**
 * @brief Limpia los recursos utilizados por la aplicación.
 */
void 
BaseApp::cleanup()
{
    m_window->destroy();
    delete m_window;
}

/**
 * @brief Actualiza el movimiento del círculo hacia el siguiente waypoint.
 * @param deltaTime El tiempo transcurrido entre frames.
 * @param circle El actor del círculo que se mueve entre los waypoints.
 */
void 
BaseApp::updateMovement(float deltaTime, EngineUtilities::TSharedPointer<Actor> circle)
{
    if (!circle || circle.isNull()) return;

    auto transform = circle->getComponent<Transform>();
    if (transform.isNull()) {
        return;
    }

    // Obtener el waypoint actual
    sf::Vector2f targetPos = waypoints[currentWaypointIndex];

    // Mover el círculo hacia el waypoint actual
    transform->Seek(targetPos, 200.0f, deltaTime, 10.0f);

    // Obtener la posición actual del círculo
    sf::Vector2f currentPos = circle->getComponent<Transform>()->getPosition();

    // Calcular la distancia al waypoint actual
    float distance = std::sqrt(std::pow(targetPos.x - currentPos.x, 2) + std::pow(targetPos.y - currentPos.y, 2));

    // Si el círculo está cerca del waypoint, avanzar al siguiente
    if (distance < 10.0f) {
        currentWaypointIndex = (currentWaypointIndex + 1) % waypoints.size(); // Ciclar a través de los waypoints
    }
}
