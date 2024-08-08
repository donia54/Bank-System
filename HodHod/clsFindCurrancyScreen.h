#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include <iomanip>
using namespace std;
class clsFindCurrancyScreen:protected clsScreen
{
private:

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:\n";
        cout << "_____________________________\n";
        cout << "\nCountry    : " << Currency.GetCountry();
        cout << "\nCode       : " << Currency.GetCurrencyCode();
        cout << "\nName       : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) = : " << Currency.GetRate();
        cout << "\n_____________________________\n";
    }

    static void _ShowResults(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Was not Found :-(\n";
        }
    }
public:

	static void ShowFindCurrencyScreen()
	{
		_DrawScreenHeader("\t  Find Currency Screen");
		cout << "\nFind By: [1] Code or [2] Country ? ";
		short Answer = 1;
		cin >> Answer;
		if (Answer == 1)
		{
            string CurrencyCode;
            cout << "\nPlease Enter CurrencyCode: ";
            CurrencyCode = clsInputValidate::ReadString();
           clsCurrency Currency= clsCurrency::FindByCode(CurrencyCode);
           //cout << Currency.GetRate()<<"LLLLLLLLL";
           _ShowResults(Currency);

		}
		else
		{
            string Country;
            cout << "\nPlease Enter Country: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResults(Currency);

		}

	}
};

