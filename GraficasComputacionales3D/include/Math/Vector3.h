#pragma once
#include "Utilities.h"

/**
 * @brief Clase que representa un vector 3D y proporciona varias operaciones aritméticas.
 */
class Vector3 {
public:
    float x; ///< Coordenada en el eje X
    float y; ///< Coordenada en el eje Y
    float z; ///< Coordenada en el eje Z

    /**
     * @brief Constructor por defecto que inicializa el vector a (0, 0, 0).
     */
    Vector3() : x(0), y(0), z(0) {};

    /**
     * @brief Constructor que inicializa el vector con los valores proporcionados.
     * @param xVal Valor inicial para la coordenada X.
     * @param yVal Valor inicial para la coordenada Y.
     * @param zVal Valor inicial para la coordenada Z.
     */
    Vector3(float xVal, float yVal, float zVal) : x(xVal), y(yVal), z(zVal) {}

    /**
     * @brief Sobrecarga del operador + para sumar dos vectores.
     * @param other El otro vector que se sumará al actual.
     * @return Un nuevo vector que es el resultado de la suma.
     */
    Vector3 operator+(const Vector3& other) const {
        return Vector3(x + other.x, y + other.y, z + other.z);
    }

    /**
     * @brief Sobrecarga del operador - para restar dos vectores.
     * @param other El otro vector que se restará al actual.
     * @return Un nuevo vector que es el resultado de la resta.
     */
    Vector3 operator-(const Vector3& other) const {
        return Vector3(x - other.x, y - other.y, z - other.z);
    }

    /**
     * @brief Sobrecarga del operador * para escalar el vector por un valor escalar.
     * @param scalar El valor escalar por el cual multiplicar el vector.
     * @return Un nuevo vector escalado.
     */
    Vector3 operator*(float scalar) const {
        return Vector3(x * scalar, y * scalar, z * scalar);
    }

    /**
     * @brief Calcula la magnitud (longitud) del vector.
     * @return La magnitud del vector.
     */
    float magnitude() const {
        return Vsqrt(x * x + y * y + z * z);
    }

    /**
     * @brief Normaliza el vector, devolviendo un vector unitario.
     * @return Un nuevo vector normalizado.
     */
    Vector3 normalize() const {
        float mag = magnitude();
        if (mag == 0) {
            return Vector3(0, 0, 0); // Devuelve un vector nulo si la magnitud es 0.
        }
        return Vector3(x / mag, y / mag, z / mag);
    }

    /**
     * @brief Devuelve un puntero a los datos del vector.
     * @return Puntero al primer elemento del vector.
     */
    float* 
    data() {
        return &x;
    }

    /**
     * @brief Devuelve un puntero constante a los datos del vector.
     * @return Puntero constante al primer elemento del vector.
     */
    const float* 
    data() const {
        return &x;
    }

private:
    // No se utilizan variables privadas en esta clase.
};
