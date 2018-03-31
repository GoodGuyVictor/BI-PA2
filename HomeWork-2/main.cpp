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
    vector<unsigned int> m_salaryList;
    vector<TEmployee> m_emailList;

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

    static bool cmpEmail(const TEmployee &curr, const TEmployee &val)
    {
        if(curr.m_email.compare(val.m_email) < 0)
            return true;
        else return false;
    }

    /**
     *
     * @param name
     * @param surname
     * @param pos (output parameter) gets the position of found employee in database
     *          in case if employee was not found gets the position where to put one
     * @return true if database already contains an employee with such combination of name and surname
     *         false otherwise
     */
    bool findEmployee(const string &name, const string &surname, size_t &pos) const;
    void addSalary(unsigned int sal);
    void resetSalary(unsigned int oldSal, unsigned int newSal);
    bool addEmail(const TEmployee &empl);
    bool resetEmail(const string &oldEmail, const string &newEmail);
};

CPersonalAgenda::CPersonalAgenda(void)
{}

CPersonalAgenda::~CPersonalAgenda(void)
{}

bool CPersonalAgenda::findEmployee(const string &name, const string &surname, size_t &pos) const
{
    if(m_staffDb.empty()) {
        pos = 0;
        return false;
    }
    auto lowerBoundSurname = lower_bound(m_staffDb.begin(),
                                         m_staffDb.end(),
                                         TEmployee(name, surname),
                                         cmpSurname);
    if(lowerBoundSurname == m_staffDb.end()) {
        pos = (size_t)(lowerBoundSurname - m_staffDb.begin());
        return false;
    }

    if(lowerBoundSurname->m_surname != surname) {
        pos = (size_t)(lowerBoundSurname - m_staffDb.begin());
        return false;
    }

    auto upperBoundSurname = upper_bound(lowerBoundSurname,
                                         m_staffDb.end(),
                                         TEmployee(name, surname),
                                         cmpSurname);
    auto lowerBoundName = lower_bound(lowerBoundSurname,
                                      upperBoundSurname,
                                      TEmployee(name, surname),
                                      cmpName);
    if(lowerBoundName == upperBoundSurname) {
        pos = (size_t)(lowerBoundName - m_staffDb.begin());
        return false;
    }
    if(lowerBoundName->m_name == name) {
        pos = (size_t)(lowerBoundName - m_staffDb.begin());
        return true;
    } else {
        pos = (size_t)(lowerBoundName - m_staffDb.begin());
        return false;
    }
}

void CPersonalAgenda::addSalary(unsigned int sal)
{
    auto it = lower_bound(m_salaryList.begin(), m_salaryList.end(), sal);
    m_salaryList.insert(it, sal);
}

void CPersonalAgenda::resetSalary(unsigned int oldSal, unsigned int newSal)
{
    //reset salary in salaryList
    auto oldSalPos = lower_bound(m_salaryList.begin(), m_salaryList.end(), oldSal);
    m_salaryList.erase(oldSalPos);
    auto newSalPos = lower_bound(m_salaryList.begin(), m_salaryList.end(), newSal);
    m_salaryList.insert(newSalPos, newSal);
}

bool CPersonalAgenda::addEmail(const TEmployee &empl)
{
    if(m_emailList.empty()){
        m_emailList.push_back(empl);
        return true;
    }
    auto it = lower_bound(m_emailList.begin(), m_emailList.end(), empl, cmpEmail);
    if(it != m_emailList.end() && it->m_email == empl.m_email)
        return false;
    m_emailList.insert(it, empl);
    return true;
}

bool CPersonalAgenda::resetEmail(const string &oldEmail, const string &newEmail)
{
    auto insertE = lower_bound(m_emailList.begin(), m_emailList.end(), TEmployee("", "", newEmail), cmpEmail);
    if(insertE->m_email == newEmail && insertE != m_emailList.end())
        return false;
    auto deleteE = lower_bound(m_emailList.begin(), m_emailList.end(), TEmployee("", "", oldEmail), cmpEmail);
    TEmployee copy = *deleteE;
    copy.m_email = newEmail;
    m_emailList.erase(deleteE);
    m_emailList.insert(insertE, copy);
    return true;
}

