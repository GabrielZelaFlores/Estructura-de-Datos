#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <list>
#include "Song.h"

class HashTable {
private:
    static const int TABLE_SIZE = 10007;
    std::vector<std::list<Song>> table;

    int hash(int year) const {
        return year % TABLE_SIZE;
    }

public:
    HashTable() : table(TABLE_SIZE) {}

    void insert(const Song& song) {
        int index = hash(song.getYear());
        table[index].push_back(song);
    }

    bool remove(int year, const std::string& trackId) {
        int index = hash(year);
        auto& bucket = table[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->getTrackId() == trackId) {
                bucket.erase(it);
                return true;
            }
        }
        return false;
    }

    std::list<Song> find(int year) {
        int index = hash(year);
        std::list<Song> results;
        for (const auto& song : table[index]) {
            if (song.getYear() == year) {
                results.push_back(song);
            }
        }
        return results;
    }

    void displayByYear(int year) {
        std::list<Song> results = find(year);
        if (results.empty()) {
            std::cout << "No se encontraron canciones para el año: " << year << std::endl;
        } else {
            std::cout << "Canciones encontradas para el año " << year << ":" << std::endl;
            for (const auto& song : results) {
                std::cout << " - " << song.getTrackName() << " de " << song.getArtistName() << std::endl;
            }
        }
    }
};

#endif

