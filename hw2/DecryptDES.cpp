#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
using namespace std;

string HexToBin(string hex);
string BinToHex(string bin);
string DecryptDES(string key, string cipherText);
vector<string> GenerateKeys(string key);
string PC(int type, string text);
string Feistel(string key, string text);
string Expansion(string text);
string exclusiveOR(string text1, string text2);
string Substitution(int digit, string text);
string DecToBin(int dec);
string Permutation(string text);

const int ipVector[64] = { 58, 50, 42, 34, 26, 18, 10, 2,
                           60, 52, 44, 36, 28, 20, 12, 4,
                           62, 54, 46, 38, 30, 22, 14, 6,
                           64, 56, 48, 40, 32, 24, 16, 8,
                           57, 49, 41, 33, 25, 17,  9, 1,
                           59, 51, 43, 35, 27, 19, 11, 3,
                           61, 53, 45, 37, 29, 21, 13, 5,
                           63, 55, 47, 39, 31, 23, 15, 7 },
    fpVector[64] = { 40, 8 , 48, 16, 56, 24, 64, 32,
                    39, 7 , 47, 15, 55, 23, 63, 31,
                    38, 6 , 46, 14, 54, 22, 62, 30,
                    37, 5 , 45, 13, 53, 21, 61, 29,
                    36, 4 , 44, 12, 52, 20, 60, 28,
                    35, 3 , 43, 11, 51, 19, 59, 27,
                    34, 2 , 42, 10, 50 ,18, 58, 26,
                    33, 1 , 41, 9 , 49, 17, 57, 25 },
    PC1Vector[56] = { 57, 49, 41, 33, 25, 17, 9,
                        1 , 58, 50, 42, 34, 26, 18,
                        10, 2 , 59, 51, 43, 35, 27,
                        19, 11, 3 , 60, 52, 44, 36,
                        63, 55, 47, 39, 31, 23, 15,
                        7 , 62, 54, 46, 38, 30, 22,
                        14, 6 , 61, 53, 45, 37, 29,
                        21, 13, 5 , 28, 20, 12, 4 },
    PC2Vector[48] = { 14, 17, 11, 24, 1 , 5 ,
                        3 , 28, 15, 6 , 21, 10,
                        23, 19, 12, 4 , 26, 8 ,
                        16, 7 , 27, 20, 13, 2 ,
                        41, 52, 31, 37, 47, 55,
                        30, 40, 51, 45, 33, 48,
                        44, 49, 39, 56, 34, 53,
                        46, 42, 50, 36, 29, 32 },
    EVector[48] = { 32, 1 , 2 , 3 , 4 , 5 ,
                    4 , 5 , 6 , 7 , 8 , 9 ,
                    8 , 9 , 10, 11, 12, 13,
                    12, 13, 14, 15, 16, 17,
                    16, 17, 18, 19, 20, 21,
                    20, 21, 22, 23, 24, 25,
                    24, 25, 26, 27, 28, 29,
                    28, 29, 30, 31, 32, 1 },
    box[8][4][16] = {
        {// S1
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
        }
},
    PVector[32] = { 16, 7 , 20, 21, 29, 12, 28, 17,
                1 , 15, 23, 26, 5 , 18, 31, 10,
                2 , 8 , 24, 14, 32, 27, 3 , 9 ,
                19, 13, 30, 6 , 22, 11, 4 , 25 };

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
        key = HexToBin(key.substr(2));
        cipherText = HexToBin(cipherText.substr(2));
        string plainText = BinToHex(DecryptDES(key, cipherText));
        std::transform(plainText.begin(), plainText.end(), plainText.begin(), ::tolower);

        // 印出結果
        cout << "0x" + plainText;
    }
}

string HexToBin(string hex)
{
    string result;

    for (int i = 0; i < hex.length(); i++)
    {
        switch (hex[i])
        {
        case '0':
            result += "0000";
            break;
        case '1':
            result += "0001";
            break;
        case '2':
            result += "0010";
            break;
        case '3':
            result += "0011";
            break;
        case '4':
            result += "0100";
            break;
        case '5':
            result += "0101";
            break;
        case '6':
            result += "0110";
            break;
        case '7':
            result += "0111";
            break;
        case '8':
            result += "1000";
            break;
        case '9':
            result += "1001";
            break;
        case 'A':
            result += "1010";
            break;
        case 'B':
            result += "1011";
            break;
        case 'C':
            result += "1100";
            break;
        case 'D':
            result += "1101";
            break;
        case 'E':
            result += "1110";
            break;
        case 'F':
            result += "1111";
            break;
        }
    }

    return result;
}

