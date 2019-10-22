#include<iostream>
#include<string>
#include<vector>
using namespace std;

//initial permutation vector
vector<int> IP = {
58, 50, 42, 34, 26, 18, 10, 2,
60, 52, 44, 36, 28, 20, 12, 4,
62, 54, 46, 38, 30, 22, 14, 6,
64, 56, 48, 40, 32, 24, 16, 8,
57, 49, 41, 33, 25, 17,  9, 1,
59, 51, 43, 35, 27, 19, 11, 3,
61, 53, 45, 37, 29, 21, 13, 5,
63, 55, 47, 39, 31, 23, 15, 7
};

vector<int> IPinverse =
{
40, 8 , 48, 16, 56, 24, 64, 32,
39, 7 , 47, 15, 55, 23, 63, 31,
38, 6 , 46, 14, 54, 22, 62, 30,
37, 5 , 45, 13, 53, 21, 61, 29,
36, 4 , 44, 12, 52, 20, 60, 28,
35, 3 , 43, 11, 51, 19, 59, 27,
34, 2 , 42, 10, 50 ,18, 58, 26,
33, 1 , 41, 9 , 49, 17, 57, 25
};

vector<int> PC_1 =
{
57, 49, 41, 33, 25, 17, 9,
1 , 58, 50, 42, 34, 26, 18,
10, 2 , 59, 51, 43, 35, 27,
19, 11, 3 , 60, 52, 44, 36,
63, 55, 47, 39, 31, 23, 15,
7 , 62, 54, 46, 38, 30, 22,
14, 6 , 61, 53, 45, 37, 29,
21, 13, 5 , 28, 20, 12, 4
};

vector<int> PC_2 =
{
14, 17, 11, 24, 1 , 5 ,
3 , 28, 15, 6 , 21, 10,
23, 19, 12, 4 , 26, 8 ,
16, 7 , 27, 20, 13, 2 ,
41, 52, 31, 37, 47, 55,
30, 40, 51, 45, 33, 48,
44, 49, 39, 56, 34, 53,
46, 42, 50, 36, 29, 32
};

vector<int> E =
{
32, 1 , 2 , 3 , 4 , 5 ,
4 , 5 , 6 , 7 , 8 , 9 ,
8 , 9 , 10, 11, 12, 13,
12, 13, 14, 15, 16, 17,
16, 17, 18, 19, 20, 21,
20, 21, 22, 23, 24, 25,
24, 25, 26, 27, 28, 29,
28, 29, 30, 31, 32, 1
};

int S_box[8][4][16] =
{ {// S1
	14,4,13,1,2,15,11,8,3,10,6,12,5,9,0,7,
	0,15,7,4,14,2,13,1,10,6,12,11,9,5,3,8,
	4,1,14,8,13,6,2,11,15,12,9,7,3,10,5,0,
	15,12,8,2,4,9,1,7,5,11,3,14,10,0,6,13
},
{//S2
	15,1,8,14,6,11,3,4,9,7,2,13,12,0,5,10,
	3,13,4,7,15,2,8,14,12,0,1,10,6,9,11,5,
	0,14,7,11,10,4,13,1,5,8,12,6,9,3,2,15,
	13,8,10,1,3,15,4,2,11,6,7,12,0,5,14,9
},
{//S3
	10,0,9,14,6,3,15,5,1,13,12,7,11,4,2,8,
	13,7,0,9,3,4,6,10,2,8,5,14,12,11,15,1,
	13,6,4,9,8,15,3,0,11,1,2,12,5,10,14,7,
	1,10,13,0,6,9,8,7,4,15,14,3,11,5,2,12
},
{//S4
	7,13,14,3,0,6,9,10,1,2,8,5,11,12,4,15,
	13,8,11,5,6,15,0,3,4,7,2,12,1,10,14,9,
	10,6,9,0,12,11,7,13,15,1,3,14,5,2,8,4,
	3,15,0,6,10,1,13,8,9,4,5,11,12,7,2,14
},
{//S5
	2,12,4,1,7,10,11,6,8,5,3,15,13,0,14,9,
	14,11,2,12,4,7,13,1,5,0,15,10,3,9,8,6,
	4,2,1,11,10,13,7,8,15,9,12,5,6,3,0,14,
	11,8,12,7,1,14,2,13,6,15,0,9,10,4,5,3
},
{//S6
	12,1,10,15,9,2,6,8,0,13,3,4,14,7,5,11,
	10,15,4,2,7,12,9,5,6,1,13,14,0,11,3,8,
	9,14,15,5,2,8,12,3,7,0,4,10,1,13,11,6,
	4,3,2,12,9,5,15,10,11,14,1,7,6,0,8,13
},
{//S7
	4,11,2,14,15,0,8,13,3,12,9,7,5,10,6,1,
	13,0,11,7,4,9,1,10,14,3,5,12,2,15,8,6,
	1,4,11,13,12,3,7,14,10,15,6,8,0,5,9,2,
	6,11,13,8,1,4,10,7,9,5,0,15,14,2,3,12
},
{//S8
	13,2,8,4,6,15,11,1,10,9,3,14,5,0,12,7,
	1,15,13,8,10,3,7,4,12,5,6,11,0,14,9,2,
	7,11,4,1,9,12,14,2,0,6,10,13,15,3,5,8,
	2,1,14,7,4,10,8,13,15,12,9,0,3,5,6,11
} };

