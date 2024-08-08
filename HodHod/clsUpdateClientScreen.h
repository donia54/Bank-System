#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsBankClient.h"
#include "clsInputValidate.h"
using namespace std;
class clsUpdateClientScreen:protected clsScreen
{
private:

    static void ReadClientInfo(clsBankClient& Client)
    {
        cout << "\nEnter FirstName: ";
        Client.FirstName = clsInputValidate::ReadString();
        cout << "\nEnter LastName: ";
        Client.LastName = clsInputValidate::ReadString();
        cout << "\nEnter Email: ";
        Client.Email = clsInputValidate::ReadString();
        cout << "\nEnter Phone: ";
        Client.Phone = clsInputValidate::ReadString();
        cout << "\nEnter PinCode: ";
        Client.PinCode = clsInputValidate::ReadString();
        cout << "\nEnter Account Balance: ";
        Client.AccountBalance = clsInputValidate::ReadFloatNumber();
    }

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

public:

    static void ShowUpdateClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::pUpdateClients))
        {
            return;
        }
        string AccountNumber;
        cout << "\nPlease Enter client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExist(AccountNumber))
        {
            cout << "\nAccount Number is not found choose another one: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient client1 = clsBankClient::Find(AccountNumber);
        _PrintClient(client1);
        cout << "\nUpdate client Info: ";
        cout << "\n________________________\n";
        ReadClientInfo(client1);

        clsBankClient::enSaveResults SaveResult;
        SaveResult = client1.Save();

        switch (SaveResult)
        {
        case clsBankClient::svFaildEmptyObjext:
            cout << "\nError account was not saved because it is empty";
            break;
        case clsBankClient::svSucceeded:
            cout << "\n Account Update Successfully :)\n";
            _PrintClient(client1);
            break;
        default:
            break;
        }
    }


};

