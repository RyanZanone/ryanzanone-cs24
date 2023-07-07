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
        if (isupper(c))
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
        capsLocation.at(i) = capsLocation.at(i) - len + rotation; // adjust caps locations by their rotation value
    }

    for (i = 0; i < capsLen; i++)
    {
        if (capsLocation.at(i) > len - 1)
        {
            capsLocation.at(i) = (capsLocation.at(i) % len);
        }
        else if (capsLocation.at(i) < 0)
        {
            capsLocation.at(i) = ((capsLocation.at(i)) % len);
        }
    }

    for (i = 0; i < len; i++)
    {
        newLine.at(i) = tolower(newLine.at(i)); // make all letters lowercase
    }

    for (i = 0; i < capsLen; i++)
    {
        if (capsLocation.at(i) < 0)
        {
            newLine.at((len + capsLocation.at(i))) = toupper(newLine.at((len + capsLocation.at(i)))); // go from the end if negative
        }
        else
        {
            newLine.at(capsLocation.at(i)) = toupper(newLine.at(capsLocation.at(i))); // make letters at caps locations uppercase
        }
    }

    return newLine;
}

int main(int argc, char *argv[])
{

    string line;
    int rotation;

    if (argc < 2)
    {
        cout << "Usage: " << argv[0] << "rotation" << endl;
    }

    rotation = stoi(argv[1]);
    getline(cin, line);

    string newLine = rotateCaps(line, rotation);
    cout << newLine << endl;

    return 0;
}