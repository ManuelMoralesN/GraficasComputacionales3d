#pragma once
#include "Prerequisites.h"

/**
 * @class Window
 * @brief Clase que gestiona una ventana de renderizado y la integración con ImGui.
 */
class 
Window {
public:
    /**
     * @brief Constructor por defecto de la clase Window.
     */
    Window() = default;

    /**
     * @brief Constructor que inicializa la ventana con dimensiones y título especificados.
     * @param width Ancho de la ventana.
     * @param height Alto de la ventana.
     * @param title Título de la ventana.
     */
    Window(int width, int height, const std::string& title);

    /**
     * @brief Destructor de la clase Window. Libera recursos de ImGui y cierra la ventana.
     */
    ~Window();

    /**
     * @brief Maneja los eventos de la ventana, como el cierre y redimensionamiento.
     */
    void 
    handleEvents();

    /**
     * @brief Limpia el contenido actual de la ventana y el RenderTexture.
     */
    void 
    clear();

    /**
     * @brief Muestra el contenido renderizado en la ventana.
     */
    void 
    display();

    /**
     * @brief Verifica si la ventana está abierta.
     * @return true si la ventana está abierta, false en caso contrario.
     */
    bool 
    isOpen() const;

    /**
     * @brief Dibuja un objeto en el RenderTexture en lugar de directamente en la ventana.
     * @param drawable Objeto dibujable a renderizar.
     */
    void 
    draw(const sf::Drawable& drawable);

    /**
     * @brief Obtiene un puntero a la ventana de renderizado.
     * @return Puntero a sf::RenderWindow.
     */
    sf::RenderWindow* getWindow();

    /**
     * @brief Actualiza la textura después de renderizar en ella.
     */
    void 
    renderToTexture();

    /**
     * @brief Muestra la textura renderizada en una ventana ImGui.
     */
    void 
    showInImGui();

    /**
     * @brief Inicializa recursos y configura la ventana.
     */
    void 
    init();

    /**
     * @brief Actualiza la GUI de ImGui y el deltaTime de la ventana.
     */
    void 
    update();

    /**
     * @brief Renderiza la GUI de ImGui en la ventana.
     */
    void 
    render();

    /**
     * @brief Libera los recursos y cierra la ventana.
     */
    void 
    destroy();

private:
    sf::RenderWindow* m_window; ///< Puntero a la ventana de SFML.
    sf::View m_view;            ///< Vista de la ventana para manejar el redimensionamiento.

public:
    sf::RenderTexture m_renderTexture; ///< Textura de renderizado de SFML.
    sf::Time deltaTime;                ///< Delta time para el cálculo de tiempo entre frames.
    sf::Clock clock;                   ///< Reloj para calcular el delta time.
};
