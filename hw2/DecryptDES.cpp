#include <iostream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::string;

string DecryptDES(string key, string cipherText);

int main(int argc, char *argv[])
{
    // �� cin �� argv ��J����A�p�G key �� cipherText �����ūh�I�s DecryptDES�]���b�Τ�K���ա^
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


