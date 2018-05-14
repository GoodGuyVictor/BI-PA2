#include <string>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

class CParser
{
private:
    vector<string> m_output;
    unordered_map<char, int> m_opPrecedence = {
            {'+', 10},
            {'-', 10},
            {'*', 20},
            {'/', 20},
            {'%', 20},
            {'(', 30},
    };

    void shuntingYard                   (const string &);
    bool isOperator                     (const char) const;
    void popOperatorFromStackToOutput   (stack<char> &);
public:
    CParser() = default;
    ~CParser() = default;
    vector<string> parse(const string &);
};
