#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsWithdrawScreen:protected clsScreen
{
private:

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName;
        cout << "\nLastName    : " << Client.LastName;
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email;
        cout << "\nPhone       : " << Client.Phone;
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode;
        cout << "\nBalance     : " << Client.AccountBalance;
        cout << "\n___________________\n";

    }

    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease enter AccountNumber? ";
        cin >> AccountNumber;
        return AccountNumber;
    }

public:

    static void ShowDepositScreen()
    {
        _DrawScreenHeader("\t   Withdraw Screen");
        string AccountNumber = _ReadAccountNumber();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nClient with [" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }
        clsBankClient client = clsBankClient::Find(AccountNumber);

        _PrintClient(client);
        double withdraw = 0;
        cout << "\nPlease enter deposit amount? ";
        withdraw = clsInputValidate::ReadDoubleNumber();
        char Ans = 'n';
        cout << "\n\nAre you sure you want perfrom this transaction? y/n ? ";
        cin >> Ans;
        if (tolower(Ans) == 'y')
        {
            if (client.Withdraw(withdraw))
            {
                cout << "\nAmount Withdrawed Successfully.\n";
                cout << "\nNew Balance Is: " << client.AccountBalance;
            }
            else
            {
                cout << "\nCannot withdraw, Insuffecient Balance!\n";
                cout << "\nAmout to withdraw is: " <<withdraw;
                cout << "\nYour Balance is: " << client.AccountBalance;
            }
        }
        else
            cout << "\nOperation was cancelled.\n";

    }
};

