#include "song.h"
#include <string>

song::song(std::string a_id, std::string a_artist, std::string a_song_name, std::string a_in, std::string a_link, int a_time) :
    id(a_id),
    artist(a_artist),
    song_name(a_song_name),
    in(a_in),
    link(a_link),
    time(a_time)
{

}

std::string song::getId()
{
    return id;
}
std::string song::getArtist()
{
    return artist;
}
std::string song::getSongName()
{
    return song_name;
}
std::string song::getIn()
{
    return in;
}
std::string song::getLink()
{
    return link;
}
int song::getTime()
{
    return time;
}
