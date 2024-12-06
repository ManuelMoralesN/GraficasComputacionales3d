#pragma once

/**
 * @brief Función para calcular la raíz cuadrada de un valor positivo utilizando el método de aproximación de Newton.
 *
 * @param value Valor flotante cuyo valor de raíz cuadrada se desea calcular.
 * @return float Raíz cuadrada aproximada del valor. Si el valor es negativo, retorna 0.
 */
inline float Vsqrt(float value) {
    if (value < 0) {
        return 0;  // Si el valor es negativo, retorna 0.
    }

    float x = value;  // Valor inicial
    float y = 1.0f;   // Aproximación inicial
    float epsilon = 0.00001f;  // Precisión deseada para el cálculo

    // Aproximación de Newton-Raphson para encontrar la raíz cuadrada
    while (x - y > epsilon) {
        x = (x + y) / 2.0f;
        y = value / x;
    }

    return x;  // Retorna el valor aproximado de la raíz cuadrada
}

/**
 * @brief Función para calcular el seno de un ángulo en radianes utilizando una serie de Taylor.
 *
 * Esta función aproxima el valor de sin(x) mediante la serie de Taylor.
 *
 * @param angle Ángulo en radianes.
 * @return float Valor aproximado de sin(angle).
 */
inline float Vsin(float angle) {
    float result = 0.0f;  ///< Resultado de la serie de Taylor
    float term = angle;   ///< Primer término de la serie (igual al ángulo en radianes)
    float angle_squared = angle * angle;  ///< Ángulo al cuadrado, reutilizado en la serie
    int n = 1;  ///< Contador de términos de la serie

    // Continuar la serie mientras el término sea suficientemente grande
    while (term > 1e-6f || term < -1e-6f) {
        result += term;
        term *= -angle_squared / ((2 * n) * (2 * n + 1));
        ++n;
    }

    return result;
}

/**
 * @brief Función para calcular el coseno de un ángulo en radianes utilizando la identidad trigonométrica.
 *
 * Esta función calcula el coseno utilizando la relación cos(x) = sin(x + π/2).
 *
 * @param angle Ángulo en radianes.
 * @return float Valor aproximado de cos(angle).
 */
inline float Vcos(float angle) {
    const float PI = 3.14159265f;  ///< Valor aproximado de π.
    return Vsin(angle + PI / 2);    // Usa la identidad cos(x) = sin(x + π/2)
}
