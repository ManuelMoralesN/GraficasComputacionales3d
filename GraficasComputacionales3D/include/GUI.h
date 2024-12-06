#pragma once
#include "Prerequisites.h"

class Window;
class Actor;

/**
 * @class GUI
 * @brief Clase encargada de manejar la interfaz gráfica de usuario.
 */
class GUI {
public:
    GUI() = default;
    ~GUI() = default;

    /**
     * @brief Inicializa la GUI y configura su estilo.
     */
    void 
    init();

    /**
     * @brief Actualiza el estado de la GUI.
     */
    void 
    update();

    /**
     * @brief Renderiza la GUI en pantalla.
     */
    void 
    render();

    /**
     * @brief Libera los recursos asociados con la GUI.
     */
    void 
    destroy();

    /**
     * @brief Configura el estilo visual de la GUI.
     */
    void 
    setupGUIStyle();

    /**
     * @brief Muestra una lista de actores en una ventana de jerarquía, permitiendo seleccionar uno.
     * @param actors Vector de punteros compartidos a actores.
     * @param selectedActorIndex Índice del actor seleccionado.
     */
    void 
    OutLiner(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors, int& selectedActorIndex);

    /**
     * @brief Muestra una consola con mensajes categorizados y filtrables.
     * @param programMessages Mapa de tipos de mensajes y sus respectivos textos.
     */
    void 
    console(std::map<ConsolErrorType, std::vector<std::string>>& programMessages);

    void
        vec3Control(const std::string& label,
            float* values,
            float resetValues = 0.0f,
            float columnWidth = 100.0f);

    /**
     * @brief Muestra y permite editar propiedades de un actor seleccionado.
     * @param selectedActor Puntero compartido al actor seleccionado.
     */
    void 
    inspector(EngineUtilities::TSharedPointer<Actor> selectedActor);

    /**
     * @brief Muestra un panel para crear actores, permitiendo configurar su nombre, tipo y color.
     * @param actors Vector donde se almacenan los actores creados.
     */
    void 
    ActorCreationPanel(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors);

private:
    // Miembros privados (actualmente no hay ninguno declarado).
};
