#include "ShapeFactory.h"


/**
 * @brief Crea una forma espec�fica basada en el tipo de forma proporcionado.
 * @param shapeType Tipo de la forma a crear (CIRCLE, RECTANGLE, TRIANGLE, EMPTY).
 * @return Puntero a la forma creada de tipo sf::Shape. Devuelve nullptr si el tipo es EMPTY o inv�lido.
 */
sf::Shape* 
ShapeFactory::createShape(ShapeType shapeType) {
    m_shapeType = shapeType;
    switch (shapeType) {
    case EMPTY:
        return nullptr;
    case CIRCLE: {
        sf::CircleShape* circle = new sf::CircleShape(0.05);
        circle->setFillColor(sf::Color::White);
        m_shape = circle;
        return circle;
    }
    case RECTANGLE: {
        sf::RectangleShape* rectangle = new sf::RectangleShape (sf::Vector2f(100.0f, 50.0f));
        rectangle->setFillColor(sf::Color::White);
        m_shape = rectangle;
        return rectangle;
    }
    case TRIANGLE: {
        sf::CircleShape* triangle = new sf::CircleShape(50.0f, 3);
        triangle->setFillColor(sf::Color::White);
        m_shape = triangle;
        return triangle;
    }
    default:
        return nullptr;
    }
}

/**
 * @brief Establece la posici�n de la forma en coordenadas (x, y).
 * @param x Coordenada X.
 * @param y Coordenada Y.
 */
void 
ShapeFactory::setPosition(float x, float y) {
    if (m_shape) {
        m_shape->setPosition(x, y);
    }
}

/**
 * @brief Establece la posici�n de la forma con un vector de posici�n.
 * @param position Vector 2D de posici�n.
 */
void 
ShapeFactory::setPosition(const Vector2& position) {
    if (m_shape) {
        m_shape->setPosition(position.x, position.y);
    }
}

/**
 * @brief Establece la rotaci�n de la forma en grados.
 * @param angle �ngulo de rotaci�n en grados.
 */
void 
ShapeFactory::setRotation(float angle) {
    if (m_shape) {
        m_shape->setRotation(angle);
    }
}

/**
 * @brief Escala la forma de acuerdo a un vector de escala.
 * @param scl Vector 2D que representa la escala en los ejes X e Y.
 */
void 
ShapeFactory::setScale(const Vector2& scl) {
    if (m_shape) {
        m_shape->setScale(scl.x, scl.y);
    }
}

/**
 * @brief Establece el color de relleno de la forma.
 * @param color Color de relleno de tipo sf::Color.
 */
void 
ShapeFactory::setFillColor(const sf::Color& color) {
    if (m_shape) {
        m_shape->setFillColor(color);
    }
}

///*
//// Funci�n opcional para movimiento de b�squeda (Seek).
//// void ShapeFactory::Seek(const sf::Vector2f& targetPosition, float speed, float deltaTime, float range) {
////     sf::Vector2f shapePosition = m_shape->getPosition();
////     sf::Vector2f direction = targetPosition - shapePosition;
////     float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
////
////     if (length > range) {
////         direction /= length;
////         m_shape->move(direction * speed * deltaTime);
////     }
//// }
