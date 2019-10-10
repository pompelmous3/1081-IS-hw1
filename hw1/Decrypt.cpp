#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <algorithm>
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
    std::transform(plainText.begin(), plainText.end(), plainText.begin(), ::tolower);
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
                position['I'] = pair<int, int>(i, j);
				position['J'] = pair<int, int>(i, j);
            }
            else
            {
                matrix[i][j] = key[k];
                used[static_cast<unsigned>(key[k] - 65)] = true;
                position[key[k]] = pair<int, int>(i, j);
            }
            j = (i < 4 ? j : j + 1);
            i = (i < 4 ? i + 1 : 0);
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
                position['I'] = pair<int, int>(i, j);
				position['J'] = pair<int, int>(i, j);
            }
            else
            {
                matrix[i][j] = static_cast<char>(k + 65);
                used[k] = true;
                position[static_cast<char>(k + 65)] = pair<int, int>(i, j);
            }
            j = (i < 4 ? j : j + 1);
            i = (i < 4 ? i + 1 : 0);
        }
    }

    // 解密
    string result;
    for (int k = 0; k < cipherText.length(); k += 2)
    {
        char letter1 = cipherText[k], letter2 = cipherText[k + 1];
        int i1 = position[letter1].first, j1 = position[letter1].second, i2 = position[letter2].first, j2 = position[letter2].second;
        if (i1 == i2)
        {
            result.push_back(matrix[i1][(j1 - 1 < 0 ? 4 : j1 - 1)]);
            result.push_back(matrix[i1][(j2 - 1 < 0 ? 4 : j2 - 1)]);
        }
        else if (j1 == j2)
        {
            result.push_back(matrix[(i1 - 1 < 0 ? 4 : i1 - 1)][j1]);
            result.push_back(matrix[(i2 - 1 < 0 ? 4 : i2 - 1)][j1]);
        }
        else
        {
            result.push_back(matrix[i2][j1]);
            result.push_back(matrix[i1][j2]);
        }
    }

    return result;
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
    // 依據總字數和key的字數 算出每欄的字數
    string result;
    vector<vector<char>> temp(key.length(), vector<char>());
    vector<int> amount(key.length(), floor(cipherText.length()/key.length()));
    for (int i = 0; i < cipherText.length() % key.length(); i++)
    {
        amount[i]++;
    }

    // 轉換明文和密文對應的欄位
    vector<int> columnIndex(key.length());
    for (int i = 0; i < key.length(); i++)
    {
        columnIndex[static_cast<int>(key[i]-'0')-1] = i;
    }
    
    // 將密文放入欄位
    int k = 0, i=0;
    while (k < cipherText.length())
    {
        temp[columnIndex[i]].push_back(cipherText[k]);
        amount[columnIndex[i]]--;
        if (amount[columnIndex[i]] == 0)
        {
            i++;
        }
        k++;
    }

    // 取出明文
    k = 0, i = 0;
    int j = 0;
    while (k < cipherText.length())
    {
        result.push_back(temp[i][j]);
        j = (i == key.length() - 1 ? j + 1 : j);
        i = (i == key.length() - 1 ? 0 : i + 1);
        k++;
    }

    return result;
}

string railFence(string key, string cipherText)
{
	string plainText("");
	int k = stoi(key);
	int colNum = cipherText.length() / k;
	int r = cipherText.length() % k;//前 r 個 row 都會多一個 column

	vector<vector<char>>v;
	v.resize(k);

	int count = 0;
	for (int i = 0; i < v.size(); i++)
	{
		if (i <= (r - 1))
		{
			for (int j = 0; j < (colNum + 1); j++)
			{
				v[i].push_back(cipherText[count++]);
			}
		}
		else
		{
			for (int j = 0; j < colNum; j++)
			{
				v[i].push_back(cipherText[count++]);
			}
		}
	}

	for (int i = 0; i < colNum; i++)
	{
		for (int j = 0; j < v.size(); j++)
		{
			plainText.push_back(v[j][i]);
		}
	}

	for (int i = 0; i < r; i++)
	{
		plainText.push_back(v[i][colNum]);
	}

	for (int i = 0; i < plainText.size(); i++)
	{
		if (plainText[i] == 32)
		{
			continue;
		}
		else
		{
			plainText[i] = plainText[i] - 65 + 97;
		}
	}

	return plainText;
}