#include "favor.h"
#include "accountmanager.h"
#include "gtest/gtest.h"
#include "skypemanager.h"


//TODO: this test should be based on a fixture that generates a database with a skype account pre-inserted, which we use for
//all of our tests. unfortunately can't use the default generated by test data because the location will be different

#define SKYPE_TEST_DB_LOC "/home/josh/.Skype/joshua.tanner/main.db"


TEST(SkypeManager, General){

    initialize();
    worker::buildDatabase();
    //reader::refreshAll();

    AccountManager::addAccount("SkypeTest", TYPE_SKYPE, "{\"skypeDatabaseLocation\":\"" SKYPE_TEST_DB_LOC "\"}");
    reader::accountList()->front()->updateMessages();



}