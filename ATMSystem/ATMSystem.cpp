#include <iostream>
#include <vector>
#include <fstream>
#include <string>

using namespace std;

const string ClientsFileName = "Clients.txt";

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;

};

enum enAtmMainMenueOptions { eQuickWithdraw = 1, eNormalWithdraw = 2, eDeposit = 3, eCheckBalance = 4, eChangePassword = 5, eLogout = 6 };

enum enQuickWithdrawMenueOptions { Twenty = 1, Fifty = 2, OneHundred = 3, TwoHundred = 4, FourHundred = 5, SixHundred = 6, EightHundred = 7, OnetThousand = 8, Exit = 9 };

sClient CurrentClient;

void Login();
void ShowMainMenue();
void ShowNormalWithdrawScreen();
void ShowQuickWithdrawScreen();

vector<string> SplitString(string S1, string Delim)
{

    vector<string> vString;

    short pos = 0;
    string sWord; // define a string variable  

    // use find() function to get the position of the delimiters  
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word   
        if (sWord != "")
        {
            vString.push_back(sWord);
        }

        S1.erase(0, pos + Delim.length());  /* erase() until positon and move to next word. */
    }

    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }

    return vString;

}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{

    sClient Client;
    vector<string> vClientData;

    vClientData = SplitString(Line, Seperator);

    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]);//cast string to double


    return Client;

}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{

    string stClientRecord = "";

    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);

    return stClientRecord;

}


vector <sClient> LoadCleintsDataFromFile(string FileName)
{

    vector <sClient> vClients;

    fstream MyFile;
    MyFile.open(FileName, ios::in);//read Mode

    if (MyFile.is_open())
    {

        string Line;
        sClient Client;

        while (getline(MyFile, Line))
        {

            Client = ConvertLinetoRecord(Line);

            vClients.push_back(Client);
        }

        MyFile.close();

    }

    return vClients;

}

bool FindUserByaccountNumberAndPinCode(string AccountNumber, string PinCode, sClient& Client)
{
    vector <sClient> vClient = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient C : vClient)
    {
        if (C.AccountNumber == AccountNumber && C.PinCode == PinCode)
        {
            Client = C;
            return true;

        }
    }

    return false;

}

bool LoadClinetInfo(string AccountNumber, string PinCode)
{
    if (FindUserByaccountNumberAndPinCode(AccountNumber, PinCode, CurrentClient))
        return true;
    else
        return false;

}

vector <sClient> SaveCleintsDataToFile(string FileName, vector <sClient> vClients)
{

    fstream MyFile;
    MyFile.open(FileName, ios::out);//overwrite

    string DataLine;

    if (MyFile.is_open())
    {

        for (sClient C : vClients)
        {

            if (C.MarkForDelete == false)
            {
                //we only write records that are not marked for delete.  
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;

            }

        }

        MyFile.close();

    }

    return vClients;

}


double CheckBalance()
{
    return CurrentClient.AccountBalance;
}

void ShowCheckBalanceScreen()
{
    cout << "===========================================\n";
    cout << "\tShow Check Balance Screen\n";
    cout << "===========================================\n";

    cout << "\nYour Balance is " << CheckBalance() << endl;

}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();

}

short ChooseQuickWithdraw()
{
    short Choice = 0;

    while (Choice < 1 || Choice > 9)
    {
        cout << "Choose what to Withdraw from? [1 to 9] ? ";
        cin >> Choice;
    }

    return Choice;
}


void Withdraw(double Amount)
{

    char Answer = 'n';

    cout << "\nAre you sure you want perfrom this transaction? y/n ?";
    cin >> Answer;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (CurrentClient.AccountNumber == C.AccountNumber)
            {
                C.AccountBalance -= Amount;
                CurrentClient = C;
                break;
            }
        }

        SaveCleintsDataToFile(ClientsFileName, vClients);

        cout << "\nDone Successfaly. New balance is: " << CheckBalance() << endl;
    }

}

void IsTheAmountExceedingYourBalance(int Amount)
{
    if (Amount > CurrentClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice\n";
        cout << "Press Ankey to continu...";
        system("pause>0");
        system("cls");
        ShowQuickWithdrawScreen();
    }
}

void PerfromQuickWithdrawMenueOption(enQuickWithdrawMenueOptions QuickWithdrawMenueOptions)
{
    switch (QuickWithdrawMenueOptions)
    {
    case Twenty:
        IsTheAmountExceedingYourBalance(20);
        Withdraw(20);
        GoBackToMainMenue();
        break;
    case Fifty:
        IsTheAmountExceedingYourBalance(50);
        Withdraw(50);
        GoBackToMainMenue();
        break;
    case OneHundred:
        IsTheAmountExceedingYourBalance(100);
        Withdraw(100);
        GoBackToMainMenue();
        break;
    case TwoHundred:
        IsTheAmountExceedingYourBalance(200);
        Withdraw(200);
        GoBackToMainMenue();
        break;
    case FourHundred:
        IsTheAmountExceedingYourBalance(400);
        Withdraw(400);
        GoBackToMainMenue();
        break;
    case SixHundred:
        IsTheAmountExceedingYourBalance(600);
        Withdraw(600);
        GoBackToMainMenue();
        break;
    case EightHundred:
        IsTheAmountExceedingYourBalance(800);
        Withdraw(800);
        GoBackToMainMenue();
        break;
    case OnetThousand:
        IsTheAmountExceedingYourBalance(1000);
        Withdraw(1000);
        GoBackToMainMenue();
        break;
    case Exit:
        ShowMainMenue();
        break;
    }
}

