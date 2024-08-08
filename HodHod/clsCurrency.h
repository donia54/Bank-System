#pragma once
#include<iostream>
#include<string>
#include "clsString.h"
#include <vector>
#include <fstream>
using namespace std;

class clsCurrency
{
private:

	enum enMode
	{
		enEmptyMode = 0, enUpdateMode = 1
	};
	enMode _Mode;
	string _Country;
	string _CurrencyCode;
	string _CurrencyName;
	float _Rate;

	static clsCurrency _ConvertCurrencyLineToObject(string Line,string Delim="#//#")
	{
		vector<string> vCurrencyData;
		vCurrencyData = clsString::Split(Line, Delim);

		return clsCurrency(enMode::enUpdateMode, vCurrencyData[0], vCurrencyData[1], vCurrencyData[2],
			stod(vCurrencyData[3]));

	}

	static vector<clsCurrency> _LoadCurrencysDataFromFile()
	{
		vector<clsCurrency>vCurrencys;
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertCurrencyLineToObject(Line);
				vCurrencys.push_back(Currency);
			}
			MyFile.close();
		}
		return vCurrencys;
	}

	static string _ConverCurrencyObjectToLine(clsCurrency Currency, string Delim = "#//#")
	{

		string stCurrencyRecord = "";
		stCurrencyRecord += Currency.GetCountry() + Delim;
		stCurrencyRecord += Currency.GetCurrencyCode() + Delim;
		stCurrencyRecord += Currency.GetCurrencyName() + Delim;
		stCurrencyRecord += to_string(Currency.GetRate());

		return stCurrencyRecord;
	}

	static void _SaveCurrencyDataToFile(vector <clsCurrency> vCurrencys)
	{
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::out);
		string DataLine;
		if (MyFile.is_open())
		{
			for (clsCurrency C : vCurrencys)
			{
				DataLine = _ConverCurrencyObjectToLine(C);
				MyFile << DataLine << endl;
			}
			MyFile.close();
		}
	}

	void _Update()
	{
		vector<clsCurrency> _vCurrencys;
		_vCurrencys = _LoadCurrencysDataFromFile();

		for (clsCurrency& C : _vCurrencys)
		{
			if (C.GetCurrencyCode() == GetCurrencyCode())
			{
				C = *this;
				break;
			}
		}
		_SaveCurrencyDataToFile(_vCurrencys);
	}

	static clsCurrency _GetEmptyCurrencyObject()
	{
		return clsCurrency(enMode::enEmptyMode, "", "", "", 0);
	}
	


public:

	clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
	{
		_Mode = Mode;
		_Country = Country;
		_CurrencyCode = CurrencyCode;
		_CurrencyName = CurrencyName;
		_Rate = Rate;
	}

	bool IsEmpty()
	{
		return (_Mode == enMode::enEmptyMode);
	}

	string GetCountry()
	{
		return _Country;
	}

	string GetCurrencyCode()
	{
		return _CurrencyCode;
	}

	string GetCurrencyName()
	{
		return _CurrencyName;
	}

	float GetRate()
	{
		return _Rate;
	}

	void UpdateRate(float NewRate)
	{
		_Rate = NewRate;
		_Update();
	}

	static clsCurrency FindByCode(string CurrencyCode)
	{
		CurrencyCode = clsString::UpperAllString(CurrencyCode);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertCurrencyLineToObject(Line);
				if (Currency.GetCurrencyCode() == CurrencyCode)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();

		}
     	return _GetEmptyCurrencyObject();
	}

	static clsCurrency FindByCountry(string Country)
	{
		Country = clsString::UpperAllString(Country);
		fstream MyFile;
		MyFile.open("Currencies.txt", ios::in);
		if (MyFile.is_open())
		{
			string Line;
			while (getline(MyFile, Line))
			{
				clsCurrency Currency = _ConvertCurrencyLineToObject(Line);
				if (clsString::UpperAllString(Currency.GetCountry()) == Country)
				{
					MyFile.close();
					return Currency;
				}
			}
			MyFile.close();
		}
		return _GetEmptyCurrencyObject();
	}

	static bool IsCurrencyExist(string CurrencyCode)
	{
		clsCurrency C = clsCurrency::FindByCode(CurrencyCode);
		return (!C.IsEmpty());
	}

	static vector <clsCurrency> GetCurrenciesList()
	{
		return  _LoadCurrencysDataFromFile();
	}

	float ConvertToUSD(float Amount)
	{
		return (float)(Amount / GetRate());
	}
		
	float ConvertToOtherCurrency(float Amount, clsCurrency CurrencyTo)
	{
		float AmountInUSD= Amount / GetRate();

		if (CurrencyTo.GetCurrencyCode() == "USD")
		{
			return AmountInUSD;
		}
		return (float)(AmountInUSD * CurrencyTo.GetRate());
	}


};

