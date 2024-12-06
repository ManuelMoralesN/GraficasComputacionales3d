#pragma once
#include "Prerequisites.h"
#include "Component.h"

/**
 * @class Texture
 * @brief Componente que representa una textura en el sistema de componentes.
 */
class 
Texture : public Component {
public:
    /**
     * @brief Constructor por defecto de la clase Texture.
     */
    Texture() = default;

    /**
     * @brief Constructor que inicializa la textura a partir del nombre de archivo y la extensión.
     * @param textureName Nombre del archivo de textura (sin extensión).
     * @param extension Extensión del archivo de textura.
     *
     * Intenta cargar la textura usando el nombre y la extensión proporcionados.
     * Si falla, intenta cargar una textura predeterminada ("Default.png").
     */
    Texture(std::string textureName, std::string extension)
        : m_textureName(textureName), m_extension(extension), Component(ComponentType::TEXTURE) {

        if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
            std::cout << "Error de carga de textura" << std::endl;

            // Cargar textura predeterminada si la original falla
            m_textureName = "Default";
            m_extension = "png";
            if (!m_texture.loadFromFile(m_textureName + "." + m_extension)) {
                std::cout << "Error de carga de textura" << std::endl;
            }
        }
    }

    /**
     * @brief Destructor de la clase Texture.
     */
    virtual ~Texture() = default;

    /**
     * @brief Devuelve una referencia a la textura de SFML.
     * @return Referencia a sf::Texture.
     */
    sf::Texture& getTexture() {
        return m_texture;
    }

    void update(float deltaTime) override {

    }
    void render(Window window) override {

    }

private:
    std::string m_textureName;  ///< Nombre del archivo de textura.
    std::string m_extension;    ///< Extensión del archivo de textura.
    sf::Texture m_texture;      ///< Objeto de textura de SFML.
};
