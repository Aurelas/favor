#ifndef favor_def_include
#define favor_def_include

/*
Definitions we use:
ANDROID - This is pretty obvious, it's true if we're compiling for Android phones
DEBUG - Also pretty obvious, it's true when we're building for debug
 */

//Macros --------------------------------------------------------------------------------
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif

#ifdef ANDROID
#define CLASS_PATH "com/favor/library/"
#endif

/*
 * For ease of use reasons, everywhere we use SQLite in favor, there should be an
 * sqlite* variable available named "db". If there's an exception to this rule, the 
 * perpetrator can call sqlite3_validate directly...
 */
#define sqlv(arg1) sqlite3_validate(arg1, db)


#define NONCOPYABLE(class) class(const class&) = delete;\
class& operator=(const class&) = delete;

#define NONMOVEABLE(class) class(const class&&) = delete;\
class& operator=(const class&&) = delete;

//Types --------------------------------------------------------------------------------
namespace favor {
    enum MessageType {
        TYPE_EMAIL = 0, TYPE_ANDROIDTEXT = 1, TYPE_LINE = 2, TYPE_SKYPE = 3, NUMBER_OF_TYPES = 4
    };
    enum MessageTypeFlag {
        FLAG_EMPTY = 0,
        FLAG_EMAIL = 1 << TYPE_EMAIL,
        FLAG_ANDROIDTEXT = 1 << TYPE_ANDROIDTEXT,
        FLAG_LINE = 1 << TYPE_LINE,
        FLAG_SKYPE = 1 < TYPE_SKYPE
    };
    inline MessageTypeFlag operator|(MessageTypeFlag lhs, MessageTypeFlag rhs){
        return static_cast<MessageTypeFlag>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }
    const MessageTypeFlag MessageTypeFlags[NUMBER_OF_TYPES] = {FLAG_EMAIL, FLAG_ANDROIDTEXT, FLAG_LINE, FLAG_SKYPE};
    extern const char *MessageTypeName[];
}

//Constants --------------------------------------------------------------------------------
#define ADDRESS_CHECK_MESSAGE_COUNT 500 //The number of recent sent messages we look at when determining what addresses to pull
#define MAX_ADDRESSES 100 //Max addresses that we want to hold per type
#define SAVE_BODY true //TODO: this will eventually be a variable we get from settings or something and not a constant

//Database --------------------------------------------------------------------------------
#define DB_PATH_FULL (string(favor::dbPath)+"/favor.db").c_str()
#define DB_SORT_ORDER "DESC"


//Accounts table
#define ACCOUNT_TABLE "accounts"
#define ACCOUNT_TABLE_SCHEMA "(name TEXT NOT NULL, type INTEGER NOT NULL, details_json TEXT, PRIMARY KEY(name, type))"

//Contacts table
#define CONTACT_TABLE "contacts"
#define CONTACT_TABLE_SCHEMA "(id INTEGER PRIMARY KEY, display_name TEXT NOT NULL, type_flags INTEGER NOT NULL)"

//Addresses table
/*Note:
The foreign key here can be null, and this is intentional. In cases where it is null, the address is not attached to a contact.
 */
#define ADDRESS_TABLE(type) "addresses_" +string(MessageTypeName[type]) + ""
#define ADDRESS_TABLE_SCHEMA "(address TEXT NOT NULL UNIQUE, count INTEGER NOT NULL, contact_id INTEGER REFERENCES " CONTACT_TABLE "(id))"

#define ADDRESS_INDEX "i_" ADDRESS_TABLE
#define ADDRESS_INDEX_SCHEMA "(contact_name)"


/*Note:
These are determined partially at runtime by using, among other things, the name of an account. They should never be necessary
outside the scope of an AccountManager class, and (unless you whip up your own accountName variable) they will accordingly
not even compile.
 */
#define SENT_TABLE_NAME "\""+accountName+"_"+MessageTypeName[type]+"_sent\""
#define RECEIVED_TABLE_NAME "\""+accountName+"_"+MessageTypeName[type]+"_received\""

#define SENT_INDEX_NAME "i_" SENT_TABLE_NAME
#define RECEIVED_INDEX_NAME "i_" RECEIVED_TABLE_NAME

/*Note:
 * http://www.sqlite.org/lang_createtable.html
 * "But the following declaration does not result in "x" being an alias for the rowid:
 * CREATE TABLE t(x INTEGER PRIMARY KEY DESC, y, z);"
 */
namespace favor{
    enum Key{
        KEY_ADDRESS = 1 << 0, //00 0001
        KEY_DATE = 1 << 1, //00 0010
        KEY_CHARCOUNT = 1 << 2, //00 0100
        KEY_MEDIA = 1 << 3, //00 1000
        KEY_BODY = 1 << 4, //01 0000
        KEY_ID = 1 << 5, //10 000
        KEY_ALL = 63    //11 1111

    };
    inline Key operator|(Key lhs, Key rhs){
        return static_cast<Key>(static_cast<int>(lhs) | static_cast<int>(rhs));
    }

    enum ResultType {AVG_CHARS, AVG_RESPONSE, TOTAL_CHARS, TOTAL_RESPONSE, TOTAL_MESSAGES};
}
//We need nulls so that averages work properly with messages we failed to record
#define RECEIVED_TABLE_SCHEMA "(id INTEGER NOT NULL, address TEXT NOT NULL, date INTEGER, charcount INTEGER, media INTEGER, body TEXT, PRIMARY KEY(id))"
#define SENT_TABLE_SCHEMA "(id INTEGER NOT NULL, address TEXT NOT NULL, date INTEGER, charcount INTEGER, media INTEGER, body TEXT, PRIMARY KEY(id, address))"
/*Note:
 * Date is more selective than address and in that sense might seem like a better candidate for
 * being first in the index, but we will commonly query specifying an address and no date at all.
 * In this case, if address was not first, we could not even use the index at all. Also, queries are
 * sorted DESC.
 */
#define MESSAGE_INDEX_SCHEMA "(address " DB_SORT_ORDER ", date " DB_SORT_ORDER ")"



#endif