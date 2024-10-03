#pragma once
#include "Prerequisites.h"
#include "Component.h"

class Window;

/**
 * @class Enity
 * @brief Representa una entidad en el juego, que puede tener varios componentes.
 */
class Enity
{
public:
    /**
     * @brief Destructor por defecto.
     */
    virtual ~Enity() = default;

    /**
     * @brief Actualiza la entidad. Este método se llama en cada frame.
     * @param deltaTime El tiempo que ha pasado desde el último frame.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Dibuja la entidad en la ventana.
     * @param window La ventana donde se dibuja.
     */
    virtual void render(Window& window) = 0;

    /**
     * @brief Agrega un componente a la entidad.
     * @tparam T El tipo del componente que se va a agregar. Debe ser derivado de la clase `Component`.
     * @param component El componente que se añade.
     */
    template<typename T>
    void addComponent(EngineUtilities::TSharedPointer<T> component)
    {
        static_assert(std::is_base_of<Component, T>::value, "T must be derived from Component");
        components.push_back(component.template dynamic_pointer_cast<Component>());
    }

    /**
     * @brief Obtiene un componente específico que tenga la entidad.
     * @tparam T El tipo del componente que se busca.
     * @return Devuelve el componente si se encuentra, o un puntero vacío si no lo tiene.
     */
    template<typename T>
    EngineUtilities::TSharedPointer<T> getComponent()
    {
        for (auto& component : components) {
            EngineUtilities::TSharedPointer<T> specificComponent = component.template dynamic_pointer_cast<T>();
            if (specificComponent) {
                return specificComponent;  // Retorna el componente si se encuentra
            }
        }
        return EngineUtilities::TSharedPointer<T>();  // Retorna un puntero vacío si no lo encuentra
    }

protected:
    bool isActive;  ///Indica si la entidad está activa o no.
    int id;  ///Identificador único de la entidad.

    // Lista de componentes que forman parte de la entidad
    std::vector<EngineUtilities::TSharedPointer<Component>> components;
};
