class InvalidInput : public std::exception
{
    const char * what() const throw() override
    {
        return "Invalid input";
    }
};

class InvalidVariableName : public std::exception
{
    const char * what() const throw() override
    {
        return "Invalid variable name";
    }
};
class InvalidValue : public std::exception
{
    const char * what() const throw() override
    {
        return "Invalid Value";
    }
};
class MissingParanthesis : public std::exception
{
    const char * what() const throw() override
    {
        return "Missing paranthesis";
    }
};

class DecimalDivision : public std::exception
{
    const char * what() const throw() override
    {
        return "Decimal division is not legit";
    }
};

class InvalidFileFormat : public std::exception
{
    const char * what() const throw() override
    {
        return "Invalid file format";
    }
};

class InvalidFileName : public std::exception
{
    const char * what() const throw() override
    {
        return "Invalid file name";
    }
};

class DivisionByZero : public std::exception
{
    const char * what() const throw() override
    {
        return "Division by zero is undefined";
    }
};