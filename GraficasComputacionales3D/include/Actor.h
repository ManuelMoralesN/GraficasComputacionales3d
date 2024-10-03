#pragma once
#include "Prerequisites.h"
#include "Enity.h"
#include "ShapeFactory.h"

class Actor : public Enity
{
public:

    /**
     * @brief Constructor por defecto de la clase Actor.
     * Crea un actor vacío con el nombre "Actor".
     */
    Actor() = default;

    /**
     * @brief Constructor que inicializa el actor con un nombre específico.
     * @param actorName Nombre del actor.
     */
    Actor(std::string actorName);

    /**
     * @brief Destructor por defecto.
     */
    virtual ~Actor() = default;

    /**
     * @brief Actualiza el estado del actor.
     * @param deltaTime Tiempo transcurrido desde la última actualización (en segundos).
     * Actualiza la lógica de los componentes del actor.
     */
    void update(float deltaTime) override;

    /**
     * @brief Renderiza el actor en la ventana proporcionada.
     * @param window Ventana en la que se debe renderizar el actor.
     */
    void render(Window& window) override;

    /**
     * @brief Destruye el actor y libera los recursos asociados.
     * Elimina todos los componentes del actor y limpia la memoria.
     */
    void destroy();

    /**
     * @brief Obtiene un componente específico del actor.
     * @tparam T Tipo de componente a obtener.
     * @return Devuelve un TSharedPointer del tipo solicitado si se encuentra el componente,
     * o un TSharedPointer vacío si no se encuentra.
     */
    template <typename T>
    EngineUtilities::TSharedPointer<T> getComponent();

private:
    std::string m_name = "Actor";  ///< Nombre del actor.
};

template<typename T>
inline EngineUtilities::TSharedPointer<T>
Actor::getComponent() {
    // Recorre la lista de componentes del actor para encontrar el solicitado
    for (auto& component : components) {
        // Intenta convertir el componente al tipo especificado T
        EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
        if (specificComponent) {
            return specificComponent;  // Retorna el componente si coincide con el tipo
        }
    }
    // Devuelve un TSharedPointer vacío si no se encuentra el componente
    return EngineUtilities::TSharedPointer<T>();
}