void ShowQuickWithdrawScreen()
{
    cout << "===========================================\n";
    cout << "\tShow Quick Withdraw Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] 20\t\t[2] 50\n";
    cout << "\t[3] 100\t\t[4] 200\n";
    cout << "\t[5] 400\t\t[6] 600\n";
    cout << "\t[7] 800\t\t[8] 1000\n";
    cout << "\t[9] Exit\n";
    cout << "===========================================\n";

    cout << "\nYour Balance is " << CheckBalance() << endl;

    double Amount = ChooseQuickWithdraw();

    PerfromQuickWithdrawMenueOption((enQuickWithdrawMenueOptions)Amount);

}

double Readamountmultipleof5()
{
    double Number;
    do
    {
        cout << "\nEnter an amount multiple of 5's ? ";
        cin >> Number;

    } while ((int)Number % 5 != 0);

    return Number;
}

void ShowNormalWithdrawScreen()
{
    cout << "===========================================\n";
    cout << "\tShow Normal Withdraw Screen\n";
    cout << "===========================================\n";

    double Amount = Readamountmultipleof5();

    if (Amount > CurrentClient.AccountBalance)
    {
        cout << "\nThe amount exceeds your balance, make another choice\n";
        cout << "Press Ankey to continu...";
        system("pause>0");
        system("cls");
        ShowNormalWithdrawScreen();

        return;
    }

    Withdraw(Amount);
}

double ReadAmountDeposit()
{
    double Amount;

    do
    {
        cout << "\nEnter a positive Deposit Amount ? ";
        cin >> Amount;

    } while (Amount < 1);

    return Amount;
}

void Deposit(double Amount)
{

    char Answer = 'n';

    cout << "\nAre you sure you want perfrom this transaction? y/n ?";
    cin >> Answer;

    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient& C : vClients)
        {
            if (CurrentClient.AccountNumber == C.AccountNumber)
            {
                C.AccountBalance += Amount;
                CurrentClient = C;
                break;
            }
        }

        SaveCleintsDataToFile(ClientsFileName, vClients);

        cout << "\nDone Successfaly. New balance is: " << CheckBalance() << endl;
    }

}

void ShowDepositScreen()
{
    cout << "===========================================\n";
    cout << "\t\tShow Deposit Screen\n";
    cout << "===========================================\n";

    Deposit(ReadAmountDeposit());

}

string ReadPinCode()
{
    string PinCode;

    cout << "\nEnter Pin Code ?";
    cin >> PinCode;

    return PinCode;
}

void ChangePassword()
{
    vector <sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    for (sClient& C : vClients)
    {
        if (C.AccountNumber == CurrentClient.AccountNumber)
        {
            C.PinCode = ReadPinCode();
            CurrentClient = C;
            break;
        }

    }

    SaveCleintsDataToFile(ClientsFileName, vClients);
    cout << "\nPassword changed successfully!";
}

void ShowChangePasswordScreen()
{
    cout << "===========================================\n";
    cout << "\tShow Change Password Screen\n";
    cout << "===========================================\n";

    ChangePassword();

}

void PerfromAtmMainMenueOption(enAtmMainMenueOptions AtmMainMenueOptions)
{
    switch (AtmMainMenueOptions)
    {
    case eQuickWithdraw:
        system("cls");
        ShowQuickWithdrawScreen();
        break;
    case eNormalWithdraw:
        system("cls");
        ShowNormalWithdrawScreen();
        GoBackToMainMenue();
        break;
    case eDeposit:
        system("cls");
        ShowDepositScreen();
        GoBackToMainMenue();
        break;
    case eCheckBalance:
        system("cls");
        ShowCheckBalanceScreen();
        GoBackToMainMenue();
        break;
    case eChangePassword:
        system("cls");
        ShowChangePasswordScreen();
        GoBackToMainMenue();
        break;
    case eLogout:
        system("cls");
        Login();
        break;
    }
}

short ReadMainMenueOption()
{
    cout << "Choose what do you want to do? [1 to 5]? ";
    short Choice = 0;
    cin >> Choice;

    return Choice;
}


void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t  AtM Main Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Quick Withdraw.\n";
    cout << "\t[2] Normal Withdraw.\n";
    cout << "\t[3] Deposit.\n";
    cout << "\t[4] Check Balance.\n";
    cout << "\t[5] Change Password.\n";
    cout << "\t[6] Logout.\n";
    cout << "===========================================\n";
    PerfromAtmMainMenueOption((enAtmMainMenueOptions)ReadMainMenueOption());
}

void Login()
{
    bool LoginFaild = false;

    string AccountNumber, PinCode;

    do
    {
        system("cls");

        cout << "===========================================\n";
        cout << "\t\tLogin Screen\n";
        cout << "===========================================\n";

        if (LoginFaild)
        {
            cout << "\nInvalid AccountNumber/PinCode!\n";
        }

        cout << "\nEnter AccountNumber? ";
        cin >> AccountNumber;

        cout << "Enter Pin Code? ";
        cin >> PinCode;

        LoginFaild = !LoadClinetInfo(AccountNumber, PinCode);


    } while (LoginFaild);

    ShowMainMenue();
}



int main()
{

    Login();

    system("pause>0");
    return 0;
}