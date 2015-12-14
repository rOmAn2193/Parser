#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

using namespace std;

char token;
bool error = 0;

ofstream outf ("/Users/romanpuzey/Documents/Programming/C++/Recursive-Descent Parser/Recursive-Descent Parser/Output.out");

int expr();
int term();
int factor();
int number();
int digit();
string s;
int cindex = 0;

string response;

void getToken()
{
    if (!error)
    {
        outf << response;
    }
    response.clear();
    outf << endl;
    if(s[cindex] != '\0') outf << "<gettoken> " << s[cindex] << " ";
    token = s[cindex];
    cindex++;
}

int expr()
{
    response += "<exp> ";
    int result = term();
    while (token == '+')
    {
        getToken();
        result += term();
    }
    return result;
}

int term()
{
    response +="<term> " ;
    int result = factor();
    while (token == '*')
    {
        getToken();
        result *= factor();
    }
    return result;
}

int factor()
{
    response += "<factor> ";
    int result;
    if (token == '(' )
    {
        getToken();
        result = expr();
        getToken();
    }
    else
        result = number();
    return result;
}

int number()
{
    response += "<number> ";
    int result = digit();
    while (isdigit(token))
        result = 10 * result + digit();
    return result;
}

int digit()
{
    response += "<digit>";
    int result;
    if (isdigit(token)) {
        result = token - '0';
        getToken();
    }
    else
        error = true;
    return result;
}

void parse()
{
    outf << endl << "<parse>" << " ";
    getToken();
    expr();
    if (!error) outf << "The parse has been completed correctly." << endl;
    else outf << "There was an error in the parse." << endl;
}

int main()
{
    ifstream inf ("/Users/romanpuzey/Documents/Programming/C++/Recursive-Descent Parser/Recursive-Descent Parser/input.txt");
    while (!inf.eof())
    {
        inf >> s;
        cindex=0;
        parse();
    }
    return 0;
}