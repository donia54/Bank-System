#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include"clsString.h"
#include"clsPerson.h"
#include"clsDate.h"
using namespace std;

class clsBankClient : public clsPerson
{
private:

	enum enMode{EmptyMode=0,UpdateMode=1,AddNewMode=3};
	enMode _Mode;
	string _AccountNumber, _PinCode;
	float _AccountBalance;
    bool _MarkedForDelete = false;
    struct stTrnsferLogRecord;

   static clsBankClient  _ConvertLineToClientObject(string Line,string Delim="#//#")
   {
       vector<string>vClientData;
       vClientData = clsString::Split(Line, Delim);

       return clsBankClient(UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
   }

   static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
   {

       string stClientRecord = "";
       stClientRecord += Client.FirstName + Seperator;
       stClientRecord += Client.LastName + Seperator;
       stClientRecord += Client.Email + Seperator;
       stClientRecord += Client.Phone + Seperator;
       stClientRecord += Client.AccountNumber() + Seperator;
       stClientRecord += Client.PinCode + Seperator;
       stClientRecord += to_string(Client.AccountBalance);
       return stClientRecord;

   }

   static vector<clsBankClient> _loadClientsDataFromFile()
   {
       vector <clsBankClient> vClients;
       fstream MyFile;
       MyFile.open("Client.txt", ios::in);

       if (MyFile.is_open())
       {
           string Line;
           while (getline(MyFile, Line))
           {

               clsBankClient Client = _ConvertLineToClientObject(Line);
               vClients.push_back(Client);
           }
           MyFile.close();

       }

       return vClients;
   }

   static void  _SaveClientsDataToFile(vector<clsBankClient> vClients)
   {
       fstream MyFile;
       MyFile.open("Client.txt", ios::out);
       string DataLine;
       if (MyFile.is_open())
       {

           for (clsBankClient C : vClients)
           {
               if (C._MarkedForDelete == false)
               {
                   DataLine = _ConverClientObjectToLine(C);
                   MyFile << DataLine << endl;
               }
           }
           MyFile.close();
       }
   }

   static clsBankClient _GetEmptyClientObject()
   {
       return clsBankClient{ EmptyMode,"","","","","","",0 };
   }

   void   _Update()
   {
       vector<clsBankClient>_vClients;
       _vClients = _loadClientsDataFromFile();
       for (clsBankClient& c : _vClients)
       {
           if (c.AccountNumber() == AccountNumber())
           {
               c = *this;
               break;
           }
       }
       _SaveClientsDataToFile(_vClients);
   }

   void _AddDataLineToFile(string stDataLine)
   {
       fstream MyFile;
       MyFile.open("Client.txt", ios::out | ios::app);

       if (MyFile.is_open())
       {

           MyFile << stDataLine << endl;

           MyFile.close();
       }

   }

   void _AddNew()
   {
       _AddDataLineToFile(_ConverClientObjectToLine(*this));
   }

   string _PreparTransferLogRecord(float Amount, clsBankClient DestinationClient, string UserName, string Delim = "#//#")
   {
       string SysDataRecord = clsDate::GetSystemDateTimeString() + Delim + AccountNumber() + Delim + DestinationClient.AccountNumber() + Delim + to_string(Amount) + Delim + to_string(AccountBalance) + Delim + to_string(DestinationClient.AccountBalance) +Delim+ UserName;
       return SysDataRecord;

   }

   void _RegisterTransferLog(float Amount, clsBankClient& DestinationClient, string UserName)
   {
       string stDataLine = _PreparTransferLogRecord(Amount, DestinationClient, UserName);

       fstream MyFile;
       MyFile.open("TransfersLog.txt", ios::out | ios::app);
       if (MyFile.is_open())
       {
           MyFile << stDataLine << endl;
           MyFile.close();
       }

   }

   static stTrnsferLogRecord _ConvertTransferLogLineToRecord(string Line, string Seperator = "#//#")
   {
       stTrnsferLogRecord TrnsferLogRecord;
       vector <string> vTrnsferLogRecordLine = clsString::Split(Line, Seperator);
       TrnsferLogRecord.DateTime = vTrnsferLogRecordLine[0];
       TrnsferLogRecord.SourceAccountNumber = vTrnsferLogRecordLine[1];
       TrnsferLogRecord.DestinationAccountNumber = vTrnsferLogRecordLine[2];
       TrnsferLogRecord.Amount = stod(vTrnsferLogRecordLine[3]);
       TrnsferLogRecord.srcBalanceAfter = stod(vTrnsferLogRecordLine[4]);
       TrnsferLogRecord.destBalanceAfter = stod(vTrnsferLogRecordLine[5]);
       TrnsferLogRecord.UserName = vTrnsferLogRecordLine[6];

       return TrnsferLogRecord;
   }
 

public:

    struct stTrnsferLogRecord
    {
        string DateTime;
        string SourceAccountNumber;
        string DestinationAccountNumber;
        float Amount;
        float srcBalanceAfter;
        float destBalanceAfter;
        string UserName;

    };


	clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance)
		: clsPerson(FirstName, LastName, Email, Phone)
	{
		_Mode = Mode;
		_AccountNumber = AccountNumber;
		_PinCode = PinCode;
		_AccountBalance = AccountBalance;
	}

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    string AccountNumber()
    {
        return _AccountNumber;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }
    string GetPinCode()
    {
        return _PinCode;
    }
    __declspec(property(get = GetPinCode, put = SetPinCode)) string PinCode;

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }
    float GetAccountBalance()
    {
        return _AccountBalance;
    }
    __declspec(property(get = GetAccountBalance, put = SetAccountBalance)) float AccountBalance;


    static clsBankClient Find(string AccontNumber)
    {
        vector<clsBankClient>vClients;
        fstream myfile;
        myfile.open("Client.txt", ios::in);
        if (myfile.is_open())
        {
            string line;
            while (getline(myfile, line))
            {
                clsBankClient client = _ConvertLineToClientObject(line);
                if (client.AccountNumber() == AccontNumber)
                {
                    myfile.close();
                    return client;
                }
                vClients.push_back(client);
            }
            myfile.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccontNumber,string PinCode)
    {
        vector<clsBankClient>vClients;
        fstream myfile;
        myfile.open("Client.txt", ios::in);
        if (myfile.is_open())
        {
            string line;
            while (getline(myfile, line))
            {
                clsBankClient client = _ConvertLineToClientObject(line);
                if (client.AccountNumber() == AccontNumber&&client.PinCode==PinCode)
                {
                    myfile.close();
                    return client;
                }
                vClients.push_back(client);
            }
            myfile.close();
        }
        return _GetEmptyClientObject();
    }

    bool Delete()
    {
        vector<clsBankClient>vClients;
        vClients = _loadClientsDataFromFile();

        for (clsBankClient& c : vClients)
        {
            if (c.AccountNumber() == _AccountNumber)
            {
                c._MarkedForDelete = true;
                break;
            }
        }

        _SaveClientsDataToFile(vClients);
        *this = _GetEmptyClientObject();
        return true;

    }

    static vector<clsBankClient> GetClientsList()
    {
        return _loadClientsDataFromFile();
    }

    static double GetTotalBalances()
    {
        vector<clsBankClient> vClients = clsBankClient::GetClientsList();

        double TotalBalances = 0;
        for (clsBankClient c : vClients)
        {
            TotalBalances += c.AccountBalance;
        }
        return TotalBalances;
    }

    static bool IsClientExist(string AccontNumber)
    {
        clsBankClient client = Find(AccontNumber);
        return (!client.IsEmpty());
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    enum enSaveResults{svFaildEmptyObjext=0,svSucceeded=1,svFaildAccountNumberExists=2};

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
            return enSaveResults::svFaildEmptyObjext;
        case enMode::UpdateMode:
            _Update();
            return enSaveResults::svSucceeded;
        case enMode::AddNewMode:
            if (clsBankClient::IsClientExist(_AccountNumber))
                return enSaveResults::svFaildAccountNumberExists;
            else
            {
                _AddNew();
                _Mode = enMode::AddNewMode;
                return enSaveResults::svSucceeded;
            }
            break;
        }

    }

    void Deposit(double Add)
    {
        _AccountBalance += Add;
        Save();
    }

    bool Withdraw(double withdraw)
    {
        if (withdraw > _AccountBalance)
        {
            return false;
        }
        else
        {
            _AccountBalance -= withdraw;
            Save();
            return true;
        }
    }

    bool Transfer(float Amount, clsBankClient& DestinationClient,string UserName)
    {
        if (Amount > AccountBalance) return false;

        Withdraw(Amount);
        DestinationClient.Deposit(Amount);
        _RegisterTransferLog(Amount, DestinationClient, UserName);
        return true;
    }


    static  vector <stTrnsferLogRecord> GetTransfersLogList()
    {
        vector <stTrnsferLogRecord> vTransferLogRecord;
        fstream MyFile;
        MyFile.open("TransfersLog.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;
            stTrnsferLogRecord TransferRecord;
            while (getline(MyFile, Line))
            {
                TransferRecord = _ConvertTransferLogLineToRecord(Line);
                vTransferLogRecord.push_back(TransferRecord);
            }
            MyFile.close();
        }
        return vTransferLogRecord;

    }




   /* void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName;
        cout << "\nLastName    : " << LastName;
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email;
        cout << "\nPhone       : " << Phone;
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";

    }*/

};
