#ifndef SONG_H
#define SONG_H

#include <string>

class Song {
private:
    std::string trackId;
    std::string artistName;
    std::string trackName;
    std::string genre;
    int year;
    int popularity;
    int duration;

public:
    Song(const std::string& id, const std::string& artist, const std::string& track,
         const std::string& genre, int year, int popularity, int duration)
        : trackId(id), artistName(artist), trackName(track), genre(genre),
          year(year), popularity(popularity), duration(duration) {}

    const std::string& getTrackId() const { return trackId; }
    const std::string& getArtistName() const { return artistName; }
    const std::string& getTrackName() const { return trackName; }
    const std::string& getGenre() const { return genre; }
    int getYear() const { return year; }
    int getPopularity() const { return popularity; }
    int getDuration() const { return duration; }
};

#endif

