#include "favor.h"
#include "reader.h"
#include "address.h"
#include "worker.h"
#include "accountmanager.h"
#include "gtest/gtest.h"
#include "testdata.h"
#include "testing.h"

using namespace std;
using namespace favor;


class Worker : public DatabaseTest {};

/*
 We trust some reader methods here, specifically to verify database changes. The testing dependencies created aren't ideal,
 but the alternative is basically copy pasting the exact same code into the tests to read the database, which seems worse.
 */

template<class InputIterator>
bool findContact (InputIterator first, InputIterator last, const Contact& val)
{
        //This is just here so we can compare contacts meaningfully for these tests; address counts or vector orders don't matter
        while (first!=last) {
                bool equal = (val.id == first->id && val.displayName == first->displayName && val.typeFlags() == first->typeFlags());
                //logger::info("Compare "+as_string(val)+" to "+as_string(*first));
                for (auto oit = val.getAddresses().begin(); oit != val.getAddresses().end(); ++oit){
                        bool foundMatch = false;
                        for (auto iit = first->getAddresses().begin(); iit != first->getAddresses().end(); ++iit){
                                foundMatch = foundMatch || (oit->type == iit->type && oit->addr == iit->addr && iit->contactId == oit->contactId);
                        }
                        equal = equal && foundMatch;
                }
                if (equal){
                        //logger::info("True");
                        return true;
                } else {
                    //logger::info("False");
                }
                ++first;
        }
        return false;
}

TEST_F(Worker, CreateAddress){
        Address addr1("test@test.com", 0, Address::NO_CONTACT_ID, TYPE_EMAIL);
        Address addr2("LineTest", 0, Address::NO_CONTACT_ID, TYPE_LINE);
        Address addr3("test2@test.com", 0, Address::NO_CONTACT_ID, TYPE_EMAIL);

        worker::createAddress(addr1.addr, addr1.count, addr1.contactId, addr1.type);
        worker::createAddress(addr2.addr, addr2.count, addr2.contactId, addr2.type);

        auto addresses = reader::addresses(FLAG_ALL, false);
        ASSERT_EQ(addresses->size(), 2);

        bool addr1Found = false;
        bool addr2Found = false;
        bool addr3Found = false;

        for (auto it = addresses->begin(); it != addresses->end(); ++it){
                logger::info(as_string(*it));
                addr1Found = addr1Found || ((*it) == addr1);
                addr2Found = addr2Found || ((*it) == addr2);
                addr3Found = addr3Found || ((*it) == addr3);
        }

        ASSERT_TRUE(addr1Found);
        ASSERT_TRUE(addr2Found);
        ASSERT_FALSE(addr3Found);

}

//TEST_F(Worker, UpdateAddressContactID){
// //TODO
//}

TEST_F(Worker, CreateContactWithAddress){
        Contact EmailTest1 CONTACT_EmailTest1_ARGS;
        Contact LineTest2 CONTACT_LineTest2_ARGS;

        std::list<Contact> definedContacts;
        definedContacts.push_back(EmailTest1);
        definedContacts.push_back(LineTest2);

        //Order is important here so predefined IDs match up
        worker::createContactWithAddress(EmailTest1.getAddresses()[0].addr, TYPE_EMAIL, EmailTest1.displayName);
        worker::createContactWithAddress(LineTest2.getAddresses()[0].addr, TYPE_LINE, LineTest2.displayName);


        auto contacts = reader::contactList();
        for (auto it = definedContacts.begin(); it != definedContacts.end();++it){
                ASSERT_TRUE(findContact(contacts->begin(), contacts->end(), *it));
        }

}

TEST_F(Worker, CreateContactWithAddressExisting){
        //What we are now testing is moving existing addresses to new contacts with this method
        Contact EmailTest1 CONTACT_EmailTest1_ARGS;
        worker::createContactWithAddress(EmailTest1.getAddresses()[0].addr, TYPE_EMAIL, EmailTest1.displayName);


        string emailTest2Name("EmailTest2");

        /*
         * This may look confusing because it's out of order, but first we create EmailTest 2 in the database with the address previously used by EmailTest1
         * so that EmailTest2 takes ownership of it. Then we create an address variable that looks like EmailTest1's address, except it has the ID of the new
         * EmaiLTest2 (which is 2) so that we can add it to EmailTest2 and later verify the two are correctly associated. Lastly we create the actual EmailTest2
         * variable so we can check for it in the results
         */
        worker::createContactWithAddress(EmailTest1.getAddresses()[0].addr, TYPE_EMAIL, emailTest2Name); //Take ownership of the address previously owned by EmailTest1
        Address NewEmailAddress(EmailTest1.getAddresses()[0].addr, EmailTest1.getAddresses()[0].count, 2, TYPE_EMAIL);
        Contact EmailTest2(2, emailTest2Name, NewEmailAddress); //Id of 3 since created third, and holding EmailTest1's address that it took

        Contact NewEmailTest1(EmailTest1.id, EmailTest1.displayName); //Recreate EmailTest1 without any linked contacts

        std::list<Contact> definedContacts;
        definedContacts.push_back(NewEmailTest1);
        definedContacts.push_back(EmailTest2);

        auto contacts = reader::contactList();
        for (auto it = definedContacts.begin(); it != definedContacts.end();++it){
            ASSERT_TRUE(findContact(contacts->begin(), contacts->end(), *it));
        }
}

