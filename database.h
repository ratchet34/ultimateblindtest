#ifndef DATABASE_H
#define DATABASE_H

#include <string>
#include <vector>

#include <QStandardItemModel>

std::string getFieldFromId(std::string field, std::string id);
std::string getGlobalRandomId();
std::string getCatRandomId(std::string cat);
std::vector<std::string> getAllCat();
std::string getCatTable(std::string catName);
std::tuple<std::string, int> getRandomTupleCat();
int getCountRandomCat(std::string id);
void setAllUndone();
void updateSong(std::string id, std::string artist, std::string song_name, std::string in, std::string link, std::string time);
void setSongRunning(std::string status);
void setNotFoundAll();
/*void checkAnswers(std::string artist, std::string song, std::string in);*/
std::string getPlayerStatus();



#endif // DATABASE_H
