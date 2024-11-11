#pragma once
#include "Prerequisites.h"

/**
 * @class NotificationService
 * @brief Servicio de notificación para manejar mensajes y notificaciones de consola.
 *
 * Esta clase utiliza el patrón Singleton para asegurar que solo exista una instancia de NotificationService.
 */
class 
NotificationService {
private:
    /**
     * @brief Constructor privado para evitar instancias múltiples.
     */
    NotificationService() {}

    // Eliminar el operador de copia y asignación para prevenir duplicaciones
    NotificationService(const NotificationService&) = delete;
    NotificationService& operator=(const NotificationService&) = delete;

public:
    /**
     * @brief Obtiene la única instancia de NotificationService.
     * @return Referencia a la instancia de NotificationService.
     */
    static NotificationService& getInstance() {
        static NotificationService instance;
        return instance;
    }

    /**
     * @brief Agrega un mensaje a la lista de mensajes según el tipo de error especificado.
     * @param code Código del tipo de error.
     * @param message Mensaje a agregar.
     */
    void 
    addMessage(ConsolErrorType code, const std::string& message) {
        m_programMessages[code].push_back(message);
    }

    /**
     * @brief Agrega un mensaje informativo.
     * @param message Mensaje informativo a agregar.
     */
    void 
    Log(const std::string& message) {
        ConsolErrorType code = ConsolErrorType::INFO;
        m_programMessages[code].push_back(message);
    }

    /**
     * @brief Obtiene todos los mensajes de un tipo de error específico.
     * @param code Código del tipo de error.
     * @return Cadena que contiene todos los mensajes del tipo especificado, separados por saltos de línea.
     */
    std::string getMessage(ConsolErrorType code) const {
        auto it = m_programMessages.find(code);
        if (it != m_programMessages.end()) {
            std::string combinedMessages;
            for (const auto& message : it->second) {
                combinedMessages += message + "\n";
            }
            return combinedMessages;
        }
        else {
            return "Message not found";
        }
    }

    /**
     * @brief Muestra todos los mensajes en la consola, organizados por tipo de error.
     */
    void 
    showAllMessages() const {
        for (const auto& pair : m_programMessages) {
            std::cout << "Code: " << pair.first << " - Messages: " << std::endl;
            for (const auto& message : pair.second) {
                std::cout << "   " << message << std::endl;
            }
        }
    }

    /**
     * @brief Guarda todos los mensajes en un archivo.
     * @param filename Nombre del archivo en el que se guardarán los mensajes.
     */
    void 
    saveMessagesToFile(const std::string& filename) const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "No se pudo abrir el archivo para guardar los mensajes." << std::endl;
            return;
        }

        for (const auto& pair : m_programMessages) {
            file << "Code: " << pair.first << " - Messages: " << std::endl;
            for (const auto& message : pair.second) {
                file << "   " << message << "\n";
            }
        }

        file.close();
        std::cout << "Mensajes guardados en el archivo: " << filename << std::endl;
    }

    /**
     * @brief Obtiene el mapa completo de notificaciones.
     * @return Mapa que contiene los mensajes clasificados por tipo de error.
     */
    std::map<ConsolErrorType, std::vector<std::string>>& getNotifications() {
        return m_programMessages;
    }

private:
    std::map<ConsolErrorType, std::vector<std::string>> m_programMessages; ///< Mapa para almacenar mensajes según su tipo.
};