TEST_F(Worker, CreateContactFromAddress){
        worker::exec(contactSeed); //Have to seed contacts first so the foreign key constraint works on addresses
        worker::exec(addressSeed);

        Contact EmailTest1Old CONTACT_EmailTest1_ARGS;
        Contact LineTest2Old CONTACT_LineTest2_ARGS;

        worker::createContactFromAddress(EmailTest1Old.getAddresses()[0], EmailTest1Old.displayName);
        worker::createContactFromAddress(LineTest2Old.getAddresses()[0], LineTest2Old.displayName);
        //TODO: it might be worthwhile to create a contact with a non-database-existant address and make sure we catch (log) that, but
        //I don't see a good way to detect whether something has been logged or not, for example

        std::vector<Address> EmailAddrs;
        for (auto it = EmailTest1Old.getAddresses().begin(); it != EmailTest1Old.getAddresses().end(); ++it){
                EmailAddrs.push_back(Address(it->addr, it->count, CONTACT_COUNT+1, it->type));
        }

        std::vector<Address> LineAddrs;
        for (auto it = LineTest2Old.getAddresses().begin(); it != LineTest2Old.getAddresses().end(); ++it) {
                LineAddrs.push_back(Address(it->addr, it->count, CONTACT_COUNT+2, it->type));
        }
        //Ids here(above and below) have to match the order of contact creations
        Contact CustomEmailTest(CONTACT_COUNT+1, EmailTest1Old.displayName, EmailAddrs);
        Contact CustomLineTest(CONTACT_COUNT+2, LineTest2Old.displayName, LineAddrs);

        //These are the original email/line test contacts without their addresses now that those addresses have moved to the above "customX" contacts
        Contact EmptyEmailTest(EmailTest1Old.id, EmailTest1Old.displayName);
        Contact EmptyLineTest(LineTest2Old.id, LineTest2Old.displayName);

        std::list<Contact> definedContacts;
        definedContacts.push_back(CustomEmailTest);
        definedContacts.push_back(CustomLineTest);
        definedContacts.push_back(EmptyEmailTest);
        definedContacts.push_back(EmptyLineTest);


        auto contacts = reader::contactList();
        for (auto it = definedContacts.begin(); it != definedContacts.end();++it){
                ASSERT_TRUE(findContact(contacts->begin(), contacts->end(), *it));
        }

}

TEST_F(Worker, RecomputeAddressTable){
        worker::exec(contactSeed); //Have to seed contacts first so the foreign key constraint works on addresses
        worker::exec(addressSeed);

        //TODO: this should eventually test name functionalities once they exist in the method, but they don't yet, so for now we
        //don't have to pay too much attention to names and can just throw some random data in

        std::vector<Address> definedAddresses;
        std::unordered_map<std::string, int> countedAddressesLine;
        std::unordered_map<std::string, std::string> addressNamesLine;
        std::unordered_map<std::string, int> countedAddressesEmail;
        std::unordered_map<std::string, std::string> addressNamesEmail;

        Address OldTest1 ADDR_test1_at_test_dot_com_ARGS;
        Address OldTest2 ADDR_Test2_ARGS;

        int newTest1Count = 27;
        int newTest2Count = 9;

        countedAddressesEmail[OldTest1.addr] = newTest1Count;
        countedAddressesLine[OldTest2.addr] = newTest2Count;
        addressNamesEmail[OldTest1.addr] = "Test 1 Email Address";

        definedAddresses.push_back(Address(OldTest1.addr, newTest1Count, OldTest1.contactId, OldTest1.type));
        definedAddresses.push_back(Address(OldTest2.addr, newTest2Count, OldTest2.contactId, OldTest2.type));

        //Now add some new addresses
        int new1Count = 3;
        int new2Count = 1;
        Address New1("worker1@work.com", new1Count, -1, TYPE_EMAIL);
        Address New2("Worky", new2Count, -1, TYPE_LINE);

        countedAddressesEmail[New1.addr] = new1Count;
        countedAddressesLine[New2.addr]= new2Count;
        addressNamesLine[New2.addr] = "New 2 Line Address";

        definedAddresses.push_back(New1);
        definedAddresses.push_back(New2);

        worker::recomputeAddressTable(countedAddressesEmail, addressNamesEmail, TYPE_EMAIL);
        worker::recomputeAddressTable(countedAddressesLine, addressNamesLine, TYPE_LINE);

        auto resultAddrs = reader::addresses(FLAG_ALL);


        for (auto it = definedAddresses.begin(); it != definedAddresses.end(); ++it){
                ASSERT_NE(std::find(resultAddrs->begin(), resultAddrs->end(), *it),resultAddrs->end());
        }
}
