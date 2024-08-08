#pragma once
#include <iostream>
#include<vector>
#include<string>
#include<iomanip>
#include"clsDate.h";
using namespace std;

class clsUtil
{
public :
	enum enCharType { Small = 1, Capital = 2, Digit = 3, Special = 4 ,Mix=5};

    static void  Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int from, int to)
    {
        int randnum = rand() % (to - from + 1) + from;
        return randnum;
    }

    static char GetRandomChar(enCharType charr)
    {
        switch (charr)
        {
        case Small:
            return (char)(RandomNumber(97, 122));
        case Capital:
            return (char)(RandomNumber(65, 90));
        case Digit:
            return (char)(RandomNumber(48, 57));
        case Special:
            return (char)(RandomNumber(33, 47));
        default:
            return (char)(RandomNumber(65, 90));
            break;
        }
    }

    static string GeneratWord(enCharType charr, int length)
    {
        string word = "";
        for (int i = 0; i < length; i++)
        {
            word += GetRandomChar(charr);
        }
        return word;
    }

    static string GeneratKey(enCharType ch=Capital)
    {
        string key = "";
        key += GeneratWord(ch, 4) + '-';
        key += GeneratWord(ch, 4) + '-';
        key += GeneratWord(ch, 4) + '-';
        key += GeneratWord(ch, 4);
        return key;
    }

    static void PrintGenerataedKeys(int number, enCharType ch = Capital)
    {
        for (int i = 1; i <= number; i++)
        {
            cout << "Key[" << i << "]:" << GeneratKey(ch) << endl;
        }
    }

    static void FillArrayRandomly(int arr[100], int size,int from,int to)
    {
        for (int i = 0; i < size; i++)
        {
            arr[i] = RandomNumber(from, to);
        }
    }

    static void FillArrayWithRandomWords(string arr[100], int size, enCharType ch, short Wordlength)
    {
        for (int i = 0; i < size; i++)
            arr[i] = GeneratWord(ch, Wordlength);

    }

    static void FillArrayWithRandomKeys(string arr[100], int arrLength, enCharType CharType)
    {
        for (int i = 0; i < arrLength; i++)
            arr[i] = GeneratKey(CharType);
    }

    static void Swap(int& a, int& b)
    {
        int temp;
        temp = a;
        a = b;
        b = temp;
    }

    static void Swap(double& a, double& b)
    {
        double temp;
        temp = a;
        a = b;
        b = temp;
    }

    static void Swap(bool& a, bool& b)
    {
        bool temp;
        temp = a;
        a = b;
        b = temp;
    }

    static void Swap(char& a, char& b)
    {
        char temp;
        temp = a;
        a = b;
        b = temp;
    }

    static void Swap(string& a, string& b)
    {
        string temp;
        temp = a;
        a = b;
        b = temp;
    }

    static void Swap(clsDate& a, clsDate& b)
    {
        clsDate::SwapDates(a, b);
    }

   static void ShufflrArray(int arr[100], int size)
    {
        for (int i = 0; i < size; i++)
        {
            Swap(arr[RandomNumber(1, size) - 1], arr[RandomNumber(1, size) - 1]);
        }
    }

   static string  Tabs(short n)
   {
       string t = "";

       for (int i = 1; i < n; i++)
       {
           t = t + "\t";
           cout << t;
       }
       return t;
   }

   static double MyAbs(double num)
   {
       if (num > 0)
           return num;
       return num * -1;
   }
   static double GetFractionPart(double num)
   {
       return num - (int)num;
   }
   static int MyRound(double num)
   {
       int INTpart = (int)num;
       double Fractionpart = GetFractionPart(num);
       if (MyAbs(Fractionpart) >= .5)
       {
           if (num > 0)
               return ++INTpart;
           else
               return --INTpart;
       }
       return INTpart;
   }
   static int MyFloor(double num)
   {
       if (num > 0)
           return int(num);
       else
           return int(num) - 1;
   }
   static int MyCeol(double num)
   {
       if (MyAbs(GetFractionPart(num)) > 0)
       {
           if (num > 0)
               return int(num) + 1;
           return int(num);
       }
       return num;
   }
   static int MySqrt(double num)
   {
       return pow(num, 0.5);
   }

   static string EncryptText(string Text, short EncryptionKey=2)
   {

       for (int i = 0; i <= Text.length(); i++)
       {

           Text[i] = char((int)Text[i] + EncryptionKey);

       }
       return Text;
   }

   static string  DecryptText(string Text, short EncryptionKey=2)
   {
       for (int i = 0; i <= Text.length(); i++)
       {

           Text[i] = char((int)Text[i] - EncryptionKey);

       }
       return Text;
   }

   static string NumberToText(int Number)
   {

       if (Number == 0)
       {
           return "";
       }

       if (Number >= 1 && Number <= 19)
       {
           string arr[] = { "", "One","Two","Three","Four","Five","Six","Seven",
       "Eight","Nine","Ten","Eleven","Twelve","Thirteen","Fourteen",
         "Fifteen","Sixteen","Seventeen","Eighteen","Nineteen" };

           return  arr[Number] + " ";

       }

       if (Number >= 20 && Number <= 99)
       {
           string arr[] = { "","","Twenty","Thirty","Forty","Fifty","Sixty","Seventy","Eighty","Ninety" };
           return  arr[Number / 10] + " " + NumberToText(Number % 10);
       }

       if (Number >= 100 && Number <= 199)
       {
           return  "One Hundred " + NumberToText(Number % 100);
       }

       if (Number >= 200 && Number <= 999)
       {
           return   NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
       }

       if (Number >= 1000 && Number <= 1999)
       {
           return  "One Thousand " + NumberToText(Number % 1000);
       }

       if (Number >= 2000 && Number <= 999999)
       {
           return   NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
       }

       if (Number >= 1000000 && Number <= 1999999)
       {
           return  "One Million " + NumberToText(Number % 1000000);
       }

       if (Number >= 2000000 && Number <= 999999999)
       {
           return   NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
       }

       if (Number >= 1000000000 && Number <= 1999999999)
       {
           return  "One Billion " + NumberToText(Number % 1000000000);
       }
       else
       {
           return   NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
       }


   }

};

