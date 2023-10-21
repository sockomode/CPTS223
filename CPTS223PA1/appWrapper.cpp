#include "appWrapper.h"

/*************************************************************
 * Function: run ()                                          *
 * Description: runs the app wrapper                         *
 *************************************************************/
void appWrapper::run()
{
    int option, score = 0;
    bool exit = false;

    importCommands();
    importProfiles();

    while (!exit)
    {
        printGameMenu();
        option = promptInt(1, 6, "Enter an option : ");

        system("CLS");
        system("pause");

        switch (option) {
            case 1:
                printGameRules();
                break;
            case 2:
                playGame(score);
                break;
            case 3:
                loadPreviousGame(score);
                break;
            case 4:
                addCommand();
                break;
            case 5:
                removeCommand();
                break;
            case 6:
                exit = true;
                if (this->modified)
                {
                    saveCommands();
                }
                saveProfiles();
                cout << "Thank you for playing!" << endl;
                break;
        }
    }
}

/*************************************************************
 * Function: printGameMenu ()                                *
 * Description: prints the game menu for the user            *
 *************************************************************/
void appWrapper::printGameMenu()
{
    string menu[6] = { "Game Rules", "Play Game", "Load Previous Game","Add Command", "Remove Command", "Exit" };

    for (int i = 1; i < 7; i++)
    {
        cout << i << ". " << menu[i - 1] << std::endl;
    }
}

/*************************************************************
 * Function: printGameRules ()                               *
 * Description: prints the game rules                        *
 *************************************************************/
void appWrapper::printGameRules()
{
    printf("The objective of the game is to match the Linux commands with it's defintion.\n");
    printf("The player will receive points according to accuracy. \n");
}


/*************************************************************
 * Function: importCommands ()                               *
 * Description: imports commands                             *
 *************************************************************/
void appWrapper::importCommands()
 {
    string line;
    mCmds.clearList();
    cmdData newData;

    std::ifstream commandStream;
    commandStream.open(mCommandsFile);

    commandStream.clear();
    commandStream.seekg(0);

    while (getline(commandStream, line))
    {
        newData = parseCmdLine(line);
        mCmds.insertAtFront(newData);
    }

    commandStream.close();
}

/*************************************************************
 * Function: importProfiles ()                               *
 * Description: iterate over previous games file and parse   *
 *        each line into profile struct, add to array        *
 *************************************************************/
void appWrapper::importProfiles()
{
    string line;

    for (int i = 0; i < 16; i++)
    {
        players[i].name = "";
        players[i].score = 0;
    }
    playerCount = 0;

    std::ifstream gameStream;
    gameStream.open(mGameFile);

    gameStream.clear();
    gameStream.seekg(0);

    while (getline(gameStream, line) && playerCount < 16)
    {
        players[playerCount] = parseProfile(line);
        playerCount++;
    }

    gameStream.close();
}

/*************************************************************
 * Function: parseCmdLine ()                                 *
 * Description: parses csv lines                             *
 *************************************************************/
cmdData appWrapper::parseCmdLine(string line)
{
    string item;
    std::stringstream lineStream;
    cmdData newData;

    lineStream.str(line);

    getline(lineStream, item, ',');
    newData.name = item;

    if (lineStream.peek() == '"')
    {
        getline(lineStream, item, '"');
        getline(lineStream, item, '"');
    }
    else
    {
        getline(lineStream, item, ',');
    }
    newData.description = item;

    return newData;
}

/*************************************************************
 * Function: parseProfile ()                                 *
 * Description: parse csv lines from previous games file     *
 *        into profile struct                                *
 *************************************************************/
profile appWrapper::parseProfile(string line)
{
    string item;
    std::stringstream lineStream;
    profile newData;

    lineStream.str(line);

    getline(lineStream, item, ',');
    newData.name = item;

    getline(lineStream, item, ',');
    newData.score = stoi(item);

    return newData;
}

/*************************************************************
 * Function: playGame ()                                     *
 * Description: allows user to play the game                 *
 *************************************************************/
void appWrapper::playGame(int startScore)
{
    int score = startScore;
    int totalGuesses = 0;
    string name;

    cout << "Please enter your name \n";
    cin >> name;

    int questions = promptInt(5, 30, "How many questions will you answer? ");
    int cmdList[3];
    int printOrder[3];
    int usedCmds[1];

    for (int i = 0; i < questions; i++)
    {
        do
        {
            randomizeIntArray(cmdList, 3, 0, mCmds.getLength() - 1);
        } while (usedCmds[cmdList[0]]);

        usedCmds[cmdList[0]] = 1;

        randomizeIntArray(printOrder, 3, 0, 2);

        int correct = cmdList[0];
        cout << mCmds.getNodeAtPosition(correct)->data.name << endl;

        int desc;
        for (int i = 0; i < 3; i++)
        {
            desc = printOrder[i];
            cout << i << ". ";
            cout << mCmds.getNodeAtPosition(cmdList[desc])->data.description << endl;
        }

        int guess = promptInt(0, 2, "Which command does this correspond to? ");
        totalGuesses++;

        system("CLS");
        system("pause");

        if (printOrder[guess] == 0)
        {
            score++;
            cout << "Correct! Your score is now " << score << endl;
        }
        else {
            score--;
            cout << "Wrong! Your score is now " << score << endl;
            cout << mCmds.getNodeAtPosition(0)->data.name << " - " << mCmds.getNodeAtPosition(0)->data.description << endl;
        }
    }

    updateProfile(name, score);
}

