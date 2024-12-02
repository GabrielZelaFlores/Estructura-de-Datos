#include "Menu.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cstring>

GLFWwindow* setupWindow() {
    if (!glfwInit()) {
        std::cerr << "Error al inicializar GLFW.\n";
        return nullptr;
    }
    GLFWwindow* window = glfwCreateWindow(1280, 720, "Gestión de Listas de Reproducción", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        std::cerr << "Error al crear la ventana.\n";
        return nullptr;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    return window;
}

int main() {
    DoublyLinkedList mainList;
    HashTable mainHashTable;
    AVLTree mainAVLTree;
    std::vector<Playlist> playlists;

    // Inicializar ventana e ImGui
    GLFWwindow* window = setupWindow();
    if (!window) return -1;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");

    // Cargar canciones desde CSV
    loadSongsFromCSV("spotify_data.csv", mainList, mainHashTable, mainAVLTree);

    // Añadir la lista principal
    playlists.emplace_back("Lista Principal", mainList, mainHashTable, mainAVLTree);

    // Variables para el menú principal
    static char newListName[256] = "";
    static int selectedPlaylist = 0; // Por defecto, lista principal seleccionada
    static bool showMenuWindow = false; // Control para mostrar el menú de la lista seleccionada

    // Bucle principal
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Mostrar menú principal
        ImGui::Begin("Gestión de Listas de Reproducción");

        ImGui::Text("Listas de Reproducción:");
        for (size_t i = 0; i < playlists.size(); ++i) {
            if (ImGui::Selectable(playlists[i].name.c_str(), selectedPlaylist == static_cast<int>(i))) {
                selectedPlaylist = static_cast<int>(i);
            }
        }

        ImGui::Separator();

        ImGui::Text("Crear Nueva Lista:");
        ImGui::InputText("Nombre", newListName, IM_ARRAYSIZE(newListName));
        if (ImGui::Button("Crear Lista")) {
            if (strlen(newListName) > 0) {
                playlists.emplace_back(newListName);
                std::cout << "Nueva lista de reproducción \"" << newListName << "\" creada.\n";
                memset(newListName, 0, sizeof(newListName)); // Limpiar el buffer
            } else {
                std::cout << "Error: el nombre de la lista está vacío.\n";
            }
        }

        ImGui::Separator();
        ImGui::Text("Seleccione una lista para interactuar:");

        if (ImGui::Button("Abrir Menú de Lista Seleccionada")) {
            showMenuWindow = true; // Activar la ventana del menú
        }

        ImGui::End();

        // Mostrar menú específico para la lista seleccionada
        if (showMenuWindow) {
            ImGui::Begin(playlists[selectedPlaylist].name.c_str(), &showMenuWindow);

            // Llama a menuImGui para manejar las opciones de la lista seleccionada
            menuImGui(playlists[selectedPlaylist].list, playlists[selectedPlaylist].hashTable,
                      playlists[selectedPlaylist].avlTree, mainList);

            ImGui::End();
        }

        // Renderizar ImGui
        ImGui::Render();
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);
        glClearColor(0.45f, 0.55f, 0.60f, 1.00f);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // Limpiar ImGui y GLFW
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
