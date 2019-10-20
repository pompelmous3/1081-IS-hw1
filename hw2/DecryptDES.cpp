#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

string DecryptDES(string key, string cipherText);

int main(int argc, char *argv[])
{
    // 用 cin 或 argv 輸入測資，如果 key 及 cipherText 不為空則呼叫 DecryptDES（防呆及方便測試）
    string key, cipherText, plainText;
    switch (argc)
    {
    case 1:
        cin >> key >> cipherText;
        break;
    case 3:
        key = argv[1];
        cipherText = argv[2];
        break;
    }
    if (key.empty() == false && cipherText.empty() == false)
    {
        cout << DecryptDES(key, cipherText);
    }
}

string DecryptDES(string key, string cipherText)
{
    string result;

    result = "DecryptDES called";

    return result;
}


