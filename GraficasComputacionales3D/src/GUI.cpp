#include "GUI.h"
#include "Window.h"
#include "Actor.h"
#include "imgui_internal.h"

/**
 * @brief Inicializa la interfaz gráfica (GUI), configurando su estilo visual.
 */
void 
GUI::init() {
    setupGUIStyle();
}

/**
 * @brief Actualiza el estado de la GUI. Actualmente, este método está vacío y no realiza ninguna acción.
 */
void 
GUI::update() {
}

/**
 * @brief Renderiza la GUI. Actualmente, este método está vacío y no realiza ninguna acción.
 */
void 
GUI::render() {
}

/**
 * @brief Libera recursos de la GUI. Actualmente, este método está vacío y no realiza ninguna acción.
 */
void 
GUI::destroy() {
}

/**
 * @brief Configura el estilo visual de la GUI utilizando colores y bordes personalizados.
 */
void 
GUI::setupGUIStyle() {
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;

    // Configuración de colores
    colors[ImGuiCol_WindowBg] = ImVec4(0.05f, 0.05f, 0.05f, 1.00f);  // Fondo oscuro
    colors[ImGuiCol_Text] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);      // Texto principal blanco
    colors[ImGuiCol_TextDisabled] = ImVec4(0.50f, 0.50f, 0.50f, 1.00f); // Texto deshabilitado gris

    // Colores de acento para botones y encabezados
    colors[ImGuiCol_Header] = ImVec4(1.00f, 0.0f, 0.0f, 1.00f);        // Rojo para resaltar
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.0f, 1.0f, 0.0f, 1.00f);  // Verde brillante
    colors[ImGuiCol_HeaderActive] = ImVec4(1.0f, 1.0f, 0.0f, 1.00f);   // Amarillo para selección
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);      // Botón gris oscuro
    colors[ImGuiCol_ButtonHovered] = ImVec4(1.00f, 0.65f, 0.0f, 1.00f); // Hover naranja
    colors[ImGuiCol_ButtonActive] = ImVec4(0.85f, 0.85f, 0.0f, 1.00f);  // Botón activo amarillo

    // Otros ajustes de estilo
    style.WindowRounding = 0.0f;    // Sin redondeo
    style.FrameRounding = 0.0f;
    style.ScrollbarRounding = 0.0f;
    style.GrabRounding = 0.0f;
    style.FrameBorderSize = 1.0f;
    style.WindowBorderSize = 1.0f;
    style.PopupBorderSize = 1.0f;

    // Escalado
    style.ScaleAllSizes(1.5f);
}

/**
 * @brief Muestra una lista de actores en forma de jerarquía, similar a Unity, permitiendo su selección.
 * @param actors Vector de actores a mostrar en la jerarquía.
 * @param selectedActorIndex Índice del actor seleccionado.
 */
void 
GUI::OutLiner(const std::vector<EngineUtilities::TSharedPointer<Actor>>& actors, int& selectedActorIndex) {
    ImGui::Begin("Outliner");

    for (int i = 0; i < actors.size(); ++i) {
        if (!actors[i].isNull()) {
            bool node_open = ImGui::TreeNodeEx(actors[i]->getName().c_str(),
                ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_SpanAvailWidth |
                (i == selectedActorIndex ? ImGuiTreeNodeFlags_Selected : 0));

            if (ImGui::IsItemClicked()) {
                selectedActorIndex = i;
            }

            if (node_open) {
                ImGui::TreePop();
            }
        }
    }

    ImGui::End();
}

/**
 * @brief Muestra una consola de mensajes filtrable, con colores según el tipo de mensaje.
 * @param programMessages Mapa de tipos de mensajes y sus respectivos textos.
 */
void 
GUI::console(std::map<ConsolErrorType, std::vector<std::string>>& programMessages) {
    ImGui::Begin("Console");

    static ImGuiTextFilter filter;
    filter.Draw("Filter (\"error\", \"warning\", etc.)", 180.0f);

    ImGui::Separator();
    ImGui::BeginChild("ScrollingRegion", ImVec2(0, 0), false, ImGuiWindowFlags_HorizontalScrollbar);

    for (const auto& pair : programMessages) {
        ImVec4 color;
        switch (pair.first) {
        case ConsolErrorType::ERROR:
            color = ImVec4(1.0f, 0.4f, 0.4f, 1.0f);
            break;
        case ConsolErrorType::WARNING:
            color = ImVec4(1.0f, 1.0f, 0.4f, 1.0f);
            break;
        case ConsolErrorType::INFO:
        default:
            color = ImVec4(0.8f, 0.8f, 0.8f, 1.0f);
            break;
        }

        for (const auto& message : pair.second) {
            if (!filter.PassFilter(message.c_str())) continue;

            ImGui::PushStyleColor(ImGuiCol_Text, color);
            ImGui::Text("[%d] %s", pair.first, message.c_str());
            ImGui::PopStyleColor();
        }
    }

    if (ImGui::GetScrollY() >= ImGui::GetScrollMaxY())
        ImGui::SetScrollHereY(1.0f);

    ImGui::EndChild();
    ImGui::End();
}

