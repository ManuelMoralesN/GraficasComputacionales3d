#pragma once

// Librerías estándar
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <thread>

// Librerías de terceros
#include <SFML/Graphics.hpp>
#include "Memory/TSharedPointer.h"
#include "Memory/TWeakPointer.h"
#include "Memory/TStaticPtr.h"
#include "Memory/TUniquePtr.h"

// Enumeración para tipos de forma
enum ShapeType
{
    EMPTY = 0,
    CIRCLE = 1,
    RECTANGLE = 2,
    TRIANGLE = 3
};

// Macro para liberar punteros de forma segura
#define SAFE_PTR_RELEASE(x) if(x != nullptr) { delete x; x = nullptr; }

// Macro para mensajes de creación de recursos
#define MESSAGE(classObj, method, state)                        \
{                                                               \
    std::ostringstream os_;                                     \
    os_ << classObj << "::" << method << " : "                  \
        << "[CREATION OF RESOURCE]" << " : " << state << " ]\n"; \
    std::cerr << os_.str();                                      \
}

// Macro para manejo de errores y cierre de programa
#define ERROR(classObj, method, errorMSG)                        \
{                                                                 \
    std::ostringstream os_;                                        \
    os_ << "ERROR : " << classObj << "::" << method << " : "        \
        << " Error in data from params [" << errorMSG << "]\n";     \
    std::cerr << os_.str();                                         \
    exit(1);                                                        \
}
