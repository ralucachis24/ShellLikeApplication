#ifndef UTILS_H
#define UTILS_H

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

#define PIPE '|'
#define REDI '>'
#define SPACE ' '

class Utils
{

public:
    /*Simply splits the source at delimiter and builts a vector of results */
    static vector<string> split(string source, char delimiter = SPACE)
    {

        vector<string> res;
        string token;
        stringstream sstream(source);

        while (getline(sstream, token, delimiter))
            res.push_back(token);
        return res;
    }

    /* Create commands each in it's own vector of strings
       Return the built vector of vector strings */
    static vector<vector<string>> parseLineCommands(string in)
    {
        vector<vector<string>> res;

        vector<string> splitAtPipe = split(in, PIPE);

        for (string s : splitAtPipe)
        {
            vector<string> splitAtSpace = stripSpaces(split(s, SPACE));
            res.push_back(splitAtSpace);
        }
        //cout << res.size() << endl;
        return res;
    }

    static char **execFood(string source)
    {
        return nullptr;
    }

private:
    /* Strip all spaces from a command token given as a vector of tokens
       Return the new built command tokens */
    static vector<string> stripSpaces(vector<string> in)
    {
        vector<string> res;

        for (string token : in)
        {
            string stripped;

            for (char ch : token)
                if (ch != SPACE)
                    stripped.push_back(ch);

            if (stripped.size() > 0)
                res.push_back(stripped);
        }
        return res;
    }
    Utils();
};

#endif