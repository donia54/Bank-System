#include <iostream>
#include"clsBankClient.h"
#include"clsInputValidate.h"
#include"clsLoginScreen.h"
#include"clsUtil.h"
#include<fstream>
using namespace std;

int main()
{
	srand((unsigned)time(NULL));
	while (true)
	{
		if (!clsLoginScreen::ShowLoginScreen())
		{
			break;
		}
	}
	



}