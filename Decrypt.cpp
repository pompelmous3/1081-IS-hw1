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
    return "caesar called";
}
string playfair(string key, string cipherText)
{
    return "playfair called";
}
string vernam(string key, string cipherText)
{
    return "vernam called";
}
string row(string key, string cipherText)
{
    return "row called";
}
string railFence(string key, string cipherText)
{
    return "rail fence called";
}