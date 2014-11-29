#include "favor.h"
#include "address.h"
#include "vector"
#include "gtest/gtest.h"

using namespace std;
using namespace favor;

TEST(LowercaseMethod, Lowercases) {
    string test1("CATS");
    string test2("cAtS");
    string test3("cats");

    string result("cats");
    ASSERT_EQ(lowercase(test1), result);
    ASSERT_EQ(lowercase(test2), result);
    ASSERT_EQ(lowercase(test3), result);
}

TEST(AsString, Integer){
    ASSERT_EQ(as_string(359), "359");
    ASSERT_EQ(as_string(-23), "-23");
    ASSERT_EQ(as_string(1234578), "1234578");
}

TEST(AsString, Long){
    ASSERT_EQ(as_string(-3002l), "-3002");
    ASSERT_EQ(as_string(0l), "0");
    ASSERT_EQ(as_string(3135239583021), "3135239583021");
}

TEST(AsString, Float){
    //Substring here because floats/doubles are tricky about output length
    float f1 = 0;
    float f2 = -25.355;
    ASSERT_EQ(as_string(f1).substr(0,1), "0");
    ASSERT_EQ(as_string(f2).substr(0, 7), "-25.355");
}

TEST(AsString, Double){
    //Substring here because floats/doubles are tricky about output length
    double d1 = -0.644893;
    double d2 = 25.555;
    ASSERT_EQ(as_string(d1).substr(0, 9), "-0.644893");
    ASSERT_EQ(as_string(d2).substr(0, 6), "25.555");
}

TEST(CompareAddress, Compare){
    //compareAddress is really a "greater than" operator

    Address a1("test1", 1, -1, TYPE_EMAIL);
    Address a2("test2", 2, -1, TYPE_EMAIL);
    Address a3("test3", 1, 1, TYPE_EMAIL);
    Address a4("test4", 2, 1, TYPE_EMAIL);
    std::list<Address> addrs;
    addrs.push_back(a1);
    addrs.push_back(a2);
    addrs.push_back(a3);
    addrs.push_back(a4);
    addrs.sort(compareAddress);
    auto it = addrs.begin();
    ASSERT_EQ(*it, a4);
    ++it;
    ASSERT_EQ(*it, a3);
    ++it;
    ASSERT_EQ(*it, a2);
    ++it;
    ASSERT_EQ(*it, a1);
    ++it;

    ASSERT_TRUE(compareAddress(a2, a1));
    ASSERT_TRUE(compareAddress(a3, a2));
}

TEST(SQLiteValidate, Validate){
    sqlite3* db;
    sqlite3_open(":memory:", &db);

    try{
        sqlite3_validate(SQLITE_OK, db, false);
        ASSERT_TRUE(true);
    } catch (std::exception& e){
        ASSERT_TRUE(false);
    }

    try{
        sqlite3_validate(SQLITE_ROW, db, false);
        ASSERT_TRUE(true);
    } catch (std::exception& e){
        ASSERT_TRUE(false);
    }

    try{
        sqlite3_validate(SQLITE_DONE, db, false);
        ASSERT_TRUE(true);
    } catch (std::exception& e){
        ASSERT_TRUE(false);
    }

    try{
        sqlite3_validate(SQLITE_CONSTRAINT, db, true);
        ASSERT_TRUE(true);
    } catch (std::exception& e){
        ASSERT_TRUE(false);
    }

    //Note that from here on out we WANT exceptions
    try{
        sqlite3_validate(SQLITE_CONSTRAINT, db, false);
        ASSERT_TRUE(false);
    } catch (std::exception& e){
        ASSERT_TRUE(true);
    }

    try{
        sqlite3_validate(SQLITE_ERROR, db, false);
        ASSERT_TRUE(false);
    } catch (std::exception& e){
        ASSERT_TRUE(true);
    }


}