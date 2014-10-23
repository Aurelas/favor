#ifndef favor_def_include
#define favor_def_include

/*
Definitions we use:
ANDROID - This is pretty obvious, it's true if we're compiling for Android phones
DEBUG - Also pretty obvious, it's true when we're building for debug
 */

//Macros
#ifdef DEBUG
#define D(x) x
#else
#define D(x)
#endif
/*
 * For ease of use reasons, everywhere we use SQLite in favor, there should be an
 * sqlite* variable available named "db". If there's an exception to this rule, the 
 * perpetrator can call sqlite3_validate directly...
 */
#define sqlv(arg1) sqlite3_validate(arg1, db)
//Types
namespace favor {
    enum MessageType {
        TYPE_EMAIL, TYPE_ANDROIDTEXT, TYPE_LINE, TYPE_SKYPE, NUMBER_OF_TYPES
    };
    extern const char *MessageTypeName[];
}

//Constants
#define ADDRESS_CHECK_MESSAGE_COUNT 500 //The number of recent sent messages we look at when determining what addresses to pull
#define MAX_ADDRESSES 100 //Max addresses that we want to hold per type

//Database
#define DB_NAME "favor.db"


//Accounts table
#define ACCOUNT_TABLE "accounts"
#define ACCOUNT_TABLE_SCHEMA "(name TEXT NOT NULL, type INTEGER NOT NULL, details_json TEXT, PRIMARY KEY(name, type))"
/*Note:
 * Frankly, the accounts table doesn't seem worth indexing. We almost exclusively read all the records from it anyway, and it's tiny.
 * The only performance gains would be on deletes, which are very infrequent.
 */

//Contacts table
/*Note:
"explicit" is our way of specifying whether Favor is automatically generating a contact for a stranded address, or whether
the contact has been explicitly specified as one (whether at Favor's suggestion or not) by the user.
 */
#define CONTACT_TABLE(type) "contacts_" + string(MessageTypeName[type]) + ""
#define CONTACT_TABLE_SCHEMA "(id INTEGER PRIMARY KEY, display_name TEXT NOT NULL)"

//Addresses table
/*Note:
The foreign key here can be null, and this is intentional. In cases where it is null, the address is not attached to a contact.
 */
#define ADDRESS_TABLE(type) "addresses_" +string(MessageTypeName[type]) + ""
#define ADDRESS_TABLE_SCHEMA(type) "(address TEXT NOT NULL, count INTEGER NOT NULL, contact_id INTEGER REFERENCES " CONTACT_TABLE(type) "(id))"

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
#define RECEIVED_TABLE_SCHEMA "(id INTEGER, address TEXT NOT NULL, date INTEGER NOT NULL, charcount INTEGER NOT NULL, media INTEGER NOT NULL, PRIMARY KEY(id))"
#define SENT_TABLE_SCHEMA "(id INTEGER, address TEXT NOT NULL, date INTEGER NOT NULL, charcount INTEGER NOT NULL, media INTEGER NOT NULL, PRIMARY KEY(id, address))"
/*Note:
 * Date is more selective than address and in that sense might seem like a better candidate for
 * being first in the index, but we will commonly query specifying an address and no date at all.
 * In this case, if address was not first, we could not even use the index at all. Also, queries are
 * sorted DESC.
 */
#define MESSAGE_INDEX_SCHEMA "(address DESC, date DESC)"



#endif