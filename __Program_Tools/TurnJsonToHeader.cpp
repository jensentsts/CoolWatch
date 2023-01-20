#include <bits/stdc++.h>
#include "json/json.h"
using namespace std;

ifstream ifs(".\\TurnJsonToHeader.json");
ofstream ofs(".\\result.h");
string str;
void replace_str(std::string &str, const std::string &before, const std::string &after)
{
    for (std::string::size_type pos(0); pos != std::string::npos; pos += after.length())
    {
        pos = str.find(before, pos);
        if (pos != std::string::npos)
            str.replace(pos, before.length(), after);
        else
            break;
    }
}

int main()
{
    string name;
    cout << "String JSON var name:";
    cin >> name;
    ofs << "const char *" << name << " = {\n";
    while (!ifs.eof())
    {
        getline(ifs, str);
        replace_str(str, "\\", "\\\\");
        replace_str(str, "\"", "\\\"");
        //replace_str(str, "\'", "\\\"");
        ofs << "\"" << str << "\"\n";
    }
    ofs << "};";
    ofs.close();
    ifs.close();
    return 0;
}