void 
GUI::vec3Control(const std::string& label, float* values, float resetValue, float columnWidth) {
    ImGuiIO& io = ImGui::GetIO();
    auto boldFont = io.Fonts->Fonts[0];

    ImGui::PushID(label.c_str());

    ImGui::Columns(2);
    ImGui::SetColumnWidth(0, columnWidth);
    ImGui::Text(label.c_str());
    ImGui::NextColumn();

    ImGui::PushMultiItemsWidths(3, ImGui::CalcItemWidth());
    ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2{ 0, 0 });

    float lineHeight = GImGui->Font->FontSize + GImGui->Style.FramePadding.y * 2.0f;
    ImVec2 buttonSize = { lineHeight + 3.0f, lineHeight };

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.9f, 0.2f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.8f, 0.1f, 0.15f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("X", buttonSize)) values[0] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##X", &values[0], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4{ 0.3f, 0.8f, 0.3f, 1.0f });
    ImGui::PushStyleColor(ImGuiCol_ButtonActive, ImVec4{ 0.2f, 0.7f, 0.2f, 1.0f });
    ImGui::PushFont(boldFont);
    if (ImGui::Button("Y", buttonSize)) values[1] = resetValue;
    ImGui::PopFont();
    ImGui::PopStyleColor(3);

    ImGui::SameLine();
    ImGui::DragFloat("##Y", &values[1], 0.1f, 0.0f, 0.0f, "%.2f");
    ImGui::PopItemWidth();
    ImGui::SameLine();

    ImGui::PopStyleVar();
    ImGui::Columns(1);

    ImGui::PopID();
}

/**
 * @brief Muestra y permite editar propiedades de un actor seleccionado, como posición y escala.
 * @param selectedActor Actor seleccionado para inspección.
 */
void 
GUI::inspector(EngineUtilities::TSharedPointer<Actor> selectedActor) {
    if (selectedActor.isNull()) {
        return;
    }

    ImGui::Begin("Inspector");
    ImGui::Text("Actor: %s", selectedActor->getName().c_str());

    auto transform = selectedActor->getComponent<Transform>();
    if (!transform.isNull()) {
        Vector2 position = transform->getPosition();
        Vector2 scale = transform->getScale();
        Vector2 rotation = transform->getRotation();

        ImGui::Text("Position");
        if (ImGui::DragFloat2("##Position", &position.x, 0.1f)) {
            transform->setPosition(position);
        }

        ImGui::Text("Rotation"); 
        if (ImGui::DragFloat2("##Rotation", &rotation.x, 0.1f)) {
            transform->setRotation(rotation);
        }

        ImGui::Text("Scale");
        if (ImGui::DragFloat2("##Scale", &scale.x, 0.1f)) {
            transform->setScale(scale);
        }
    }

    ImGui::End();
}

/**
 * @brief Panel de creación de actores, permite configurar el nombre, tipo y color del actor.
 * @param actors Vector donde se almacenan los actores creados.
 */
void 
GUI::ActorCreationPanel(std::vector<EngineUtilities::TSharedPointer<Actor>>& actors) {
    ImGui::Begin("Actor Factory", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_AlwaysAutoResize);

    static char actorName[64] = "";
    static int selectedActorType = 0;
    const char* actorTypes[] = { "Track", "Circle", "Triangle" };

    ImGui::Text("Actor Factory");

    ImGui::InputText("##actorName", actorName, IM_ARRAYSIZE(actorName));
    ImGui::SameLine();
    ImGui::Text("Name");

    ImGui::Combo("##actorType", &selectedActorType, actorTypes, IM_ARRAYSIZE(actorTypes));
    ImGui::SameLine();
    ImGui::Text("Type");

    static int selectedColor = 0;
    ImGui::Text("Color:");
    ImGui::SameLine();
    if (ImGui::RadioButton("Red", selectedColor == 0)) selectedColor = 0;
    ImGui::SameLine();
    if (ImGui::RadioButton("Blue", selectedColor == 1)) selectedColor = 1;
    ImGui::SameLine();
    if (ImGui::RadioButton("Purple", selectedColor == 2)) selectedColor = 2;

    if (ImGui::Button("Create Actor", ImVec2(120, 0))) {
        auto newActor = EngineUtilities::MakeShared<Actor>(actorName);
        auto shapeFactory = newActor->getComponent<ShapeFactory>();
        if (shapeFactory) {
            if (actorTypes[selectedActorType] == std::string("Track")) {
                shapeFactory->createShape(ShapeType::RECTANGLE);
            }
            else if (actorTypes[selectedActorType] == std::string("Circle")) {
                shapeFactory->createShape(ShapeType::CIRCLE);
            }
            else if (actorTypes[selectedActorType] == std::string("Triangle")) {
                shapeFactory->createShape(ShapeType::TRIANGLE);
            }

            if (selectedColor == 0) {
                shapeFactory->getShape()->setFillColor(sf::Color::Red);
            }
            else if (selectedColor == 1) {
                shapeFactory->getShape()->setFillColor(sf::Color::Blue);
            }
            else if (selectedColor == 2) {
                shapeFactory->getShape()->setFillColor(sf::Color(128, 0, 128));
            }
        }

        actors.push_back(newActor);
        strcpy(actorName, "");
    }

    ImGui::End();
}