bool CPersonalAgenda::Add(const string &name,
                          const string &surname,
                          const string &email,
                          unsigned int salary)
{
    size_t position;

    if(findEmployee(name, surname, position))
        return false;
    else {
        if(!addEmail(TEmployee(name, surname, email, salary)))
            return false;
        addSalary(salary);
        auto dbPosition = m_staffDb.begin() + position;
        m_staffDb.insert(dbPosition, TEmployee(name, surname, email, salary));
        return true;
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
    size_t position;
    if(findEmployee(name, surname, position)) {
        auto currentEmployee = m_staffDb.begin() + position;
        //if the last one
        if(currentEmployee == m_staffDb.end() - 1)
            return false;
        currentEmployee++;
        outName = currentEmployee->m_name;
        outSurname = currentEmployee->m_surname;
        return true;
    }
    return false;
}

//bool CPersonalAgenda::Del(const string &name, const string &surname)
//{
//    size_t position;
//    if(findEmployee(name, surname, position)) {
//        auto currentEmployee = m_staffDb.begin() + position;
//        auto salaryPos = lower_bound(m_salaryList.begin(), m_salaryList.end(), currentEmployee->m_salary);
//        auto emailPos = lower_bound(m_emailList.begin(), m_emailList.end(), currentEmployee->m_email, cmpEmail);
//        m_salaryList.erase(salaryPos);
//        m_emailList.erase(emailPos);
//        m_staffDb.erase(currentEmployee);
//        return true;
//    }
//    return false;
//}

//bool CPersonalAgenda::Del(const string &email)
//{
//    //linear complexity!!!!!!!!!!!!!!!!!!
//    for (auto it = m_staffDb.begin(); it < m_staffDb.end(); it++) {
//        if(it->m_email == email) {
//            auto salaryPos = lower_bound(m_salaryList.begin(), m_salaryList.end(), it->m_salary);
//            auto emailPos = lower_bound(m_emailList.begin(), m_emailList.end(), it->m_email, cmpEmail);
//            m_salaryList.erase(salaryPos);
//            m_emailList.erase(emailPos);
//            m_staffDb.erase(it);
//            return true;
//        }
//    }
//    return false;
//}

bool CPersonalAgenda::SetSalary(const string &name, const string &surname, unsigned int salary)
{
    size_t position;
    if(findEmployee(name, surname, position)) {
        auto currentEmployee = m_staffDb.begin() + position;

        resetSalary(currentEmployee->m_salary, salary);

        //reset salary in emailList
        auto emailListPos = lower_bound(m_emailList.begin(), m_emailList.end(), *currentEmployee, cmpEmail);
        emailListPos->m_salary = salary;

        //reset salary in staffDb
        currentEmployee->m_salary = salary;
        return true;
    }
    return false;
}

bool CPersonalAgenda::SetSalary(const string &email, unsigned int salary)
{
    //reset salary in emailList
    auto emailListPos = lower_bound(m_emailList.begin(), m_emailList.end(), TEmployee("", "", email), cmpEmail);
    emailListPos->m_salary = salary;

    //resete salary in staffDb
    string name = emailListPos->m_name;
    string surname = emailListPos->m_surname;
    size_t position;
    if(findEmployee(name, surname, position)) {
        auto currentEmployee = m_staffDb.begin() + position;
        //reset salary in salaryList
        resetSalary(currentEmployee->m_salary, salary);
        currentEmployee->m_salary = salary;
    }
}

unsigned int CPersonalAgenda::GetSalary(const string &name, const string &surname) const
{
    size_t position;
    if(findEmployee(name, surname, position)) {
        auto currentEmployee = m_staffDb.begin() + position;
        return currentEmployee->m_salary;
    }
    return 0;
}

unsigned int CPersonalAgenda::GetSalary(const string &email) const
{
    auto currentEmployee = lower_bound(m_emailList.begin(), m_emailList.end(), TEmployee("", "", email), cmpEmail);
    if(currentEmployee == m_emailList.end())
        return 0;
    return currentEmployee->m_salary;
//    //linear complexity!!!!!!!!!!!!!!!!!!
//    for (auto it = m_staffDb.begin(); it < m_staffDb.end(); it++) {
//        if(it->m_email == email) {
//            return it->m_salary;
//        }
//    }
//    return 0;
}

bool CPersonalAgenda::ChangeName(const string &email, const string &newName, const string &newSurname)
{
    //linear complexity!!!!!!!!!!!!!!!!!!
    for (auto it = m_staffDb.begin(); it < m_staffDb.end(); it++) {
        if(it->m_email == email) {
            size_t position;
            if(findEmployee(newName, newSurname, position)) {
                return false;
            }else {
                TEmployee tmp = *it;
                m_staffDb.erase(it);
                tmp.m_name = newName;
                tmp.m_surname = newSurname;
                auto dbPosition = m_staffDb.begin() + position;
                m_staffDb.insert(dbPosition, tmp);
                return true;
            }
        }
    }
    return false;
}

bool CPersonalAgenda::ChangeEmail(const string &name, const string &surname, const string &newEmail)
{
    size_t position;
    if(findEmployee(name, surname, position)) {
        auto currentEmployee = m_staffDb.begin() + position;
        if(!resetEmail(currentEmployee->m_email, newEmail))
            return false;
        currentEmployee->m_email = newEmail;
        return true;
    }
    return false;
}

bool CPersonalAgenda::GetRank(const string &name, const string &surname, int &rankMin, int &rankMax) const
{
    size_t position;
    if(findEmployee(name, surname, position)) {
        auto currentEmployee = m_staffDb.begin() + position;
        auto lowerBoundSalary = lower_bound(m_salaryList.begin(), m_salaryList.end(), currentEmployee->m_salary);
        auto upperBoundSalary = upper_bound(lowerBoundSalary, m_salaryList.end(), currentEmployee->m_salary);
        rankMin = (int)(lowerBoundSalary - m_salaryList.begin());
        rankMax = rankMin + (int)(upperBoundSalary - lowerBoundSalary) - 1;
        return true;
    }
    return false;
}

bool CPersonalAgenda::GetRank(const string &email, int &rankMin, int &rankMax) const
{
    auto currentEmployee = lower_bound(m_emailList.begin(), m_emailList.end(), TEmployee("", "", email), cmpEmail);
    if(currentEmployee == m_emailList.end())
        return false;
    auto lowerBoundSalary = lower_bound(m_salaryList.begin(), m_salaryList.end(), currentEmployee->m_salary);
    auto upperBoundSalary = upper_bound(lowerBoundSalary, m_salaryList.end(), currentEmployee->m_salary);
    rankMin = (int)(lowerBoundSalary - m_salaryList.begin());
    rankMax = rankMin + (int)(upperBoundSalary - lowerBoundSalary) - 1;
    return true;
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
    assert ( b1 . GetNext ( "John", "Miller", outName, outSurname )
             && outName == "John"
             && outSurname == "Smith" );
    assert ( b1 . GetNext ( "John", "Smith", outName, outSurname )
             && outName == "Peter"
             && outSurname == "Smith" );
    assert ( ! b1 . GetNext ( "Peter", "Smith", outName, outSurname ) );
    assert ( ! b1 . GetNext ( "Peterdw", "Smith", outName, outSurname ) );
    assert ( b1 . SetSalary ( "John", "Smith", 35000 ) );
    assert ( b1 . SetSalary ( "john", 32000 ) );
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
    /*assert ( b1 . ChangeName ( "peter", "James", "Bond" ) );
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