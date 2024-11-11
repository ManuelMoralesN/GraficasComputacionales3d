#include "Actor.h"
#include "Services/NotificationService.h"

/**
 * @brief Constructor de la clase Actor. Configura el nombre, los componentes básicos (ShapeFactory y Transform)
 *        y notifica la creación del actor.
 * @param actorName Nombre del actor.
 */
Actor::Actor(std::string actorName) {
    NotificationService& notifier = NotificationService::getInstance();

    // Configura el nombre del actor
    m_name = actorName;

    // Configura el componente de forma (ShapeFactory)
    EngineUtilities::TSharedPointer<ShapeFactory> shape = EngineUtilities::MakeShared<ShapeFactory>();
    addComponent(shape);

    // Configura el componente de transformación (Transform)
    EngineUtilities::TSharedPointer<Transform> transform = EngineUtilities::MakeShared<Transform>();
    addComponent(transform);

    // Notifica que el actor se creó correctamente
    notifier.Log("Actor named " + m_name + " was created.");
}

/**
 * @brief Actualiza el estado del actor, sincronizando la posición, rotación y escala del ShapeFactory
 *        con los valores de Transform.
 * @param deltaTime Tiempo transcurrido desde la última actualización.
 */
void 
Actor::update(float deltaTime) {
    auto transform = getComponent<Transform>();
    auto shape = getComponent<ShapeFactory>();

    if (transform && shape) {
        shape->setPosition(transform->getPosition());
        shape->setRotation(transform->getRotation().x);
        shape->setScale(transform->getScale());
    }
}

/**
 * @brief Renderiza el actor en la ventana proporcionada, dibujando su forma (ShapeFactory).
 * @param window Referencia a la ventana donde se renderiza el actor.
 */
void 
Actor::render(Window& window) {
    for (unsigned int i = 0; i < components.size(); i++) {
        if (components[i].dynamic_pointer_cast<ShapeFactory>()) {
            window.draw(*components[i].dynamic_pointer_cast<ShapeFactory>()->getShape());
        }
    }
}

/**
 * @brief Método para destruir el actor y liberar recursos. Actualmente, este método está vacío.
 */
void 
Actor::destroy() {
}