vector<int> P =
{
16, 7 , 20, 21, 29, 12, 28, 17,
1 , 15, 23, 26, 5 , 18, 31, 10,
2 , 8 , 24, 14, 32, 27, 3 , 9 ,
19, 13, 30, 6 , 22, 11, 4 , 25
};

string desEncrypt(string plainText, string key);
string PC_1F(string key);
string keyTransform(string preRoundKey, int round);
string leftShift(string preKey, int shiftNumber);
string PC_2F(string shiftedKey);
string hexToBi(string hex);
string initialPermutation(string plain);
string roundF(string plainText, string key);
string f(string pR, string key_48);
string XORstrings(string a, string b);
string sBoxOperation(string p_48, int round);
int biToInt(string bi);
string intToBi(int n);
string PF(string toBePFed);
string IPinverseF(string p);
string biToHex(string bi);

int main() {

	string p, k;
	cin >> p >> k;
	cout << "p : " << p << endl << "k : " << k << endl;

	string cipherText = desEncrypt(p, k);
	cipherText = biToHex(cipherText);

	cout << "0x" << cipherText;
	system("pause");
	return 0;

}

//---------------------------------------------------- desEncrypt ------------------------------------------------

string desEncrypt(string plainText, string key)
{

	// 1 : 去掉前兩位，16 進位轉成 2 進位
	plainText.erase(0, 2);
	key.erase(0, 2);
	//cout << "desEncrypt plainText : " << plainText << endl << "desEncrypt key : " << key << endl;



	plainText = hexToBi(plainText);
	key = hexToBi(key);

	//cout << "desEncrypt plainText after hexToBi : " << plainText << endl << "desEncrypt key after hexToBi : " << key << endl;
	//system("pause");

	// 2 : plainText 做 IP , key 做 PC_1
	plainText = initialPermutation(plainText);
	key = PC_1F(key);

	//cout << "desEncrypt plainText after IP : " << plainText << endl << "desEncrypt key after PC_1 : " << key << endl;
	//system("pause");

	// 3 : 做 16 次 roundF 

	string afterRoundF = roundF(plainText, key);

	afterRoundF = IPinverseF(afterRoundF);
	return afterRoundF;
}

//--------------------------------------------------- PC_1F ------------------------------------------------

string PC_1F(string key)
{
	string PC_1_key = "";
	for (int i = 0; i < PC_1.size(); i++)
	{
		PC_1_key += key[PC_1[i] - 1];
	}
	return PC_1_key;
}

//--------------------------------------------------- keyTransform ------------------------------------------------

string keyTransform(string preRoundKey, int round)
{
	string keyL(preRoundKey, 0, 28);
	string keyR(preRoundKey, 28, 28);

	if (round == 1 || round == 2 || round == 9 || round == 16)
	{//left shift 1 bit
		keyL = leftShift(keyL, 1);
		keyR = leftShift(keyR, 1);
	}
	else
	{
		keyL = leftShift(keyL, 2);
		keyR = leftShift(keyR, 2);
	}

	keyL += keyR;
	return keyL;
}

//--------------------------------------------------- leftShift -------------------------------------------------
//input  : 要做 shift 的 28 bit keyL, keyR 
//output : shift 後的 28 bit

string leftShift(string preKey, int shiftNumber)
{
	string shiftedKey(preKey);

	for (int i = 0; i < shiftedKey.length(); i++)
	{
		if (i + shiftNumber < preKey.length())
		{
			shiftedKey[i] = preKey[i + shiftNumber];
		}
		else// i + shiftNumber >= preKey.length()
		{
			shiftedKey[i] = preKey[i + shiftNumber - preKey.length()];
		}
	}

	return shiftedKey;
}

//--------------------------------------------------- PC_2F ------------------------------------------------
// input  : shift 完的 56-bit key
// output : permuted choice 後的 48-bit key

string PC_2F(string shiftedKey)
{
	string k = "";

	for (int i = 0; i < PC_2.size(); i++)
	{
		k += shiftedKey[PC_2[i] - 1];
	}
	return k;
}

//--------------------------------------------------- hexToBi ------------------------------------------------
// input  : 
// output :

string hexToBi(string hex) {

	string bi = "";
	int bitValue;

	//每一個 hex 的 bit 都擴展成 4 個 bit, push_back 到 bi
	for (int i = 0; i < hex.length(); i++)
	{
		bitValue = hex[i];
		if (bitValue >= 48 && bitValue <= 57)// '0' to '9'
		{
			bitValue -= 48;
		}
		else if (bitValue >= 97 && bitValue <= 102)// 'a' to 'f' (10 to 15)
		{
			bitValue = bitValue - 97 + 10;
		}
		else if (bitValue >= 65 && bitValue <= 70)// 'A' to 'F'
		{
			bitValue = bitValue - 65 + 10;
		}


		bi.push_back(bitValue / 8 + 48);
		bi.push_back((bitValue % 8) / 4 + 48);
		bi.push_back((bitValue % 4) / 2 + 48);
		bi.push_back(bitValue % 2 + 48);
	}
	return bi;
}

