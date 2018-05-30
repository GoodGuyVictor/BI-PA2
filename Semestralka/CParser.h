#include <string>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/*! @class CParser
 *  @brief The class parses a string by means of shunting yard algorithm
 */
class CParser
{
private:
    /** Parsed output */
    vector<string>              m_output;
    /** Operator precedence stored in map as key = operator, value = precedence value*/
    unordered_map<char, int>    m_opPrecedence = {
            {'+', 10},
            {'-', 10},
            {'*', 20},
            {'/', 20},
            {'%', 20},
            {'(', 30},
    };

    /**
     * Method parses input string and store the result in m_output container
     * https://en.wikipedia.org/wiki/Shunting-yard_algorithm
     * @param input Input string
     */
    void shuntingYard                   (const string & input);
    /**
     * Determines whether a given token is binary operator
     * @param token The token to be examined
     * @return true if token is a binary operator false otherwise
     */
    bool isOperator                     (const char token) const;
    /**
     * Pops the top element from stack and place it into m_output container
     * @param operatorStack Stack with operators
     */
    void popOperatorFromStackToOutput   (stack<char> & operatorStack);
public:
    /**
     * Default constructor
     */
                    CParser     () = default;
    /**
     * Default destructor
     */
                    ~CParser    () = default;
    /**
     * Method runs shunting yard algorithm and returns parsed input
     * @param input The input to be parsed
     * @return m_output containing parsed input
     */
    vector<string>  parse       (const string & input);
};
