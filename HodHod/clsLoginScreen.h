#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsPerson.h"
#include "clsUser.h"
#include "clsInputValidate.h"
#include"clsMainScreen.h"
#include"Global.h"
using namespace std;

class clsLoginScreen:protected clsScreen
{
private:

	static bool _Login()
	{
		bool LoginFaild = false;
		int FaildCnt = 0;
		string Username, Pass;
		do
		{
			if (LoginFaild)
			{
				FaildCnt++;
				cout << "\nInvlaid Usename/password!\n";
				cout << "\nYou have " << (3 - FaildCnt)
					<< " Trial(s) to login.\n\n";
			}
			if (FaildCnt == 3)
			{
				cout << "\nYour are Locked after 3 faild trails \n\n";
				return false;
			}
			cout << "Enter Username : ";
			cin >> Username;
			cout << "Enter Password : ";
			cin >> Pass;
			CurrentUser = clsUser::Find(Username, Pass);
			LoginFaild = CurrentUser.IsEmpty();
		} while (LoginFaild);
		CurrentUser.RegisterLoginToLogFile();
		clsMainScreen::ShowMainMenue();
		return true;
	}

public:

	static bool ShowLoginScreen()
	{
		system("cls");
		_DrawScreenHeader("\t  Login Screen");
		return _Login();

	}
};

