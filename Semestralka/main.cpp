#include <iostream>
#include <iomanip>
#include <sstream>
#include <list>
#include <string>
#include <vector>
#include <typeinfo>
#include <algorithm>
#include <cstring>

using namespace std;

class COperatorStack
{

};


class COperand
{
protected:
    string m_value;

public:
    COperand() = default;
    explicit COperand(const string & val) : m_value(val) {};
    virtual ~COperand() = default;
    COperand & operator+(const COperand & other);
//    template <typename T>
//    virtual T getValue() const;
};


class CInteger : public COperand
{
public:
    explicit CInteger(const string & val) : COperand(val) {}
};


class CDecimal : public COperand
{
    explicit CDecimal(const string & val) : COperand(val) {}

};


class CVariable : public COperand
{
private:
    string m_name;
public:
    explicit CVariable(const string & name, const string & val) : COperand(val), m_name(name) {}
};


class CParser
{
private:
    vector<string> m_output;

    void shuntingYard(const string & input);

public:
    CParser() = default;
    ~CParser() = default;
    void readInput();
};

void CParser::readInput()
{
    string input;

    cout << ">";
    getline(cin, input, '\n');
    shuntingYard(input);
}

void CParser::shuntingYard(const string &input)
{

}


class CCalculator
{
private:
    vector<CVariable> m_variables;
    vector<string> m_history;

    void removeWhiteSpaces(string &str);

public:
    CCalculator() { cout << "Welcome to super high precision calculator! Have fun! =)" << endl; }
    void run();
    void readInput();
};

void CCalculator::run()
{
    CParser parser;

    readInput();
//    while(true)
//    {
//        parser.readInput();
//    }
}

void CCalculator::readInput()
{
    string input;

    cout << ">";
    getline(cin, input, '\n');
    removeWhiteSpaces(input);

    cout << "Read input: " << input;

    //adding new variable
    if(input.find('=') != string::npos)
    {
        char * p;
        p = strtok((char*)input.c_str(), "=");
        string name(p);
        p = strtok(NULL, "=");
        string val(p);
        m_variables.emplace_back(CVariable(name, val));
    }
}

void CCalculator::removeWhiteSpaces(string &str)
{
    for (auto it = str.begin(); it < str.end(); it++)
        if (*it == ' ')
            str.erase(it);
}

void extractInt(const string & str);

int main()
{



//    string sinput("53.345747");
//    string::size_type sz;
//    double dinput = stod(sinput);
//
//    cout << dinput;
//
//    do
//    {
//        getline(cin, input, '\n');
//        cout << input << endl;
//        extractInt(input);
//
//    } while(input != "quit");
//
//
    CCalculator calc;
    calc.run();

    return 0;
}

void extractInt(const string & str)
{
    stringstream ss;
    vector<int> tmpCoords;

    /* Storing the whole string into string stream */
    ss << str;

    /* Running loop till the end of the stream */
    string temp;
    int found;
    while (!ss.eof()) {

        /* extracting word by word from stream */
        ss >> temp;

        /* Checking the given word is integer or not */
        if (stringstream(temp) >> found) {
            tmpCoords.push_back(found);
        }
    }
    cout << "extracted ints:" << endl;
    for (auto &it : tmpCoords)
        cout << it << " ";
}