#include <map>
#include "TwitterData.hpp"
using namespace std;

int main(int argc, char *argv[])
{
    string raw_data[5][6] = {{"rangerPower", "Smit", "Rick", "smitRick@gmail.com", "1117", "power lifting"},
                             {"kittyKat72", "Smith", "Kathryn", "kat@gmail.com", "56", "health"},
                             {"lexi5", "Anderson", "Alexis", "lexi5@gmail.com", "900", "education"},
                             {"savage1", "Savage", "Ken", "ksavage@gmail.com", "17", "president"},
                             {"smithMan", "Smith", "Rick", "rick@hotmail.com", "77", "olympics"}};
    TwitterData *twitter_data = new TwitterData[5];
    for (int i = 0; i < 5; ++i)
    {
        twitter_data[i].setUserName(raw_data[i][0]);
        twitter_data[i].setActualName(raw_data[i][2] + " " + raw_data[i][1]);
        twitter_data[i].setEmail(raw_data[i][3]);
        twitter_data[i].setNumTweets(stoi(raw_data[i][4]));
        twitter_data[i].setCategory(raw_data[i][5]);
    }


    map<string, TwitterData> twitterUsers;
    for (int i = 0; i < 5; i++)
    {
        twitterUsers[ twitter_data[i].getUserName() ] = twitter_data[i];
    }
    cout << "Print searchByName map: " << endl;
    for (const auto &pair : twitterUsers)
    {
        cout << "Key: " << pair.first << ", Value: " << pair.second.print() << endl;
    }
    string userQuery = "savage1";
    auto userSearch = twitterUsers.find(userQuery);
    if (userSearch != twitterUsers.end())
    {
        cout << "Search for key: " << userSearch->first << " Value: ";
        cout << userSearch->second.print() << endl;
        twitterUsers.erase(userQuery);
        cout << "Removed User: " << userSearch->first << endl;
    }
    elsep
    {
        cout << "User not found: " << userSearch->first << endl;
    }

    map<string, TwitterData> twitterEmails;
    for (int i = 0; i < 5; i++)
    {
        twitterEmails[ twitter_data[i].getEmail() ] = twitter_data[i];
    }
    cout << "Print searchByEmail map: " << endl;
    for (const auto &pair : twitterEmails)
    {
        cout << "Key: "<< pair.first << ", Value: " << pair.second.print() << endl;
    }
    string emailQuery = "kat@gmail.com";
    auto emailSearch = twitterEmails.find(emailQuery);
    if (emailSearch != twitterEmails.end())
    {
        cout << "Search for key: " << emailSearch->first << " Value: ";
        cout << emailSearch->second.print() << endl;;
        twitterEmails.erase(emailQuery);
        cout << "Removed User: " << emailSearch->first << endl;
    }
    else
    {
        cout << "User not found: " << emailSearch->first << endl;
    }
    return 0;
}