/*************************************************************
 * Function: loadPreviousGame ()                             *
 * Description: loads previous game scores from scores.csv   *
 *************************************************************/
void appWrapper::loadPreviousGame(int& score)
{
    string name;
    bool found = false;
    cout << "Enter your name: ";
    cin >> name;

    for (int i = 0; i < playerCount; i++)
    {
        if (players[i].name == name)
        {
            score = players[i].score;
            found = true;
            break;
        }
    }

    if (found)
    {
        printf("Welcome back!\n");
    }
    else
    {
        printf("Error name not found!\n");
    }
}

/*************************************************************
 * Function: addCommand ()                                   *
 * Description: allows user to add command to commands.csv   *
 *************************************************************/
void appWrapper::addCommand()
{
    cmdData newData;
    bool valid = false;
    node<cmdData>* pCurrent;

    while (!valid) {
        cout << "Enter the name of the command you would like to add: ";
        cin >> newData.name;

        valid = true;
        pCurrent = mCmds.getHead();
        while (pCurrent != nullptr)
        {
            if (pCurrent->data.name == newData.name)
            {
                valid = false;
                break;
            }
            pCurrent = pCurrent->next;
        }

        if (!valid)
        {
            cout << "Duplicate command entered. Please try again." << endl;
        }
    }

    cout << "Enter the command description: ";
    getline(cin, newData.description);
    getline(cin, newData.description);
    cout << "Command '" << newData.name << "' successfully added." << endl;

    mCmds.insertAtFront(newData);
    this->modified = true;
}

/*************************************************************
 * Function: removeCommand ()                                *
 * Description: allows user to remove command from quiz list *
 *************************************************************/
void appWrapper::removeCommand()
{
    if (!mCmds.isEmpty())
    {
        string name;
        bool removed = false;

        cout << "Enter the name of the command you'd like to remove: \n";
        cin >> name;

        node<cmdData>* pCurrent = mCmds.getHead();
        while (pCurrent != nullptr)
        {
            if (pCurrent->data.name == name)
            {
                removed = mCmds.removeNode(pCurrent);
                break;
            }
            pCurrent = pCurrent->next;
        }

        if (removed)
        {
            this->modified = true;
            cout << "Command '" << name << "' successfully removed." << endl;
        }
        else
        {
            cout << "Unable to find command '" << name << "' to remove." << endl;
        }
    }
    else
    {
        cout << "Command list is empty, unable to remove." << endl;
    }
}

void appWrapper::updateProfile(string name, int score)
{
    for (int i = 0; i < playerCount; i++)
    {
        if (players[i].name == name)
        {
            players[i].score = score;
            return;
        }
    }

    if (playerCount < 16)
    {
        players[playerCount].name = name;
        players[playerCount].score = score;
        playerCount++;
    }
    else
    {
    }
}

/*************************************************************
 * Function: saveCommands ()                                 *
 * Description: saves command data to commands.csv           *
 *************************************************************/
void appWrapper::saveCommands()
{
    std::ofstream commandStream;
    commandStream.open(mCommandsFile, std::ofstream::trunc);
    node<cmdData>* pCurrent = mCmds.getHead();
    while (pCurrent != nullptr)
    {
        commandStream << pCurrent->data.name << ",\"" << pCurrent->data.description << "\"\n";
        pCurrent = pCurrent->next;
    }

    commandStream.close();
}

/*************************************************************
 * Function: saveProfiles ()                                 *
 * Description: saves game data to scores.csv                *
 *************************************************************/
void appWrapper::saveProfiles()
{
    std::ofstream gameStream;
    gameStream.open(mGameFile);

    for (int i = 0; i < playerCount; i++)
    {
        gameStream << players[i].name << "," << players[i].score << "\n";
    }

    gameStream.close();
}

/*************************************************************
 * Function: randomizeIntArray ()                            *
 * Description: randomizes the integer array                 *
 *************************************************************/
void appWrapper::randomizeIntArray(int intArray[], int length, int min, int max)
{
    int fill, newInt = 0;
    bool valid;

    while (fill < length)
    {

        newInt = randomInt(min, max);
        valid = true;
        for (int i = 0; i < fill; i++)
        {
            if (intArray[i] == newInt)
            {
                valid = false;
            }
        }

        if (valid)
        {
            intArray[fill] = newInt;
            fill++;
        }
    }
}

/*************************************************************
 * Function: randomInt ()                                    *
 * Description: returns a random integer                     *
 *************************************************************/
int randomInt(int min, int max)
{
    return (rand() % (max - min + 1)) + min;
}

/*************************************************************
 * Function: promptInt ()                                    *
 * Description: prompts user for an integer                  *
 *************************************************************/
int promptInt(int min, int max, string message)
{
    int p;

    do {
        if (cin.fail())
        {
            cin.clear();
            cin.ignore(1024, '\n');
        }
        cout << message;
        cin >> p;

    } while (cin.fail() || (p < min || p > max));

    return p;
}

/*************************************************************
 * Function: operator==                                      *
 * Description: a comparison operator function               *
 *************************************************************/
bool operator==(const cmdData& lhs, const cmdData& rhs)
{
    return (lhs.name == rhs.name && lhs.description == rhs.description);
}