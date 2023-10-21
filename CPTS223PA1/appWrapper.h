#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <string.h>

#include "List.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

struct cmdData
        {
             string name;
             string description;

        };

struct profile{
    string name;
    int score;
};

class appWrapper {
public:
    appWrapper(string commandsFile, string gameFile)
    {
        mCommandsFile = commandsFile;
        mGameFile = gameFile;

        modified = false;
    }

    appWrapper(const appWrapper& app)
    {
        mCommandsFile = app.mCommandsFile;
        mGameFile = app.mGameFile;

        modified = false;
    }

    void run();

private:
    List<cmdData> mCmds;
    profile players[16];
    int playerCount;
    string mCommandsFile;
    string mGameFile;

    void importCommands();
    void importProfiles();
    cmdData parseCmdLine(string line);
    profile parseProfile(string line);
    void printGameMenu();

    void printGameRules();
    void playGame(int startScore);
    void loadPreviousGame(int& score);
    void addCommand();
    void removeCommand();

    bool modified;
    void updateProfile(string name, int score);
    void saveCommands();
    void saveProfiles();

    void randomizeIntArray(int intArray[], int length, int min, int max);
};

int randomInt(int min, int max);
int promptInt(int min, int max, string message);
bool operator==(const cmdData& lhs, const cmdData& rhs);