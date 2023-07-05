#include <iostream>
#include <string>
#include <vector>

using namespace std;

string rotateCaps(string &line, int rotation)
{

    string newLine = line;
    int len = line.length();
    vector<int> capsLocation;
    int i;

    for (i = 0; i < len; i++)
    {
        char c = newLine.at(i);
        if (isupper(c) == true)
        {
            capsLocation.push_back(i); // track all locations of capital letters
        }
    }

    if (capsLocation.size() == 0)
    {
        return newLine;
    }

    for (size_t j = 0; j < capsLocation.size(); j++)
    {
        capsLocation.at(j) += rotation;
    }

    for (i = 0; i < len; i++)
    {
        newLine.at(i) = tolower(newLine.at(i));
    }

    for (size_t j = 0; j < capsLocation.size(); j++)
    {
        newLine.at(capsLocation.at(j)) = toupper(newLine.at(capsLocation.at(j)));
    }

    return newLine;
}

int main(int argc, char *argv[])
{

    string line;
    int rotation;

    rotation = stoi(argv[1]);
    getline(cin, line);

    string newLine = rotateCaps(line, rotation);
    cout << newLine << endl;

    return 0;
}