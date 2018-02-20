#include<iostream>
#include<string>
#include <iomanip>
#include <sstream>
#include <vector>
using namespace std;

int main()
{
	string checkValue;
	string frame;
	cout << "Please enter the Frame: \n";
	cin >> frame;
	int length;
	string payload;
	vector<int> message;
	vector<int> totalframe;
	int checksum = 0;
	int checksum2;
	checkValue = frame.substr(0, 4);
	if (checkValue == "004b")
	{
		cout << checkValue << "  ";
		checkValue = frame.substr(4, 4);
		if (checkValue == "0049")
		{
			cout << checkValue << "  ";
			checkValue = frame.substr(8, 8);
			stringstream str;
			str << checkValue;
			str >> hex >> length;
			cout << length << "  ";
			
			int hexadec;
			for (int i = 0; i < (frame.length() - 18); i = i+2)
			{
				checkValue = frame.substr(16+i,2);
				stringstream str;
				str << checkValue;
				str >> hex >> hexadec;
				message.push_back(hexadec);
			}

			for (int i = 0; i < (frame.length() - 2); i = i + 2)
			{
				checkValue = frame.substr(i, 2);
				stringstream str;
				str << checkValue;
				str >> hex >> hexadec;
				checksum += hexadec;
			}
			checkValue = frame.substr(frame.length()-2, 2);
			stringstream str2;
			str2 << checkValue;
			str2 >> hex >> checksum2;
			checksum = checksum % 128;
			if (checksum != checksum2)
			{
				cout << "ERROR";
			}
			{
				for (int i = 0; i < (frame.length() - 18) / 2; i = i++)
				{
					payload = (char)message[i];
					cout << payload;
				}
				cout << "\n";
			}
		}
		else
		{
			cout << "ADDRESS MISMATCH";
		}
	}
	else
	{
		cout << "ADDRESS MISMATCH";
	}
}
