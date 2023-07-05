#include <iostream>
#include <string>
#include <vector>

using namespace std;

string rotateCaps(string &line, int rotation)
{

    string newLine = line;
    int len = line.length();
    vector<int> capsLocation;
    unsigned int i;

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

    for (i = 0; i < capsLocation.size(); i++)
    {
        capsLocation.at(i) += rotation;
    }

    for (i = 0; i < len; i++)
    {
        newLine.at(i) = tolower(newLine.at(i));
    }

    for (i = 0; i < capsLocation.size(); i++)
    {
        newLine.at(capsLocation.at(i)) = toupper(newLine.at(capsLocation.at(i)));
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