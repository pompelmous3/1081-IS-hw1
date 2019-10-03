#include <iostream>
#include <string>
using namespace std;
string caesar(string key, string plainText);
string playfair(string key, string plainText);
string vernam(string key, string plainText);
string row(string key, string plainText);
string railFence(string key, string plainText);

int main(int argc, char *argv[]) {

    // input
    const string CIPHER = argv[1], KEY = argv[2], PLAIN_TEXT = argv[3];
    string cipherText;

    if (CIPHER == "caesar")
    {
        cipherText = caesar(KEY, PLAIN_TEXT);
    }
    else if (CIPHER == "playfair")
    {
        cipherText = playfair(KEY, PLAIN_TEXT);
    }
    else if (CIPHER == "vernam")
    {
        cipherText = vernam(KEY, PLAIN_TEXT);
    }
    else if (CIPHER == "row")
    {
        cipherText = row(KEY, PLAIN_TEXT);
    }
    else if (CIPHER == "rail_fence")
    {
        cipherText = railFence(KEY, PLAIN_TEXT);
    }

    // output
    cout << cipherText;
}

string caesar(string key, string plainText)
{
	int k = std::stoi(key);
	for (int i = 0; i < plainText.length(); i++)
	{
		if (plainText[i] == 32)
		{
			continue;
		}
		else
		{
			plainText[i] = ((plainText[i] - 97) + k) % 26 + 65;
		}
	}

    return plainText;
}
string playfair(string key, string plainText)
{
    return "playfair called";
}
string vernam(string key, string plainText)
{
	string autoKey(key), cipherText(plainText);

	for (int i = 0; i < autoKey.length(); i++)//把 key 都轉成小寫
	{
		autoKey[i] = autoKey[i] - 65 + 97;
	}

	for (int i = key.length(); i < plainText.length(); i++)
	{
		autoKey.push_back(plainText[i - key.length()]);
	}

	for (int i = 0; i < cipherText.length(); i++)
	{
		if (cipherText[i] == 32)
		{
			continue;
		}
		else
		{
			cipherText[i] = ((cipherText[i] - 97) ^ (autoKey[i] - 97)) + 65;
		}
	}
	return cipherText;
}
string row(string key, string plainText)
{
    return "row called";
}
string railFence(string key, string plainText)
{
    return "rail fence called";
}