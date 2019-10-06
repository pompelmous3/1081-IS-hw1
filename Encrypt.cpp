#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
using namespace std;
string caesar(string key, string plainText);
string playfair(string key, string plainText);
string vernam(string key, string plainText);
string row(string key, string plainText);
string railFence(string key, string plainText);

int main(int argc, char *argv[]) {

    // input
    const string CIPHER = argv[1], KEY = argv[2], PLAIN_TEXT = argv[3];
    //const string CIPHER = "playfair", KEY = "COMP", PLAIN_TEXT = "doyourbestandthenletgo"; // 測試用
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
    // 將 key 填入 matrix
    vector<bool> used(26, false);
    vector<vector<char>> matrix(5, vector<char>(5));
    map<char, pair<int, int>> position;

    int i = 0, j = 0, k = 0;
    while (k < key.length())
    {
        if (used[static_cast<unsigned>(key[k] - 65)] == false)
        {
            if (key[k] == 'I' || key[k] == 'J')
            {
                matrix[i][j] = 'I';
                used[8] = true;
                used[9] = true;
                position['I'] = pair<int, int>(i,j);
            }
            else
            {
                matrix[i][j] = key[k];
                used[static_cast<unsigned>(key[k] - 65)] = true;
                position[key[k]] = pair<int, int>(i,j);
            }
            if (i < 4)
            {
                i++;
            }
            else
            {
                i = 0;
                j++;
            }
        }
        k++;
    }
    for (int k = 0; k < 26; k++)
    {
        if (used[k] == false)
        {
            if (k == 8 || k == 9)
            {
                matrix[i][j] = 'I';
                used[8] = true;
                used[9] = true;
                position['I'] = pair<int, int>(i,j);
            }
            else
            {
                matrix[i][j] = static_cast<char>(k + 65);
                used[k] = true;
                position[static_cast<char>(k+65)] = pair<int, int>(i,j);
            }
            if (i < 4)
            {
                i++;
            }
            else
            {
                i = 0;
                j++;
            }
        }
    }

    // 加密
    string result;
    std::transform(plainText.begin(), plainText.end(), plainText.begin(), ::toupper);
    for (int k = 0; k < plainText.length(); k += 2)
    {
        char letter1 = plainText[k], letter2 = plainText[k + 1];
        int i1 = position[letter1].first, j1 = position[letter1].second, i2 = position[letter2].first, j2 = position[letter2].second;
        if (i1 == i2)
        {
            result.push_back(matrix[i1][(j1 + 1 > 4 ? 0 : j1 + 1)]);
            result.push_back(matrix[i1][(j2 + 1 > 4 ? 0 : j2 + 1)]);
        }
        else if (j1 == j2)
        {
            result.push_back(matrix[(i1 + 1 > 4 ? 0 : i1 + 1)][j1]);
            result.push_back(matrix[(i2 + 1 > 4 ? 0 : i2 + 1)][j1]);
        }
        else
        {
            result.push_back(matrix[i2][j1]);
            result.push_back(matrix[i1][j2]);
        }
    }

    return result;
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
	int k = stoi(key);
	string cipherText("");

	vector<vector<char>> v;
	v.resize(k);

	int count = 0;
	for (int i = 0; i < plainText.length(); i++)
	{
		v[count].push_back(plainText[i]);
		if (count == k - 1)
		{
			count = 0;
		}
		else
		{
			count++;
		}
	}

	for (int i = 0; i < v.size(); i++)
	{
		for (int j = 0; j < v[i].size(); j++)
		{
			cipherText.push_back(v[i][j]);
		}
	}

	for (int i = 0; i < cipherText.length(); i++)
	{
		if (cipherText[i] == 32)
		{
			continue;
		}
		else
		{
			cipherText[i] = cipherText[i] - 97 + 65;
		}
	}

	return cipherText;
}