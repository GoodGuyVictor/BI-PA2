#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
#endif /* __PROGTEST__ */

struct TEmployee
{
    string m_name;
    string m_surname;
    string m_email;
    unsigned int m_salary;

    TEmployee(string name, string surname, string email = "", unsigned int salary = 0)
    :m_name(name), m_surname(surname), m_email(email), m_salary(salary)
    {}
};

class CPersonalAgenda
{
public:
    CPersonalAgenda  ( void );
    ~CPersonalAgenda ( void );
    bool          Add              ( const string    & name,
                                     const string    & surname,
                                     const string    & email,
                                     unsigned int      salary );
    bool          Del              ( const string    & name,
                                     const string    & surname );
    bool          Del              ( const string    & email );
    bool          ChangeName       ( const string    & email,
                                     const string    & newName,
                                     const string    & newSurname );
    bool          ChangeEmail      ( const string    & name,
                                     const string    & surname,
                                     const string    & newEmail );
    bool          SetSalary        ( const string    & name,
                                     const string    & surname,
                                     unsigned int      salary );
    bool          SetSalary        ( const string    & email,
                                     unsigned int      salary );
    unsigned int  GetSalary        ( const string    & name,
                                     const string    & surname ) const;
    unsigned int  GetSalary        ( const string    & email ) const;
    bool          GetRank          ( const string    & name,
                                     const string    & surname,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          GetRank          ( const string    & email,
                                     int             & rankMin,
                                     int             & rankMax ) const;
    bool          GetFirst         ( string          & outName,
                                     string          & outSurname ) const;
    bool          GetNext          ( const string    & name,
                                     const string    & surname,
                                     string          & outName,
                                     string          & outSurname ) const;
private:
    vector<TEmployee> m_staffDb;

    static bool cmpSurname(const TEmployee &curr, const TEmployee &val)
    {
        if(curr.m_surname.compare(val.m_surname) < 0)
            return true;
        else return false;
    }

    static bool cmpName(const TEmployee &curr, const TEmployee &val)
    {
        if(curr.m_name.compare(val.m_name) < 0)
            return true;
        else return false;
    }

    vector<TEmployee>::iterator findLowerBoundSurname(const TEmployee &emp) const
    {
        vector<TEmployee>::iterator lowestSurname;
        lowestSurname = lower_bound(m_staffDb.begin(),
                                 m_staffDb.end(),
                                 emp, cmpSurname);
        return lowestSurname;
    }

    vector<TEmployee>::iterator findUpperBoundSurname(const TEmployee &emp, vector<TEmployee>::iterator lbs) const
    {
        vector<TEmployee>::iterator upperBoundSurname;
        upperBoundSurname = upper_bound(lbs,
                                m_staffDb.end(),
                                emp,
                                cmpSurname);
        return upperBoundSurname;
    }

    vector<TEmployee>::iterator findLowerBoundName(const TEmployee &emp, vector<TEmployee>::iterator ls) const
    {
        auto highestSurname = findUpperBoundSurname(emp, ls);

        vector<TEmployee>::iterator lowerBoundName;
        lowerBoundName = lower_bound(ls, highestSurname, emp, cmpName);

        return lowerBoundName;
    }

    vector<TEmployee>::iterator findEmployee(const string &name, const string &surname)
    {
        vector<TEmployee>::iterator employee;
        employee = findLowerBoundName(TEmployee(name, surname),
                                             findLowerBoundSurname(TEmployee(name, surname)));
        return employee;
    }
};

CPersonalAgenda::CPersonalAgenda(void)
{}

CPersonalAgenda::~CPersonalAgenda(void)
{}

bool CPersonalAgenda::Add(const string &name,
                          const string &surname,
                          const string &email,
                          unsigned int salary)
{

    //linear complexity!!!!!!!!!!!!!!!!!!
    vector<TEmployee>::iterator it;
    for (it = m_staffDb.begin(); it < m_staffDb.end(); it++) {
        if(it->m_email == email)
            return false;
    }

    if(m_staffDb.empty()) {
        m_staffDb.emplace_back(TEmployee(name, surname, email, salary));
        return true;
    } else {
        auto lowerBoundSurname = findLowerBoundSurname(TEmployee(name, surname, email, salary));
        if(lowerBoundSurname->m_surname != surname) {
            m_staffDb.insert(lowerBoundSurname, TEmployee(name, surname, email, salary));
            return true;
        } else {
            if(lowerBoundSurname->m_name == name)
                return false;
            else {
                auto lowerBoundName = findLowerBoundName(TEmployee(name, surname, email, salary), lowerBoundSurname);
                if(lowerBoundName->m_name == name)
                    return false;
                else {
                    m_staffDb.insert(lowerBoundName, TEmployee(name, surname, email, salary));
                    return true;
                }
            }
        }
    }
}

bool CPersonalAgenda::GetFirst(string &outName, string &outSurname) const
{
    if(!m_staffDb.empty()) {
        outName = m_staffDb.front().m_name;
        outSurname = m_staffDb.front().m_surname;
        return true;
    }
    return false;
}

bool CPersonalAgenda::GetNext(const string &name, const string &surname, string &outName, string &outSurname) const
{
    vector<TEmployee>::iterator currentEmployee;
    currentEmployee = findEmployee(name, surname);
    currentEmployee++;
    currentEmployee
}


#ifndef __PROGTEST__
int main ( void )
{




    string outName, outSurname;
    int lo, hi;

    CPersonalAgenda b1;
    assert ( b1 . Add ( "John", "Smith", "john", 30000 ) );
    assert ( b1 . Add ( "John", "Miller", "johnm", 35000 ) );
    assert ( b1 . Add ( "Peter", "Smith", "peter", 23000 ) );
    assert ( b1 . GetFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    /*assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( b1 . GetNext ( "John", "Smith", outName, outSurname )
             && outName == "Peter"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "Peter", "Smith", outName, outSurname ) );
    /*assert ( b1 . SetSalary ( "john", 32000 ) );
    assert ( b1 . GetSalary ( "john" ) ==  32000 );
    assert ( b1 . GetSalary ( "John", "Smith" ) ==  32000 );
    assert ( b1 . GetRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 1
             && hi == 1 );
    assert ( b1 . GetRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . GetRank ( "johnm", lo, hi )
             && lo == 2
             && hi == 2 );
    assert ( b1 . SetSalary ( "John", "Smith", 35000 ) );
    assert ( b1 . GetSalary ( "John", "Smith" ) ==  35000 );
    assert ( b1 . GetSalary ( "john" ) ==  35000 );
    assert ( b1 . GetRank ( "John", "Smith", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . GetRank ( "peter", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . GetRank ( "johnm", lo, hi )
             && lo == 1
             && hi == 2 );
    assert ( b1 . ChangeName ( "peter", "James", "Bond" ) );
    assert ( b1 . GetSalary ( "peter" ) ==  23000 );
    assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
    assert ( b1 . GetSalary ( "Peter", "Smith" ) ==  0 );
    assert ( b1 . GetFirst ( outName, outSurname )
             && outName == "James"
             && outSurname == "Bond" );
    assert ( b1 . GetNext ( "James", "Bond", outName, outSurname )
             && outName == "John"
             && outSurname == "Miller" );
    assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . ChangeEmail ( "James", "Bond", "james" ) );
    assert ( b1 . GetSalary ( "James", "Bond" ) ==  23000 );
    assert ( b1 . GetSalary ( "james" ) ==  23000 );
    assert ( b1 . GetSalary ( "peter" ) ==  0 );
    assert ( b1 . Del ( "james" ) );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 0
             && hi == 1 );
    assert ( b1 . Del ( "John", "Miller" ) );
    assert ( b1 . GetRank ( "john", lo, hi )
             && lo == 0
             && hi == 0 );
    assert ( b1 . GetFirst ( outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "John", "Smith", outName, outSurname ) );
    assert ( b1 . Del ( "john" ) );
    assert ( ! b1 . GetFirst ( outName, outSurname ) );
    assert ( b1 . Add ( "John", "Smith", "john", 31000 ) );
    assert ( b1 . Add ( "john", "Smith", "joHn", 31000 ) );
    assert ( b1 . Add ( "John", "smith", "jOhn", 31000 ) );

    CPersonalAgenda b2;
    assert ( ! b2 . GetFirst ( outName, outSurname ) );
    assert ( b2 . Add ( "James", "Bond", "james", 70000 ) );
    assert ( b2 . Add ( "James", "Smith", "james2", 30000 ) );
    assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( ! b2 . Add ( "James", "Bond", "james3", 60000 ) );
    assert ( ! b2 . Add ( "Peter", "Bond", "peter", 50000 ) );
    assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
    assert ( ! b2 . SetSalary ( "Joe", "Black", 90000 ) );
    assert ( ! b2 . SetSalary ( "joe", 90000 ) );
    assert ( b2 . GetSalary ( "Joe", "Black" ) ==  0 );
    assert ( b2 . GetSalary ( "joe" ) ==  0 );
    assert ( ! b2 . GetRank ( "Joe", "Black", lo, hi ) );
    assert ( ! b2 . GetRank ( "joe", lo, hi ) );
    assert ( ! b2 . ChangeName ( "joe", "Joe", "Black" ) );
    assert ( ! b2 . ChangeEmail ( "Joe", "Black", "joe" ) );
    assert ( ! b2 . Del ( "Joe", "Black" ) );
    assert ( ! b2 . Del ( "joe" ) );
    assert ( ! b2 . ChangeName ( "james2", "James", "Bond" ) );
    assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "james" ) );
    assert ( ! b2 . ChangeName ( "peter", "Peter", "Smith" ) );
    assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter" ) );
    assert ( b2 . Del ( "Peter", "Smith" ) );
    assert ( ! b2 . ChangeEmail ( "Peter", "Smith", "peter2" ) );
    assert ( ! b2 . SetSalary ( "Peter", "Smith", 35000 ) );
    assert ( b2 . GetSalary ( "Peter", "Smith" ) ==  0 );
    assert ( ! b2 . GetRank ( "Peter", "Smith", lo, hi ) );
    assert ( ! b2 . ChangeName ( "peter", "Peter", "Falcon" ) );
    assert ( ! b2 . SetSalary ( "peter", 37000 ) );
    assert ( b2 . GetSalary ( "peter" ) ==  0 );
    assert ( ! b2 . GetRank ( "peter", lo, hi ) );
    assert ( ! b2 . Del ( "Peter", "Smith" ) );
    assert ( ! b2 . Del ( "peter" ) );
    assert ( b2 . Add ( "Peter", "Smith", "peter", 40000 ) );
    assert ( b2 . GetSalary ( "peter" ) ==  40000 );

 */


    return 0;
}
#endif /* __PROGTEST__ */