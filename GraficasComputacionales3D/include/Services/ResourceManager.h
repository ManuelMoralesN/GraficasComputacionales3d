#pragma once

#include "Prerequisites.h"
#include "Texture.h"

/**
 * @class ResourceManager
 * @brief Clase Singleton responsable de la gesti�n de recursos, espec�ficamente texturas.
 */
class 
    ResourceManager {
private:
    /**
     * @brief Constructor privado para implementar el patr�n Singleton.
     */
    ResourceManager() = default;

    /**
     * @brief Destructor privado para evitar la eliminaci�n directa del Singleton.
     */
    ~ResourceManager() = default;

    // Deshabilitar copiado y asignaci�n
    ResourceManager(const ResourceManager&) = delete;             ///< Deshabilitar constructor por copia.
    ResourceManager& operator=(const ResourceManager&) = delete;  ///< Deshabilitar asignaci�n.

public:
    /**
     * @brief Obtiene la instancia �nica de ResourceManager.
     * @return Referencia a la instancia �nica del ResourceManager.
     */
    static ResourceManager& getInstance() {
        static ResourceManager instance; ///< Instancia �nica del Singleton.
        return instance;
    }

    /**
     * @brief Carga una textura desde un archivo.
     * @param fileName Nombre del archivo de la textura.
     * @param extension Extensi�n del archivo (ejemplo: ".png").
     * @return `true` si la textura ya est� cargada o se carg� exitosamente, `false` en caso contrario.
     */
    bool 
    loadTexture(const std::string& fileName, const std::string& extension) {
        // Verificar si la textura ya est� cargada
        if (m_textures.find(fileName) != m_textures.end()) {
            return true; // Textura ya cargada
        }

        // Crear y cargar la textura
        EngineUtilities::TSharedPointer<Texture> texture = EngineUtilities::MakeShared<Texture>(fileName, extension);
        if (texture) {
            m_textures[fileName] = texture; // Almacenar la textura en el mapa
            return true;
        }

        std::cerr << "Failed to load texture: " << fileName << extension << std::endl;
        return false;
    }

    /**
     * @brief Obtiene una textura previamente cargada.
     * @param fileName Nombre del archivo de la textura.
     * @return Puntero compartido a la textura solicitada, o un puntero nulo si no se encuentra.
     */
    EngineUtilities::TSharedPointer<Texture> getTexture(const std::string& fileName) {
        // Buscar la textura en el mapa
        auto it = m_textures.find(fileName);
        if (it != m_textures.end()) {
            return it->second; // Devolver la textura si existe
        }

        std::cerr << "Texture not found: " << fileName << std::endl;
        return EngineUtilities::TSharedPointer<Texture>(); // Devolver puntero nulo
    }

private:
    /**
     * @brief Mapa que almacena las texturas cargadas, asociadas a sus nombres de archivo.
     */
    std::unordered_map<std::string, EngineUtilities::TSharedPointer<Texture>> m_textures;
};
