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
    return "caesar called";
}
string playfair(string key, string plainText)
{
    return "playfair called";
}
string vernam(string key, string plainText)
{
    return "vernam called";
}
string row(string key, string plainText)
{
    return "row called";
}
string railFence(string key, string plainText)
{
    return "rail fence called";
}