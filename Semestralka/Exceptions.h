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
