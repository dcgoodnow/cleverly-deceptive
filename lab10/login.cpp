#include <fstream>
#include <iostream>
#include <string>

using namespace std;

#include "HashTable.cpp"

class user{
  public:
    user(string, string);
    string getKey() const;
    string getValue() const;
    static unsigned int hash(const string& str);

  private:
    string password;
    string name;
};

user::user(string n, string pw)
{
   name = n;
   password = pw;
}

string user::getKey() const
{
   return name;
}

string user::getValue() const
{
   return pw;
}

unsigned int user::hash(const string& str) {
   unsigned int val = 0;

   for (int i = 0; i < str.length(); ++i) {
      val += str[i];
   }

   return val;
}

int main()
{
   HashTable<user, string> users(7);
   ifstream userFile;
   userFile.open("password.dat");
   string tempName;
   string tempPw;
   while(userFile.good())
   {
      userFile >> tempName >> tempPw;
      users.insert(user(tempName, tempPw));
   }
   users.showStructure();
   userFile.close();
   


   return 0;
}
