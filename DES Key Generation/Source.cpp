#include <iostream>
#include <string>
#include <iomanip>
//#include <ostream>
#include <sstream>
#include <bitset>

using namespace std;


char getHexCharacter(std::string str)
{
	if (str.compare("1111") == 0) return 'F';
	else if (str.compare("1110") == 0) return 'E';
	else if (str.compare("1101") == 0) return 'D';
	else if (str.compare("1100") == 0) return 'C';
	else if (str.compare("1011") == 0) return 'B';
	else if (str.compare("1010") == 0) return 'A';
	else if (str.compare("1001") == 0) return '9';
	else if (str.compare("1000") == 0) return '8';
	else if (str.compare("0111") == 0) return '7';
	else if (str.compare("0110") == 0) return '6';
	else if (str.compare("0101") == 0) return '5';
	else if (str.compare("0100") == 0) return '4';
	else if (str.compare("0011") == 0) return '3';
	else if (str.compare("0010") == 0) return '2';
	else if (str.compare("0001") == 0) return '1';
	else if (str.compare("0000") == 0) return '0';

}

int main()
{   
	int PC1 [8][7] = { 57, 49, 41, 33, 25, 17, 9, 1, 58, 50, 42, 34, 26, 18,
10, 2, 59, 51, 43, 35, 27, 19, 11, 3, 60, 52, 44, 36, 63, 55, 47, 39, 31, 23,
15, 7, 62, 54, 46, 38, 30, 22, 14, 6, 61, 53, 45, 37, 29, 21, 13, 5, 28, 20, 12, 4 };

	int PC2 [6][8] = { 14, 17, 11, 24, 1, 5, 3, 28, 15, 6, 21,
		10, 23, 19, 12, 4, 26, 8, 16, 7, 27, 20, 13, 2, 
		41, 52, 31, 37, 47, 55, 30, 40, 51, 45, 33, 48, 44, 49, 39, 56, 34, 53, 46, 42, 50, 36, 29, 32 };

	int Rotations [16]={ 1, 1, 2, 2, 2, 2, 2, 2, 1, 2, 2, 2, 2, 2, 2, 1 };


	
//	cin.ignore();  //ignores an end of line character 
	string input;
	getline(cin, input);

	//transform hex to binary
	string str;

	for (int o = 0; o<input.length() ; o++)
	{
		char s = input[o];
		stringstream ss;
		ss << hex << s;
		unsigned n;
		ss >> n;  // n is where we store the hex representation da elli fahmah , not 100% sure 
		bitset<4> b(n);
		str += b.to_string();
		//cout << str;
		
		//str is 64 bit 

	}

	//cout << "**" << endl;

	//first we need to know the order in the perm table
	//second we get the str[index in the str which is equal to that order-1] because the str starts from 0 not 1
	int index;
	string str3;
	string str2;
	for (int i = 0; i<8; i++)
	{
		for (int j = 0; j < 7; j++)
		{
			index = PC1[i][j];
			str3 = str[index - 1];
			str2 += str3;

		}
	//	cout << str2 << endl;
		


	}
	// str2 is 56 bit 
	//the next steps will be done 16 times
	//each time we should divide a 56-bit string into 2 parts 28 and 28 then applying the rotations then
	//combining them again to go to the PC2 and the next round

	for (int round = 0; round < 16; round++)
	{

		string left = str2.substr(0, 28);
		string right = str2.substr(28, 55);
	//	cout << left.length() << endl;
		//cout << right.length() << endl;

	//	cout << "left = " << left << endl ;
	//	cout << "right = " << right << endl;

		for (int rot = 0; rot < Rotations[round]; rot++)
		{
			char first_left = left[0];
			char first_right = right[0];
			for (int s = 1; s < 28; s++)
			{
				left[s - 1] = left[s];
				//cout << "s = " << s <<endl;
				right[s - 1] = right[s];
				//cout << "s = " << s<<endl;
			}
			left[27] = first_left;

			right[27] = first_right;
			//cout << "rotation" << Rotations[round];
			//cout << "left = " << left << endl;
			//cout << "right = " << right << endl;

		}
		//we should combine the left and right again
		str2 = left + right;
		//cout << left.length() << endl;
		//cout << right.length() << endl;

		//cout << "left + right = " << str2 << endl ;
		//cout << str2.length() << endl;
		// str2 will go to 2 paths to next round and to PC2 


		int index;
		string str3;
		string key;
		for (int i = 0; i<6; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				index = PC2[i][j];
				str3 = str2[index - 1];
				key += str3;

			}
			//	cout << str2 << endl;

			

		}
		//cout << key << "%%%%%%%%%%%"<< endl;
		string final_key; 
		int k = 0;
		for (int i=0;i<12;i++)
		{
			
			string sub_key = key.substr(k,4);
			char hex_char = getHexCharacter(sub_key);
			final_key +=  hex_char;
			k += 4;
		//	cout << sub_key << "   HOLA" << endl;
		}
		
		cout << final_key;
		cout << endl;
	}
	
	system("pause");
}

