#pragma once
#include<iostream>
#include "clsScreen.h"
#include "clsCurrency.h"
#include "clsInputValidate.h"
using namespace std;
class clsCurrencyCalculator:protected clsScreen
{
private:

    static float _ReadAmount()
    {
        cout << "\nEnter Amount to Exchange: ";
        float Amount = 0;
        Amount = clsInputValidate::ReadFloatNumber();
        return Amount;
    }

    static clsCurrency _GetCurrency(string Message)
    {

        string CurrencyCode;
        cout << Message << endl;
        CurrencyCode = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(CurrencyCode))
        {
            cout << "\nCurrency is not found, choose another one: ";
            CurrencyCode = clsInputValidate::ReadString();
        }
        clsCurrency Currency = clsCurrency::FindByCode(CurrencyCode);
        return Currency;
    }

    static  void _PrintCurrencyCard(clsCurrency Currency, string Title = "Currency Card:")
    {
        cout << "\n" << Title << "\n";
        cout << "_____________________________\n";
        cout << "\nCountry       : " << Currency.GetCountry();
        cout << "\nCode          : " << Currency.GetCurrencyCode();
        cout << "\nName          : " << Currency.GetCurrencyName();
        cout << "\nRate(1$) =    : " << Currency.GetRate();
        cout << "\n_____________________________\n\n";
    }

    static void _PrintCalculationsResults(float Amount, clsCurrency CurrencyFrom, clsCurrency CurrencyTo)
    {

        _PrintCurrencyCard(CurrencyFrom, "Convert From:");
        float AmountInUSD = CurrencyFrom.ConvertToUSD(Amount);
        cout << Amount << " " << CurrencyFrom.GetCurrencyCode()<< " = " << AmountInUSD << " USD\n";
        if (CurrencyTo.GetCurrencyCode() == "USD")   return;
        cout << "\nConverting from USD to:\n";
        _PrintCurrencyCard(CurrencyTo, "To:");
        float AmountInCurrrency2 = CurrencyFrom.ConvertToOtherCurrency(Amount, CurrencyTo);
        cout << Amount << " " << CurrencyFrom.GetCurrencyCode() << " = " << AmountInCurrrency2 << " " << CurrencyTo.GetCurrencyCode();

    }


public:

	static void ShowCurrencyCalculatorScreen()
	{
        char Continue = 'y';
        while (Continue == 'y' || Continue == 'Y')
        {
            system("cls");
            _DrawScreenHeader("\t Currency calculator Screen");
            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();
            _PrintCalculationsResults(Amount, CurrencyFrom, CurrencyTo);
            cout << "\n\nDo you want to perform another calculation? y/n ? ";
            cin >> Continue;
        }

	}
};

