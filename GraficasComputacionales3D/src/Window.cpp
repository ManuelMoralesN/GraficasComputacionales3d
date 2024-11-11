#include "Window.h"

/**
 * @brief Constructor de la clase Window. Crea una ventana y configura ImGui.
 * @param width Ancho de la ventana.
 * @param height Alto de la ventana.
 * @param title Título de la ventana.
 */
Window::Window(int width, int height, const std::string& title) {
    m_window = new sf::RenderWindow(sf::VideoMode(width, height), title);
    if (!m_window) {
        ERROR("Window", "Window", "CHECK CONSTRUCTOR");
        // NotificationService.instace.Notify(ConsolErrorType::ERROR, "Error initializing the window class, check for constructor");
    }
    else {
        MESSAGE("Window", "Window", "OK");
    }

    // Inicializa los recursos de ImGui para SFML
    ImGui::SFML::Init(*m_window);

    // Crear RenderTexture con las mismas dimensiones que la ventana
    if (!m_renderTexture.create(width, height)) {
        ERROR("Window", "RenderTexture", "CHECK CREATION");
    }
}

/**
 * @brief Destructor de la clase Window. Libera recursos de ImGui y elimina la ventana.
 */
Window::~Window() {
    ImGui::SFML::Shutdown();
    delete m_window;
}

/**
 * @brief Maneja los eventos de la ventana, incluyendo el cierre y el redimensionamiento.
 */
void 
Window::handleEvents() {
    sf::Event event;
    while (m_window->pollEvent(event)) {
        // Procesa los eventos de entrada en ImGui
        ImGui::SFML::ProcessEvent(event);
        switch (event.type) {
        case sf::Event::Closed:
            m_window->close();
            break;
        case sf::Event::Resized:
            unsigned int width = event.size.width;
            unsigned int height = event.size.height;

            m_view = m_window->getView();
            m_view.setSize(static_cast<float>(width), static_cast<float>(height));
            m_window->setView(m_view);

            m_renderTexture.create(width, height);
            break;
        }
    }
}

/**
 * @brief Limpia el contenido actual de la ventana y el RenderTexture.
 */
void 
Window::clear() {
    if (m_window != nullptr) {
        m_window->clear();
    }
    else {
        ERROR("Window", "clear", "CHECK FOR WINDOW POINTER DATA");
    }
    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.clear();
    }
}

/**
 * @brief Muestra el contenido renderizado en la ventana.
 */
void 
Window::display() {
    if (m_window != nullptr) {
        m_window->display();
    }
    else {
        ERROR("Window", "display", "CHECK FOR WINDOW POINTER DATA");
    }
}

/**
 * @brief Verifica si la ventana está abierta.
 * @return true si la ventana está abierta, false en caso contrario.
 */
bool 
Window::isOpen() const {
    if (m_window != nullptr) {
        return m_window->isOpen();
    }
    else {
        ERROR("Window", "isOpen", "CHECK FOR WINDOW POINTER DATA");
        return false;
    }
}

/**
 * @brief Dibuja un objeto en el RenderTexture en lugar de directamente en la ventana.
 * @param drawable Objeto dibujable a renderizar.
 */
void 
Window::draw(const sf::Drawable& drawable) {
    if (m_renderTexture.getSize().x > 0 && m_renderTexture.getSize().y > 0) {
        m_renderTexture.draw(drawable);
    }
}

/**
 * @brief Obtiene un puntero a la ventana de renderizado.
 * @return Puntero a sf::RenderWindow.
 */
sf::RenderWindow* Window::getWindow() {
    if (m_window != nullptr) {
        return m_window;
    }
    else {
        ERROR("Window", "getWindow", "CHECK FOR WINDOW POINTER DATA");
        return nullptr;
    }
}

/**
 * @brief Actualiza la textura después de renderizar en ella.
 */
void 
Window::renderToTexture() {
    m_renderTexture.display();
}

/**
 * @brief Muestra la textura renderizada en una ventana ImGui.
 */
void 
Window::showInImGui() {
    const sf::Texture& texture = m_renderTexture.getTexture();
    ImVec2 size(texture.getSize().x, texture.getSize().y);

    ImGui::Begin("Scene");
    ImGui::Image((void*)(intptr_t)texture.getNativeHandle(), size, ImVec2(0, 1), ImVec2(1, 0));
    ImGui::End();
}

/**
 * @brief Actualiza la GUI de ImGui y el deltaTime de la ventana.
 */
void 
Window::update() {
    deltaTime = clock.restart();
    ImGui::SFML::Update(*m_window, deltaTime);
}

/**
 * @brief Renderiza la GUI de ImGui en la ventana.
 */
void 
Window::render() {
    ImGui::SFML::Render(*m_window);
}

/**
 * @brief Libera los recursos y cierra la ventana.
 */
void 
Window::destroy() {
    ImGui::SFML::Shutdown();
    SAFE_PTR_RELEASE(m_window);
}
