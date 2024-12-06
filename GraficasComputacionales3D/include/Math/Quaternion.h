#pragma once

#include "Vector3.h"
#include "Utilities.h" 

class Quaternion {
public:
    float w; ///< Parte escalar del cuaternión.
    float x; ///< Parte vectorial en X del cuaternión.
    float y; ///< Parte vectorial en Y del cuaternión.
    float z; ///< Parte vectorial en Z del cuaternión.

    /**
     * @brief Constructor por defecto que inicializa los valores de w, x, y, z a 0.
     */
    Quaternion() : w(0), x(0), y(0), z(0) {}

    /**
     * @brief Constructor parametrizado que inicializa el cuaternión con los valores proporcionados.
     * @param w Valor de la parte escalar.
     * @param x Valor de la parte vectorial X.
     * @param y Valor de la parte vectorial Y.
     * @param z Valor de la parte vectorial Z.
     */
    Quaternion(float wVal, float xVal, float yVal, float zVal) : w(wVal), x(xVal), y(yVal), z(zVal) {}

    /**
     * @brief Constructor que inicializa un cuaternión a partir de un ángulo y un eje de rotación dado como Vector3.
     * @param axis Vector que define el eje de rotación (debe estar normalizado).
     * @param angle Ángulo de rotación en radianes.
     */
    Quaternion(const Vector3& axis, float angle) {
        float 
        halfAngle = angle * 0.5f;
        float 
        sinHalfAngle = Vsin(halfAngle);
        w = Vcos(halfAngle);
        x = axis.x * sinHalfAngle;
        y = axis.y * sinHalfAngle;
        z = axis.z * sinHalfAngle;
    }

    /**
     * @brief Sobrecarga del operador + para sumar dos cuaterniones.
     * @param other El cuaternión a sumar.
     * @return El cuaternión resultante.
     */
    Quaternion operator+(const Quaternion& other) const {
        return Quaternion(w + other.w, x + other.x, y + other.y, z + other.z);
    }

    /**
     * @brief Sobrecarga del operador * para multiplicar un cuaternión por un escalar.
     * @param scalar El valor escalar.
     * @return El cuaternión escalado.
     */
    Quaternion operator*(float scalar) const {
        return Quaternion(w * scalar, x * scalar, y * scalar, z * scalar);
    }

    /**
     * @brief Sobrecarga del operador * para multiplicar dos cuaterniones.
     * @param other El cuaternión a multiplicar.
     * @return El cuaternión resultante de la multiplicación.
     */
    Quaternion operator*(const Quaternion& other) const {
        return Quaternion(
            w * other.w - x * other.x - y * other.y - z * other.z,
            w * other.x + x * other.w + y * other.z - z * other.y,
            w * other.y - x * other.z + y * other.w + z * other.x,
            w * other.z + x * other.y - y * other.x + z * other.w
        );
    }

    /**
     * @brief Calcula la magnitud del cuaternión.
     * @return La magnitud del cuaternión.
     */
    float 
    magnitude() const {
        return Vsqrt(w * w + x * x + y * y + z * z);
    }

    /**
     * @brief Normaliza el cuaternión, devolviendo un cuaternión de magnitud 1.
     * @return El cuaternión normalizado.
     */
    Quaternion normalize() const {
        float 
        mag = magnitude();
        if (mag == 0) {
            return Quaternion(0, 0, 0, 0); // Devuelve un cuaternión nulo si la magnitud es 0.
        }
        return Quaternion(w / mag, x / mag, y / mag, z / mag);
    }

    /**
     * @brief Devuelve el conjugado del cuaternión.
     * @return El cuaternión conjugado.
     */
    Quaternion conjugate() const {
        return Quaternion(w, -x, -y, -z);
    }

    /**
     * @brief Devuelve el cuaternión inverso.
     * @return El cuaternión inverso.
     */
    Quaternion inverse() const {
        float 
        magSquared = w * w + x * x + y * y + z * z;
        if (magSquared == 0) {
            return Quaternion(0, 0, 0, 0); // Devuelve un cuaternión nulo si la magnitud es 0.
        }
        return conjugate() * (1.0f / magSquared);
    }

    /**
     * @brief Rota un vector 3D utilizando el cuaternión.
     * @param v El vector a rotar.
     * @return El vector rotado.
     */
    Vector3 rotate(const Vector3& v) const {
        Quaternion qv(0, v.x, v.y, v.z);
        Quaternion result = (*this) * qv * this->inverse();
        return Vector3(result.x, result.y, result.z);
    }

    /**
     * @brief Devuelve un puntero a los componentes del cuaternión.
     * @return Un puntero a los valores w, x, y, z.
     */
    float* 
    data() {
        return &w;
    }

    /**
     * @brief Devuelve un puntero constante a los componentes del cuaternión.
     * @return Un puntero constante a los valores w, x, y, z.
     */
    const 
    float* 
    data() const {
        return &w;
    }
};

