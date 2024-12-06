#pragma once
#include "Utilities.h"

/**
 * @brief Clase que representa un vector 2D y proporciona varias operaciones aritméticas.
 */
class Vector2 {
public:
    float x; ///< Coordenada en el eje X
    float y; ///< Coordenada en el eje Y

    /**
     * @brief Constructor por defecto que inicializa el vector a (0, 0).
     */
    Vector2() : x(0), y(0) {};

    /**
     * @brief Constructor que inicializa el vector con los valores proporcionados.
     * @param xVal Valor inicial para la coordenada X.
     * @param yVal Valor inicial para la coordenada Y.
     */
    Vector2(float xVal, float yVal) : x(xVal), y(yVal) {}

    /**
     * @brief Destructor por defecto. No se necesita liberar recursos.
     */
    ~Vector2() = default;

    /**
     * @brief Sobrecarga del operador + para sumar dos vectores.
     * @param other El otro vector que se sumará al actual.
     * @return Un nuevo vector que es el resultado de la suma.
     */
    Vector2 operator+(const Vector2& other) const {
        float new_xVal = x + other.x;
        float new_yVal = y + other.y;
        return Vector2(new_xVal, new_yVal);
    }

    /**
     * @brief Sobrecarga del operador - para restar dos vectores.
     * @param other El otro vector que se restará al actual.
     * @return Un nuevo vector que es el resultado de la resta.
     */
    Vector2 operator-(const Vector2& other) const {
        float new_xVal = x - other.x;
        float new_yVal = y - other.y;
        return Vector2(new_xVal, new_yVal);
    }

    /**
     * @brief Sobrecarga del operador * para escalar el vector por un valor escalar.
     * @param scalar El valor escalar por el cual multiplicar el vector.
     * @return Un nuevo vector escalado.
     */
    Vector2 operator*(float scalar) const {
        return Vector2(x * scalar, y * scalar);
    }

    /**
     * @brief Calcula la magnitud (longitud) del vector.
     * @return La magnitud del vector.
     */
    float 
    magnitude() const {
        return Vsqrt(x * x + y * y);
    }

    // Sobrecarga del operador +=
    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Sobrecarga del operador /=
    Vector2
        operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this;
    }


    /**
     * @brief Normaliza el vector, devolviendo un vector unitario.
     * @return Un nuevo vector normalizado.
     */
    Vector2 normalize() const {
        float mag = magnitude();
        if (mag == 0) {
            return Vector2(0, 0); // Devuelve un vector nulo si la magnitud es 0.
        }
        return Vector2(x / mag, y / mag);
    }

    /**
     * @brief Devuelve un puntero a los datos del vector.
     * @return Puntero al primer elemento del vector.
     */
    float* data() {
        return &x;
    }

    /**
     * @brief Devuelve un puntero constante a los datos del vector.
     * @return Puntero constante al primer elemento del vector.
     */
    const float* data() const {
        return &x;
    }

private:
    // No se utilizan variables privadas en esta clase.
};
