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

    int capsLen = capsLocation.size();

    if (capsLen == 0)
    {
        return newLine; // if there are no caps, no modifications are made
    }

    for (i = 0; i < capsLen; i++)
    {
        capsLocation.at(i) += rotation; // adjust caps locations by their rotation value
    }

    for (i = 0; i < len; i++)
    {
        newLine.at(i) = tolower(newLine.at(i)); // make all letters lowercase
    }

    for (i = 0; i < capsLen; i++)
    {
        newLine.at(capsLocation.at(i)) = toupper(newLine.at(capsLocation.at(i))); // make letters at caps locations uppercase
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