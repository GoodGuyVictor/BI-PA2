#include <vector>
#include <iostream>
#include <stack>
#include "CVariable.h"
#include "CExpression.h"
#include "Enums.h"

using namespace std;

/*! @class CCalculator
 *  @brief Calculator engine
 */
class CCalculator
{
private:
    /** Set of variables */
    vector<CVariable>   m_variables;
    /** History list */
    vector<string>      m_history;

    /**
     * Reads input from keyboard, creates variable if needed
     * @return 4 options: intput itself if input was math expression,
     * "variable" in case of declaration of new variable,
     * "save" command ment to save current calculator state into file
     * "read" command ment to read up calculator state from the file
     */
    string          readInput               ();
    /**
     * Removes all whitespaces in input string
     * @param input Input from keyboard will be transformed containing no spaces in it
     */
    void            removeWhiteSpaces       (string & input);
    /**
     * The logic itself. Method firstly parses the given input every operand is put into CExpression object
     * and pushed into stack of CExpression objects furthermore. If operator is encountered then two latest
     * operands from stack are taken away, calculated and the result pushed back into the stack
     * @param input Input from keyboard with no whitespaces
     * @return Highly accurate number resulting all the input expression
     */
    CBigNum         calculate               (const string & input);
    /**
     * Stores the math expression taken from keyboard and its result in vector of strings
     * @param input Input math expression (with no whitespaces here)
     * @param result Result of the expression (highly accurate number)
     */
    void            saveHistory             (const string& input, const CBigNum& result);
    /**
     * Determines type of transmitted operand
     * @param operand The operand to be examined
     * @return Enum values one of four types: VAL_INT, VAL_LONG, VAL_VAR, VAL_DEC
     */
    EValType        determineType           (const string& operand) const;
    /**
     * Figures out whether the trensmitted token is binary operator
     * @param token The token to be examined
     * @return true if the token is binary operator false otherwise
     */
    bool            isOperator              (const string& token) const;
    /**
     * Creates the CExpression object of corresponding type of given operand and pushes it into the stack of
     * expressions
     * @param operand The operand to be put into CExpression object and pushed into stack
     * @param stack Stack of expressions
     */
    void            pushToStack             (const string & operand, stack<CExpression*> & stack) const;
    /**
     * Performs operation over two operands
     * @param lVal Lef hand operand
     * @param rVal Right hand operand
     * @param op Operator operation of which is to be carried out
     * @return Resulting expression of operation over two operands
     */
    CExpression *   performOperation        (CExpression* lVal, CExpression* rVal, const string& op);
    /**
     * Method examines whether a given variable name contains illegal characters
     * @param varName Variable name to be examined
     * @return true if there is at least one illegal character false otherwise
     */
    bool            containIllegalChar      (const string & varName) const;
    /**
     * Takes the input and split it at the equality sign for variable name and variable value.
     * In case the variable name is new creates a new variable with such name and value and adds it
     * into variables list otherwise reassign the existing variable
     * @param input Input to be processed
     */
    void            addVariable             (std::string input);
    /**
     * Validates a variable name
     * @param name The variable name to be validated
     */
    void            validateVariableName    (const std::string & name) const;

public:
    CCalculator() { cout << "Welcome to arbitrary precision calculator!" << endl
                         << "-To creat a variable type: <variable name> = <value>" << endl
                         << " *Variable names can only consist of letters and numbers having letter as the very first symbol" << endl
                         << "-To quit type \"quit\"" << endl;}
    void    run();
    void    saveToFile() const;
    void            readFromFile            (std::string = "data.txt");

};