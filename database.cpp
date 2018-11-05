#include "headeronly_src/sqlite3pp.h"
#include "database.h"
#include <string.h>
#include <vector>

using namespace std;
#define DB_PATH         "data.sqlite"

string getFieldFromId(std::string field, std::string id)
{
    string out;
    try{
        sqlite3pp::database db(DB_PATH);

        std::string query ="select `"+field+"` from t_songs where id=\""+id+"\";";
        sqlite3pp::query qry(db, query.c_str());

        for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
            for (int j = 0; j < qry.column_count(); ++j) {
                out = (*i).get<char const*>(j);
            }
        }
    }
    catch (const std::exception& e) {
        out = "field_not_found";
    }
    return out;
}

string getGlobalRandomId()
{
    string out;
    sqlite3pp::database db(DB_PATH);

    std::string query ="select id from t_songs where not link=\"Empty\" and done=\"False\" order by random() limit 1";
    sqlite3pp::query qry(db, query.c_str());

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
        for (int j = 0; j < qry.column_count(); ++j) {
            out = (*i).get<char const*>(j);
        }
    }
    query = "update t_songs set done=\"True\" where id=\""+out+"\"";
    db.execute(query.c_str());
    return out;
}

int getCountRandomCat(std::string id)
{
    int count = 0;
    sqlite3pp::database db(DB_PATH);

    std::string query = "select count(*) from t_songs where id=\""+id+"\" and not link=\"Empty\" and done=\"False\"";
    sqlite3pp::query qry_count(db, query.c_str());
    for (sqlite3pp::query::iterator i = qry_count.begin(); i != qry_count.end(); ++i) {
        for (int j = 0; j < qry_count.column_count(); ++j) {
            count = atoi((*i).get<char const*>(j));
        }
    }

    return count;
}

std::tuple<std::string, int> getRandomTupleCat(std::string cat)
{
    string out;
    int count;
    sqlite3pp::database db(DB_PATH);

    std::string query = "select song_id from "+cat+" order by random() limit 1";
    sqlite3pp::query qry(db, query.c_str());

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
        for (int j = 0; j < qry.column_count(); ++j) {
            out = (*i).get<char const*>(j);
        }
    }

    count = getCountRandomCat(out);

    return std::make_tuple(out, count);
}

string getCatRandomId(std::string cat)
{
    std::tuple<std::string, int> temp_tuple("test", 12);
    do
    {
        temp_tuple = getRandomTupleCat(cat);
    } while (std::get<1>(temp_tuple) == 0);

    std::string out = std::get<0>(temp_tuple);

    sqlite3pp::database db(DB_PATH);
    std::string query = "update t_songs set done=\"True\" where id=\""+out+"\"";
    db.execute(query.c_str());
    return out;
}

std::vector<std::string> getAllCat()
{
    int count = 0;
    sqlite3pp::database db(DB_PATH);

    std::string query = "select count(*) from t_categories";
    sqlite3pp::query qry_count(db, query.c_str());
    for (sqlite3pp::query::iterator i = qry_count.begin(); i != qry_count.end(); ++i) {
        for (int j = 0; j < qry_count.column_count(); ++j) {
            count = atoi((*i).get<char const*>(j));
        }
    }

    std::vector<std::string> out(count);

    query ="select cat_name from t_categories";
    sqlite3pp::query qry(db, query.c_str());

    int counting = 0;

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
        for (int j = 0; j < qry.column_count(); ++j) {
            out[counting] = (*i).get<char const*>(j);
        }
        counting += 1;
    }

    return out;
}

std::string getCatTable(std::string catName)
{
    string out = "not_found";
    sqlite3pp::database db(DB_PATH);

    std::string query ="select table_name from t_categories where cat_name =\""+catName+"\"";
    sqlite3pp::query qry(db, query.c_str());

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
        for (int j = 0; j < qry.column_count(); ++j) {
            out = (*i).get<char const*>(j);
        }
    }
    return out;
}

void setAllUndone()
{
    sqlite3pp::database db(DB_PATH);
    std::string query = "update t_songs set done=\"False\"";
    db.execute(query.c_str());
}

void updateSong(std::string id, std::string artist, std::string song_name, std::string in, std::string link, std::string time)
{
    sqlite3pp::database db(DB_PATH);
    std::string query = "update t_songs set artist=\""+artist+"\", song=\""+song_name+"\", `in`=\""+in+"\", link=\""+link+"\", time=\""+time+"\" where id=\""+id+"\"";
    db.execute(query.c_str());
}

void setSongRunning(std::string status)
{
    sqlite3pp::database db(DB_PATH);
    std::string query = "update t_config set value=\""+status+"\" where param=\"song_running\"";
    db.execute(query.c_str());
}

void setNotFoundAll()
{
    sqlite3pp::database db(DB_PATH);
    std::string query = "update t_players set artist=\"\", song=\"\", h_in=\"\", found_a=\"false\", found_s=\"false\", found_i=\"false\"";
    db.execute(query.c_str());
}

//Folowing code commented after moving to tcp packets

/*void checkAnswers(string artist, string song, string in)
{
    sqlite3pp::database db(DB_PATH);
    std::string query = "update t_players set found_a=\"true\" where artist=\""+artist+"\"";
    db.execute(query.c_str());
    query = "update t_players set found_s=\"true\" where song=\""+song+"\"";
    db.execute(query.c_str());
    query = "update t_players set found_i=\"true\" where h_in=\""+in+"\"";
    db.execute(query.c_str());
}*/

/*std::string getPlayerStatus()
{
    std::string model;

    int count = 0;
    sqlite3pp::database db(DB_PATH);

    std::string query = "select count(*) from t_players";
    sqlite3pp::query qry_count(db, query.c_str());
    for (sqlite3pp::query::iterator i = qry_count.begin(); i != qry_count.end(); ++i) {
        for (int j = 0; j < qry_count.column_count(); ++j) {
            count = atoi((*i).get<char const*>(j));
        }
    }

    std::vector<std::vector<std::string>> items(count, std::vector<std::string>(4,"null"));

    query ="select username, found_a, found_s, found_i from t_players";
    sqlite3pp::query qry(db, query.c_str());

    int counting = 0;

    std::string list_found = "";

    bool anyfound = false;

    for (sqlite3pp::query::iterator i = qry.begin(); i != qry.end(); ++i) {
        anyfound = false;
        list_found = "";
        for (int j = 0; j < qry.column_count(); ++j) {
            if (j == 0)
            {
                model += (*i).get<char const*>(j);
                model += "\n";
            }
            else if (j == 1)
            {
                if (std::string((*i).get<char const*>(j)) == "true")
                {
                    list_found += "\"Artist\" ";
                    anyfound = true;
                }
            }
            else if (j == 2)
            {
                if (std::string((*i).get<char const*>(j)) == "true")
                {
                    list_found += "\"Song name\" ";
                    anyfound = true;
                }
            }
            else if (j == 3)
            {
                if (std::string((*i).get<char const*>(j)) == "true")
                {
                    list_found += "\"Heard in\" ";
                    anyfound = true;
                }
            }

            if (!anyfound && j != 0)
            {
                list_found = "Nothing ";
            }

        }
        list_found += "found";

        model += list_found;
        model += "\n";
        counting += 1;
    }

    return model;
}*/
