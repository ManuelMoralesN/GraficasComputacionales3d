#pragma once
#include "Prerequisites.h"
#include "Component.h"
#include "Window.h"

/**
 * @class ShapeFactory
 * @brief Clase que maneja la creación y control de formas geométricas.
 */
class ShapeFactory : public Component
{
public:
    /**
     * @brief Constructor por defecto.
     */
    ShapeFactory() = default;

    /**
     * @brief Destructor por defecto.
     */
    virtual ~ShapeFactory() = default;

    /**
     * @brief Constructor que inicializa la forma con un tipo específico.
     * @param shapeType Tipo de la forma a crear.
     */
    ShapeFactory(ShapeType shapeType) : m_shape(nullptr), m_shapeType(ShapeType::EMPTY), Component(ComponentType::SHAPE) {}

    /**
     * @brief Crea una forma del tipo especificado.
     * @param shapeType Tipo de la forma a crear (Círculo, Rectángulo, etc.).
     * @return Puntero a la forma creada.
     */
    sf::Shape* createShape(ShapeType shapeType);

    /**
     * @brief Actualiza la forma en cada frame (no implementado actualmente).
     * @param deltaTime Tiempo transcurrido desde el último frame.
     */
    void update(float deltaTime) override {}

    /**
     * @brief Renderiza la forma en la ventana proporcionada (no implementado actualmente).
     * @param window Ventana en la que se debe renderizar la forma.
     */
    void render(Window window) override {}

    /**
     * @brief Obtiene la forma actual.
     * @return Puntero a la forma.
     */
    sf::Shape* getShape() {
        return m_shape;
    }

    /**
     * @brief Establece la posición de la forma.
     * @param x Coordenada X.
     * @param y Coordenada Y.
     */
    void setPosition(float x, float y);

    /**
     * @brief Establece la posición de la forma.
     * @param position Vector con las coordenadas.
     */
    void setPosition(const Vector2& position);

    /**
     * @brief Establece el color de relleno de la forma.
     * @param color Color a aplicar a la forma.
     */
    void setFillColor(const sf::Color& color);

    /**
     * @brief Mueve la forma hacia una posición objetivo usando una velocidad y rango.
     * @param targetPosition Posición objetivo a la que moverse.
     * @param speed Velocidad a la que se mueve la forma.
     * @param deltaTime Tiempo transcurrido desde el último frame.
     * @param range Distancia mínima a la que se considera que ha llegado al objetivo.
     */
    //void Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range);

    void
    setRotation(float angle);

    void
    setScale(const Vector2& scl);

private:
    sf::Shape* m_shape;
    ShapeType m_shapeType;
};
