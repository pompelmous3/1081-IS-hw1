#include <iostream>
#include <string>
using namespace std;
string caesar(string key, string cipherText);
string playfair(string key, string cipherText);
string vernam(string key, string cipherText);
string row(string key, string cipherText);
string railFence(string key, string cipherText);

int main(int argc, char *argv[]) {

    // input
    const string CIPHER = argv[1], KEY = argv[2], CIPHER_TEXT = argv[3];
    string plainText;

    if (CIPHER == "caesar")
    {
        plainText = caesar(KEY, CIPHER_TEXT);
    }
    else if (CIPHER == "playfair")
    {
        plainText = playfair(KEY, CIPHER_TEXT);
    }
    else if (CIPHER == "vernam")
    {
        plainText = vernam(KEY, CIPHER_TEXT);
    }
    else if (CIPHER == "row")
    {
        plainText = row(KEY, CIPHER_TEXT);
    }
    else if (CIPHER == "rail_fence")
    {
        plainText = railFence(KEY, CIPHER_TEXT);
    }

    // output
    cout << plainText;
}

string caesar(string key, string cipherText)
{
	int k = stoi(key);
	for (int i = 0; i < cipherText.length(); i++)
	{
		if (cipherText[i] == 32)
		{
			continue;
		}
		else
		{
			cipherText[i] = ((cipherText[i] - 65) - k + 26) % 26 + 97;
		}
	}
    return cipherText;
}
string playfair(string key, string cipherText)
{
    return "playfair called";
}
string vernam(string key, string cipherText)
{
	string autoKey(key), plainText(cipherText);

	for (int i = 0; i < plainText.length(); i++)
	{
		if (cipherText[i] == 32)
		{
			continue;
		}
		else
		{
			plainText[i] = ((cipherText[i] - 65) ^ (autoKey[i] - 65)) + 97;

			autoKey.push_back(((cipherText[i] - 65) ^ (autoKey[i] - 65)) + 65);
		}
	}
	return plainText;
}
string row(string key, string cipherText)
{
    return "row called";
}
string railFence(string key, string cipherText)
{
    return "rail fence called";
}