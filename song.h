#ifndef SONG_H
#define SONG_H

#include <string>

class song
{
public:
    song(std::string a_id, std::string a_artist, std::string a_song_name, std::string a_in, std::string a_link, int a_time);
    std::string getId();
    std::string getArtist();
    std::string getSongName();
    std::string getIn();
    std::string getLink();
    int getTime();

private:
    std::string id;
    std::string artist;
    std::string song_name;
    std::string in;
    std::string link;
    int time;
};

#endif // SONG_H
