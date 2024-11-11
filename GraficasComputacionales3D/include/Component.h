#pragma once
class Window;

/**
 * @enum ComponentType
 * @brief Define los tipos de componentes que pueden ser asociados a una entidad.
 */
enum ComponentType {
    NONE = 0,
    TRANSFORM = 1,
    SPRITE = 2,
    RENDERER = 3,
    PHYSICS = 4,
    AUDIOSOURCE = 5,
    SHAPE = 6,
    TEXTURE = 7,
};

/**
 * @class Component
 * @brief Clase base para todos los componentes de una entidad.
 * Un componente representa una funcionalidad específica que puede ser añadida a una entidad.
 */
class Component
{
public:
    /**
     * @brief Constructor por defecto.
     */
    Component() = default;

    /**
     * @brief Constructor que inicializa el tipo del componente.
     * @param type Tipo del componente.
     */
    Component(const ComponentType type) : m_type(type) {}

    /**
     * @brief Destructor virtual por defecto.
     */
    virtual ~Component() = default;

    /**
     * @brief Actualiza el componente en cada frame.
     * @param deltaTime Tiempo transcurrido desde el último frame.
     */
    virtual void update(float deltaTime) = 0;

    /**
     * @brief Renderiza el componente.
     * @param window Ventana en la que se debe renderizar el componente.
     */
    virtual void render(Window window) = 0;

    /**
     * @brief Obtiene el tipo del componente.
     * @return Tipo de componente asociado.
     */
    ComponentType getType() const { return m_type; }

protected:
    ComponentType m_type; // Tipo de componente
};