//--------------------------------------------------- initialPermutation ------------------------------------------------
// input  : 
// output :

string initialPermutation(string plain) {
	string plainCopy = plain;
	for (int i = 0; i < plain.size(); i++)
	{
		plain[i] = plainCopy[IP[i] - 1];
	}
	return plain;
}

//--------------------------------------------------- roundF -------------------------------------------------
// input  : 傳入 initialPermutation 後的 plainText , 及 PC_1 後的 key
// output : return 做完 16 次 f 的 text , 出去做 finalPermutation

string roundF(string plainText, string key)
{
	/*cout << "roundF plainText : " << plainText << endl << "roundF key : " << key << endl;
	system("pause");*/

	string plainL(""), plainR(""), nextPlainL(""), nextPlainR("");

	string roundKey(key);//56-bit
	string key_48_bit;//48-bit


	for (int i = 1; i <= 16; i++)
	{
		plainL = plainText.substr(0, 32);
		plainR = plainText.substr(32, 32);
		/*cout << "round : " << i << endl;
		cout << "plainText : " << plainText << endl;
		cout << "plainL : " << plainL << endl;
		cout << "plainR : " << plainR << endl;*/

		//key schedule
		roundKey = keyTransform(roundKey, i);//roundKey 做該 round 的 shift, 改動會傳到下一 round
		key_48_bit = PC_2F(roundKey);//key_48_bit 是這 round 跟 plainR 做 f() 的 48-bit key

		cout << "roundKey : " << roundKey << endl;

		nextPlainR = XORstrings(plainL, f(plainR, key_48_bit));
		nextPlainL = plainR;

		plainText = nextPlainL + nextPlainR;
	}

	system("pause");
	return plainText;
}

//--------------------------------------------------- f ------------------------------------------------
// input  : 
// output :

string f(string pR, string key_48)
{
	// expansion
	string plain_48("");
	for (int i = 0; i < E.size(); i++)
	{
		plain_48 += pR[E[i] - 1];
	}

	//Eed pR XOR key_48
	plain_48 = XORstrings(plain_48, key_48);

	// S-box

	string sboxed("");

	for (int i = 1; i <= 8; i++)
	{
		sboxed += sBoxOperation(plain_48, i);
	}

	sboxed = PF(sboxed);
	return sboxed;
}

//--------------------------------------------------- XORstrings ------------------------------------------------
// input  : 
// output :

string XORstrings(string a, string b)
{
	string result("");
	if (a.length() == b.length())
	{
		for (int i = 0; i < a.length(); i++)
		{
			result += ((a[i] - 48) ^ (b[i] - 48)) + 48;
		}
		return result;
	}
	else
	{
		cout << "XORstrings two strings are not the same size" << endl;
		return "";
	}
}

string sBoxOperation(string p_48, int round)
{
	string subStr = p_48.substr((round - 1) * 6, 6);

	string rowStr = subStr.substr(0, 1) + subStr[5];//第一個和最後一個組成 row string
	string columnStr = subStr.substr(1, 4);
	string resultStr;
	int resultInt;

	int row = biToInt(rowStr);
	int column = biToInt(columnStr);

	resultInt = S_box[round - 1][row][column];
	resultStr = intToBi(resultInt);
	return resultStr;
}

int biToInt(string bi)
{
	int result = bi[bi.length() - 1] - 48;
	for (int i = bi.size() - 2, ex = 1; i >= 0; i--)
	{
		result += (bi[i] - 48) * pow(2, ex);
		ex++;
	}
	return result;
}

string intToBi(int n)
{//4 bit
	string s("");
	s.push_back(n / 8 + 48);
	s.push_back((n % 8) / 4 + 48);
	s.push_back((n % 4) / 2 + 48);
	s.push_back(n % 2 + 48);
	return s;
}

string PF(string toBePFed)
{
	string result("");
	for (int i = 0; i < P.size(); i++)
	{
		result += toBePFed[P[i] - 1];
	}
	return result;
}

string IPinverseF(string p)
{
	string result("");
	for (int i = 0; i < IPinverse.size(); i++)
	{
		result += p[IPinverse[i] - 1];
	}
	return result;
}

string biToHex(string bi)
{
	string hex("");
	string hexBitStr;
	int hexBitInt;
	for (int i = 0; i < bi.size(); i += 4)
	{
		hexBitInt = 0;
		hexBitStr = bi.substr(i, 4);
		hexBitInt = (hexBitStr[0] - 48) * 8 + (hexBitStr[1] - 48) * 4 + (hexBitStr[2] - 48) * 2 + (hexBitStr[3] - 48);
		if (hexBitInt >= 0 && hexBitInt <= 9)
		{
			hex.push_back(48 + hexBitInt);
		}
		else// 10 ~ 15 -> A ~ F
		{
			hex.push_back(65 + hexBitInt - 10);
		}
	}
	return hex;
}