#include "UserDatabase.h"

UserDatabase::UserDatabase() {
    addInitialUsers();
}

void UserDatabase::addInitialUsers() {
    readUsersFile(this->Users);
}
