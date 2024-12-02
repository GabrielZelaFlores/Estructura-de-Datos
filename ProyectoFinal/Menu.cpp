#include <cstring>
#include "Menu.h"
#include "imgui.h"
#include <algorithm>
void menuImGui(DoublyLinkedList& list, HashTable& hashTable, AVLTree& avlTree, const DoublyLinkedList& mainList) {
    static int currentOption = 0; // Opción seleccionada
    static char idBuffer[256] = "";
    static char artistBuffer[256] = "";
    static char trackBuffer[256] = "";
    static char genreBuffer[256] = "";
    static int year = 0;
    static int popularity = 0;
    static int duration = 0;
    static int currentPos = 0;
    static int newPos = 0;
    static char searchKeyword[256] = "";
    static int searchOption = 0;
    static std::vector<Playlist> playlists;
    static Playlist mainPlaylist("Principal", list, hashTable, avlTree);
    static Playlist* currentPlaylist = &mainPlaylist;

    // Gestión de listas de reproducción
    if (ImGui::Begin("Gestión de Listas de Reproducción")) {
        if (ImGui::Button("Lista Principal")) {
            currentPlaylist = &mainPlaylist;
        }

        static char newListName[256] = "";
        ImGui::InputText("Nombre de la Nueva Lista", newListName, IM_ARRAYSIZE(newListName));
        if (ImGui::Button("Crear Nueva Lista")) {
            std::string listName(newListName);
            playlists.emplace_back(listName);
            std::cout << "Nueva lista de reproducción \"" << listName << "\" creada.\n";
        }

        if (!playlists.empty()) {
            ImGui::Text("Listas Disponibles:");
            for (size_t i = 0; i < playlists.size(); ++i) {
                if (ImGui::Button(playlists[i].name.c_str())) {
                    currentPlaylist = &playlists[i];
                }
            }
        }
        ImGui::End();
    }

    // Mostrar canciones en la lista principal
    /*if (ImGui::Begin("Lista Principal")) {
        const auto& songs = mainList.toVector();
        if (songs.empty()) {
            ImGui::Text("No hay canciones en la lista principal.");
        } else {
            ImGui::Text("Canciones en la Lista Principal:");
            ImGui::Separator();

            for (const auto& song : songs) {
                ImGui::Text("%s - %s (Año: %d, Popularidad: %d, Duración: %d ms)",
                            song.getTrackName().c_str(),
                            song.getArtistName().c_str(),
                            song.getYear(),
                            song.getPopularity(),
                            song.getDuration());
            }
        }
        ImGui::End();
    }*/
    ImGui::Begin("Menú");
    if (ImGui::Button("Agregar canción")) currentOption = 1;
    if (ImGui::Button("Eliminar canción")) currentOption = 2;
    if (ImGui::Button("Cambiar orden de canciones")) currentOption = 3;
    if (ImGui::Button("Reproducción aleatoria")) currentOption = 4;
    if (ImGui::Button("Mostrar canciones ordenadas")) currentOption = 5;
    if (ImGui::Button("Buscar canciones")) currentOption = 6;

    ImGui::End();

    // Ejecutar lógica basada en la opción seleccionada
    switch (currentOption) {
        case 1: { // Agregar canción
            ImGui::Begin("Agregar Canción");
            ImGui::InputText("ID", idBuffer, IM_ARRAYSIZE(idBuffer));
            ImGui::InputText("Artista", artistBuffer, IM_ARRAYSIZE(artistBuffer));
            ImGui::InputText("Canción", trackBuffer, IM_ARRAYSIZE(trackBuffer));
            ImGui::InputText("Género", genreBuffer, IM_ARRAYSIZE(genreBuffer));
            ImGui::InputInt("Año", &year);
            ImGui::InputInt("Popularidad", &popularity);
            ImGui::InputInt("Duración (ms)", &duration);

            if (ImGui::Button("Agregar")) {
                if (std::strlen(idBuffer) > 0 && std::strlen(artistBuffer) > 0 && 
                    std::strlen(trackBuffer) > 0 && std::strlen(genreBuffer) > 0 &&
                    year > 0 && popularity > 0 && duration > 0) {
                    Song newSong(idBuffer, artistBuffer, trackBuffer, genreBuffer, year, popularity, duration);
                    list.addSong(newSong);
                    hashTable.insert(newSong);
                    avlTree.insert(newSong);
                    std::cout << "Canción agregada exitosamente.\n";
                } else {
                    std::cout << "Error: Datos incompletos o inválidos.\n";
                }
                currentOption = 0; // Regresar al menú principal
            }
            ImGui::End();
            break;
        }
        case 2: { // Eliminar canción
            ImGui::Begin("Eliminar Canción");
            ImGui::InputText("ID", idBuffer, IM_ARRAYSIZE(idBuffer));

            if (ImGui::Button("Eliminar")) {
                deleteSongGlobal(list, hashTable, avlTree, idBuffer);
                currentOption = 0;
            }
            ImGui::End();
            break;
        }
        case 3: { // Cambiar orden
            ImGui::Begin("Cambiar Orden de Canciones");
            ImGui::InputInt("Posición Actual", &currentPos);
            ImGui::InputInt("Nueva Posición", &newPos);

            if (ImGui::Button("Cambiar")) {
                list.changeOrder(currentPos - 1, newPos - 1);
                std::cout << "Orden cambiado exitosamente.\n";
                currentOption = 0;
            }
            ImGui::End();
            break;
        }
        case 4: { // Reproducción aleatoria
            list.shuffle();
            std::cout << "Canciones barajadas aleatoriamente.\n";
            currentOption = 0;
            break;
        }
        case 5: { // Mostrar canciones ordenadas
            static int criteriaOption = 1;
            static int orderOption = 1;

            ImGui::Begin("Mostrar Canciones Ordenadas");
            ImGui::Text("Seleccione criterio:");
            ImGui::RadioButton("Original", &criteriaOption, 1);
            ImGui::RadioButton("Popularidad", &criteriaOption, 2);
            ImGui::RadioButton("Año", &criteriaOption, 3);
            ImGui::RadioButton("Duración", &criteriaOption, 4);
            ImGui::RadioButton("Género", &criteriaOption, 5);

            ImGui::Text("Seleccione orden:");
            ImGui::RadioButton("Ascendente", &orderOption, 1);
            ImGui::RadioButton("Descendente", &orderOption, 2);
            
            static char genreInput[256] = ""; // Buffer para género
            if (criteriaOption == 5) {       // Si se selecciona género
                ImGui::InputText("Ingrese Género", genreInput, IM_ARRAYSIZE(genreInput));
            }
            
            if (ImGui::Button("Mostrar")) {
                std::string criteria;
                switch (criteriaOption) {
                    case 1: criteria = "original"; break;
                    case 2: criteria = "popularidad"; break;
                    case 3: criteria = "año"; break;
                    case 4: criteria = "duracion"; break;
                    case 5: criteria = "genero"; break;
                }
                
            if (criteria == "genero" && std::strlen(genreInput) > 0) {
            // Filtrar manualmente las canciones por género
            std::vector<Song> filteredSongs = list.toVector();
            filteredSongs.erase(std::remove_if(filteredSongs.begin(), filteredSongs.end(),
                                               [&](const Song& song) { return song.getGenre() != genreInput; }),
                                filteredSongs.end());

            if (filteredSongs.empty()) {
                std::cout << "No se encontraron canciones del género \"" << genreInput << "\".\n";
            } else {
                std::cout << "Canciones del género \"" << genreInput << "\":\n";
                for (const auto& song : filteredSongs) {
                    std::cout << song.getTrackName() << " - " << song.getArtistName()
                              << " (Popularidad: " << song.getPopularity()
                              << ", Duración: " << song.getDuration() << " ms)\n";
                }
            }
        } else {
            displaySorted(list, criteria, orderOption == 1);
        }
                std::cout << "Resultados mostrados en consola.\n";
                currentOption = 0;
            }
            ImGui::End();
            break;
        }
        case 6: { // Buscar canciones
            ImGui::Begin("Buscar Canciones");
            ImGui::InputText("Palabra clave", searchKeyword, IM_ARRAYSIZE(searchKeyword));

            ImGui::Text("Seleccione criterio de búsqueda:");
            ImGui::RadioButton("Por Nombre", &searchOption, 1);
            ImGui::RadioButton("Por Año", &searchOption, 2);
            ImGui::RadioButton("Por Autor", &searchOption, 3);

            if (ImGui::Button("Buscar")) {
                if (searchOption == 1) {
                    avlTree.displaySearchResults(searchKeyword);
                } else if (searchOption == 2) {
                    int year = std::atoi(searchKeyword);
                    displaySongsByYear(hashTable, year);
                } else if (searchOption == 3) {
                    avlTree.searchByAuthor(searchKeyword);
                }
                std::cout << "Resultados mostrados en consola.\n";
                currentOption = 0;
            }
            ImGui::End();
            break;
        }
    }
}
