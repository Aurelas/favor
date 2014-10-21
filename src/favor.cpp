#include "favor.h"
#include "worker.h"
#include "reader.h"
#include "logger.h"
#include "message.h"

using namespace std;

namespace favor {
    const char *MessageTypeName[] = {"email", "androidtext", "line", "skype"};

    void initialize() {
        sqlite3_enable_shared_cache(1);
        //The worker must be initialized first, because it will create the database if there is none
        worker::initialize();
        reader::initialize();
    }

    void cleanup() {
        worker::cleanup();
        reader::cleanup();
    }


    void sqlite3_validate(int result, sqlite3 *db) {
        switch (result) {
            //TODO: a specific case for constraint violations (esp. unique) that logs an error but doesn't except
            case SQLITE_OK:
                break;
            case SQLITE_ROW:
                break;
            case SQLITE_DONE:
                break;
            default:
                logger::error("SQLite error #" + as_string(result) + ", db says \"" + sqlite3_errmsg(db) + "\"");
                throw sqliteException();
        }
    }

    //On Android, these methods will not behave well with numbers whose digit count exceeds the DIGIT_MAX
    string as_string(long int l) {
    #ifdef ANDROID
    #define LONG_DIGIT_MAX 20
    char result[LONG_DIGIT_MAX] = {0};
    sprintf(result, "%ld", l);
    return string(result);
    #else
        return to_string(l);
    #endif
    }

    string as_string(int i) {
    #ifdef ANDROID
    #define INT_DIGIT_MAX 10
    char result[INT_DIGIT_MAX] = {0};
    sprintf(result, "%d", i);
    return string(result);
    #else
        return to_string(i);
    #endif
    }

    string as_string(const rapidjson::Document &json) {
        rapidjson::StringBuffer buff;
        rapidjson::Writer<rapidjson::StringBuffer> writer(buff);
        json.Accept(writer);
        return buff.GetString();
    }

    string as_string(const message &m) {
        //TODO:
    }

    string lowercase(const string &s){
        string ret;
        ret.reserve(s.length());
        transform(s.begin(), s.end(), ret.begin(), ::tolower); //Only compiles specifically with "::tolower"
        return ret;
    }


}