string BinToHex(string bin)
{
    string result;
    for (int i = 0; i < bin.length(); i += 4)
    {
        int tempValue = 0;
        for (int j = 0; j < 4; j++)
        {
            if (bin[i + j] == '1')
            {
                tempValue += pow(2, 3 - j);
            }
        }
        if (tempValue < 10)
        {
            result.push_back(static_cast<char>(tempValue + '0'));
        }
        else
        {
            result.push_back(static_cast<char>(tempValue - 10 + 'A'));
        }
    }

    return result;
}

string DecryptDES(string key, string cipherText)
{
    // IP
    string text;
    for (int i = 0; i < 64; i++)
    {
        text.push_back(cipherText[ipVector[i] - 1]);
    }

    vector<string> subkeys = GenerateKeys(key);
    string left = text.substr(0, 32), right = text.substr(32, 32);

    // Round * 16
    for (int round = 1; round <= 16; round++)
    {
        string temp = right;
        right = exclusiveOR(left, Feistel(subkeys[round-1], right));
        left = temp;
    }
    text = right + left;

    // FP
    string result;
    for (int i = 0; i < 64; i++)
    {
        result.push_back(text[fpVector[i] - 1]);
    }
    return result;
}

vector<string> GenerateKeys(string key)
{
    vector<string> subkeys;
    key = PC(1, key);
    string left = key.substr(0, 28), right = key.substr(28, 28);

    for (int round = 1; round <= 16; round++)
    {
        switch (round)
        {
        case 1:
            key = left + right;
            subkeys.push_back(PC(2, key));
            break;
        case 2:
        case 9:
        case 16:
            left = left.substr(27, 1) + left.substr(0, 27);
            right = right.substr(27, 1) + right.substr(0, 27);
            key = left + right;
            subkeys.push_back(PC(2, key));
            break;
        default:
            left = left.substr(26, 2) + left.substr(0, 26);
            right = right.substr(26, 2) + right.substr(0, 26);
            key = left + right;
            subkeys.push_back(PC(2, key));
            break;
        }
    }
    return subkeys;
}

string PC(int type, string text)
{
    string result;
    if (type == 1)
    {
        for (int i = 0; i < 56; i++)
        {
            result.push_back(text[PC1Vector[i] - 1]);
        }
    }
    else if (type == 2)
    {
        for (int i = 0; i < 48; i++)
        {
            result.push_back(text[PC2Vector[i] - 1]);
        }
    }

    return result;
}

string Feistel(string key, string text)
{
    text = exclusiveOR(Expansion(text), key);

    string result;

    for (int i = 0; i < 8; i++)
    {
        result += Substitution(i + 1, text.substr(i * 6, 6));
    }

    result = Permutation(result);

    return result;
}

string Expansion(string text)
{
    string result;

    for (int i = 0; i < 48; i++)
    {
        result.push_back(text[EVector[i] - 1]);
    }

    return result;
}

string exclusiveOR(string text1, string text2)
{
    string result;
    for (int i = 0; i < text1.length(); i++)
    {
        if (text1[i] == text2[i])
        {
            result.push_back('0');
        }
        else
        {
            result.push_back('1');
        }
    }

    return result;
}

string Substitution(int digit, string text)
{
    int row = 0, column = 0;
    for (int i = 0; i < 6; i++)
    {
        if (text[i] == '1')
        {
            switch (i)
            {
            case 0:
                row += 2;
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                column += pow(2, 4 - i);
                break;
            case 5:
                row += 1;
                break;
            }
        }
    }

    string result = DecToBin(box[digit - 1][row][column]);

    return result;
}

// 將十進位int轉為二進位字串
string DecToBin(int dec)
{
    string result = "";
    for (int i = 0; i < 4; i++)
    {
        result = static_cast<char>((dec % 2) + '0') + result;
        dec /= 2;
    }

    return result;
}

string Permutation(string text)
{
    string result;
    for (int i = 0; i < 32; i++)
    {
        result.push_back(text[PVector[i] - 1]);
    }

    return result;
}