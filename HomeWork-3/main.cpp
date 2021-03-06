#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <ctime>
#include <climits>
#include <cmath>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <memory>
using namespace std;
class InvalidDateException
{
};
#endif /* __PROGTEST__ */

// uncomment if your code implements the overloaded suffix operators
 #define TEST_LITERALS

struct TTmpDate
{
    int m_year;
    int m_month;
    int m_day;
    vector<TTmpDate> m_buffer;

    TTmpDate(const int year, const int month, const int day)
            :m_year(year), m_month(month), m_day(day)
    {
        m_buffer.push_back(*this);
    }

    TTmpDate operator + (const TTmpDate &);
    TTmpDate operator - (const TTmpDate &);
    TTmpDate & operator - ();

};

TTmpDate TTmpDate::operator+(const TTmpDate &rightOperand)
{
    TTmpDate result = *this;
    result.m_year += rightOperand.m_year;
    result.m_month += rightOperand.m_month;
    result.m_day += rightOperand.m_day;
    result.m_buffer.push_back(rightOperand);

    return result;
}

TTmpDate TTmpDate::operator-(const TTmpDate &rightOperand)
{
    TTmpDate copy = rightOperand;
    return operator+(copy.operator-());
}

TTmpDate & TTmpDate::operator-()
{
    m_year = m_year * (-1);
    m_month = m_month * (-1);
    m_day = m_day * (-1);
    m_buffer[0].m_year = m_year;
    m_buffer[0].m_month = m_month;
    m_buffer[0].m_day =  m_day;
    return *this;
}


class CDate
{
public:
    CDate (const int year = 0, const int month = 0, const int day = 0)
            :m_year(year), m_month(month), m_day(day)
    {
        validate();
    }

    friend ostream & operator << (ostream & os, const CDate & date);
    CDate operator + (const TTmpDate & rightOperand);
    CDate operator - (const TTmpDate & rightOperand);
    int operator - (const CDate & rightOperand);
    CDate& operator = (const CDate& rightDate);
    CDate& operator += (const TTmpDate & addingDate);
    bool operator == (const CDate & rightOperand);
    bool operator != (const CDate & rightOperand);
    bool operator < (const CDate & rightOperand);

private:
    int m_year;
    int m_month;
    int m_day;

    bool isLeapYear(int year)
    {
        return (((!(year%4) && (year%100)) || !(year%400)) && (year%4000));
    }

    bool validDate(int year,int month,int day);
    void validate();
    int getJnd(int year, int month, int day);
    void setDateByJnd ( int Jnd );
};

CDate CDate::operator+(const TTmpDate &rightOperand)
{
    CDate result = *this;
    result.m_year += rightOperand.m_year;

    if(rightOperand.m_month / 12) {
        result.m_year += rightOperand.m_month / 12;
        result.m_month += rightOperand.m_month % 12;
    } else {
        result.m_month += rightOperand.m_month;

    }
    if(result.m_month > 12) {
        result.m_year++;
        result.m_month -= 12;
    }

    if(result.m_month <= 0) {
        result.m_year--;
        result.m_month = 12 + result.m_month;
    }

    if (rightOperand.m_day != 0) {
        int Jnd = getJnd(result.m_year, result.m_month, result.m_day);
        Jnd += rightOperand.m_day;
        result.setDateByJnd(Jnd);
    }

    result.validate();
    if(result.m_year > 4000)
        result.m_day++;
    return result;
}

CDate CDate::operator-(const TTmpDate &rightOperand)
{
    TTmpDate copy = rightOperand;
    return operator+(copy.operator-());
}

ostream & operator<<(ostream &os, const CDate & date)
{
    ios_base::fmtflags ff;
    ff = os.flags();

    if(date.m_month < 10 && date.m_day < 10) {
        os << dec << date.m_year << '-' << '0' << date.m_month << '-' << '0' << date.m_day;
    }

    if(date.m_month >= 10 && date.m_day < 10) {
        os << dec << date.m_year << '-' << date.m_month << '-' << '0' << date.m_day;
    }

    if(date.m_month < 10 && date.m_day >= 10) {
        os << dec  << date.m_year << '-' << '0' << date.m_month << '-' << date.m_day;
    }

    if(date.m_month >= 10 && date.m_day >= 10) {
        os << dec  << date.m_year << '-' << date.m_month << '-' << date.m_day;
    }
    os.flags(ff);
    return os;
}

CDate & CDate::operator=(const CDate &rightDate)
{
    m_year = rightDate.m_year;
    m_month = rightDate.m_month;
    m_day = rightDate.m_day;
    validate();
    return *this;
}

bool CDate::validDate(int year, int month, int day)
{
    int short monthlen[]={31,28,31,30,31,30,31,31,30,31,30,31};

    if (month > 12 || year < 1600)
        return false;
    if (isLeapYear(year) && month==2)
        monthlen[1]++;
    if (day>monthlen[month-1])
        return false;
    return true;
}

void CDate::validate()
{
    if(m_year > 0 && m_month > 0 && m_day > 0) {
        if (!validDate(m_year, m_month, m_day))
            throw InvalidDateException();
    } else
        throw InvalidDateException();
}

int CDate::getJnd(int year, int month, int day)
{
    if(year > 4000) day--;
    int a = (14 - month) / 12;
    int y = year + 4800 - a;
    int m = month + 12 * a - 3;

    return (day + (153 * m + 2) / 5 + 365 * y + y / 4 - y / 100 + y / 400 - 32045);
}

void CDate::setDateByJnd(int Jnd)
{
    int a = Jnd + 32044;
    int b = (4 * a + 3) / 146097;
    int c = a - 146097 * b / 4;
    int d = (4 * c + 3) / 1461;
    int e = c - 1461 * d / 4;
    int m = (5 * e + 2) / 153;

    m_day = (e - (153 * m + 2) / 5 + 1);
    m_month = (m + 3 - 12 * (m / 10));
    m_year = (100 * b + d - 4800 + m / 10);
}

CDate & CDate::operator+=(const TTmpDate &addingDate)
{
    for (auto it = addingDate.m_buffer.begin(); it < addingDate.m_buffer.end(); it++) {
        *this = operator+(*it);
        validate();
    }
    return *this;
}

bool CDate::operator<(const CDate &rightOperand)
{
    if(m_year == rightOperand.m_year)
        if(m_month == rightOperand.m_month)
            if(m_day == rightOperand.m_day)
                return false;
            else
                return m_day < rightOperand.m_day;
        else
            return m_month < rightOperand.m_month;
    else
        return m_year < rightOperand.m_year;
}

bool CDate::operator!=(const CDate &rightOperand)
{
    return m_year != rightOperand.m_year
           || m_month != rightOperand.m_month
           || m_day != rightOperand.m_day;
}

bool CDate::operator==(const CDate &rightOperand)
{
    return m_year == rightOperand.m_year
           && m_month == rightOperand.m_month
           && m_day == rightOperand.m_day;
}

int CDate::operator-(const CDate &rightOperand)
{
    int leftJnd = getJnd(m_year, m_month, m_day);
    int rightJnd = getJnd(rightOperand.m_year, rightOperand.m_month, rightOperand.m_day);
    return leftJnd - rightJnd;
}

TTmpDate Year(int y)
{
    return TTmpDate(y, 0, 0);
}

TTmpDate Month(int m)
{
    return TTmpDate(0, m, 0);
}

TTmpDate Day(int d)
{
    return TTmpDate(0, 0, d);
}

TTmpDate operator"" _day(unsigned long long int d)
{
    return TTmpDate(0, 0, d);
}

TTmpDate operator"" _days(unsigned long long int d)
{
    return TTmpDate(0, 0, d);
}

TTmpDate operator"" _year(unsigned long long int y)
{
    return TTmpDate(y, 0, 0);
}

TTmpDate operator"" _years(unsigned long long int y)
{
    return TTmpDate(y, 0, 0);
}

TTmpDate operator"" _month(unsigned long long int m)
{
    return TTmpDate(0, m, 0);
}

TTmpDate operator"" _months(unsigned long long int m)
{
    return TTmpDate(0, m, 0);
}


#ifndef __PROGTEST__
string             toString                                ( const CDate     & x )
{
    ostringstream oss;
    oss << x;
    return oss . str ();
}

int                main                                    ( void )
{

    CDate tmp ( 2000, 1, 1 );

    assert ( toString ( CDate ( 2000, 1, 1 ) )  == "2000-01-01" );
    assert ( toString ( CDate ( 2500, 12, 21 ) )  == "2500-12-21" );
    assert ( toString ( CDate ( 1685, 7, 11 ) )  == "1685-07-11" );
    try
    {
        tmp = CDate ( 1900, 2, 29 );
        assert ( "Missing exception" == NULL );
    }
    catch ( const InvalidDateException & e )
    {
    }
    assert ( toString ( CDate ( 2000, 2, 29 ) )  == "2000-02-29" );
    assert ( toString ( CDate ( 2004, 2, 29 ) )  == "2004-02-29" );
    try
    {
        tmp = CDate ( 4000, 2, 29 );
        assert ( "Missing exception" == NULL );
    }
    catch ( const InvalidDateException & e )
    {
    }
    assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 1 ) )  == "2019-03-15" );
    assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 7 ) )  == "2025-03-15" );
    assert ( toString ( CDate ( 2018, 3, 15 ) + Year ( 73 ) )  == "2091-03-15" );
    assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 3 ) )  == "2018-06-15" );
    assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 1 ) )  == "2018-04-15" );
    assert ( toString ( CDate ( 2018, 3, 15 ) + Month ( 285 ) )  == "2041-12-15" );
    assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 1 ) )  == "2018-03-16" );
    assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 12 ) )  == "2018-03-27" );
    assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 1234567 ) )  == "5398-05-02" );
    assert ( toString ( CDate ( 2018, 3, 15 ) + Day ( 3 ) + Year ( 2 ) + Month ( 3 ) + Day ( 5 ) + Month ( 11 ) )  == "2021-05-23" );
    try
    {
        tmp = CDate ( 2000, 2, 29 ) + Year ( 300 );
        assert ( "Missing exception" == NULL );
    }
    catch ( const InvalidDateException & e )
    {
    }
    try
    {
        tmp = CDate ( 2000, 3, 30 ) + Month ( 11 );
        assert ( "Missing exception" == NULL );
    }
    catch ( const InvalidDateException & e )
    {
    }
    assert ( toString ( CDate ( 2001, 2, 20 ) + Day ( 9 ) )  == "2001-03-01" );
    assert ( toString ( CDate ( 2000, 1, 1 ) + Day ( 28 ) + Month ( 1 ) )  == "2000-02-29" );
    assert ( toString ( CDate ( 1999, 1, 1 ) + Year ( 1 ) + Day ( 28 ) + Month ( 1 ) )  == "2000-02-29" );
    assert ( toString ( CDate ( 2001, 1, 1 ) + Day ( 1095 ) + Day ( 28 ) + Month ( 1 ) )  == "2004-02-29" );
    try
    {
        tmp = CDate ( 2001, 1, 1 ) + Day ( 28 ) + Month ( 1 ) + Day ( 1095 );
        assert ( "Missing exception" == NULL );
    }
    catch ( const InvalidDateException & e )
    {
    }
    try
    {
        tmp = CDate ( 2000, 1, 1 ) + Day ( 28 ) + Month ( 1 ) + Year ( 1 );
        assert ( "Missing exception" == NULL );
    }
    catch ( const InvalidDateException & e )
    {
    }
    tmp = CDate ( 2000, 1, 1 );
    assert ( toString ( tmp - Year ( 5 ) + Month ( 2 ) )  == "1995-03-01" );
    assert ( toString ( tmp ) == "2000-01-01" );
    assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 1 ) - Month ( 3 ) - Day ( 10 ) )  == "1998-09-21" );
    assert ( toString ( CDate ( 2000, 1, 1 ) - Year ( 2 ) - Month ( -3 ) + Day ( -10 ) )  == "1998-03-22" );
    assert ( toString ( CDate ( 2000, 1, 1 ) + Day ( 59 ) - Month ( 1 ) - Year ( 2 ) )  == "1998-01-29" );
    try
    {
        tmp = CDate ( 2000, 1, 1 ) + Day ( 59 ) - Year ( 2 ) - Month ( 1 );
        assert ( "Missing exception" == NULL );
    }
    catch ( const InvalidDateException & e )
    {
    }
    tmp = CDate ( 2000, 1, 1 );
    tmp +=  - Year ( 2 ) - Month ( -3 ) + Day ( -10 );
    assert ( toString ( tmp ) == "1998-03-22" );
    tmp = CDate ( 2000, 1, 1 );
    tmp += Day ( 59 ) - Month ( 1 ) - Year ( 2 );
    assert ( toString ( tmp ) == "1998-01-29" );
    try
    {
        tmp = CDate ( 2000, 1, 1 );
        tmp += Day ( 59 ) - Year ( 2 ) - Month ( 1 );
        assert ( "Missing exception" == NULL );
    }
    catch ( const InvalidDateException & e )
    {
    }
    tmp = CDate ( 2018, 3, 15 ) + Day ( -3 );
    assert ( toString ( tmp ) == "2018-03-12" );
    assert ( !( CDate ( 2018, 3, 15 ) == CDate ( 2000, 1, 1 ) ) );
    assert ( CDate ( 2018, 3, 15 ) != CDate ( 2000, 1, 1 ) );
    assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2000, 1, 1 ) ) );
    assert ( CDate ( 2018, 3, 15 ) == CDate ( 2018, 3, 15 ) );
    assert ( !( CDate ( 2018, 3, 15 ) != CDate ( 2018, 3, 15 ) ) );
    assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2018, 3, 15 ) ) );
    assert ( !( CDate ( 2018, 3, 15 ) + Day ( 1 ) == CDate ( 2018, 3, 15 ) ) );
    assert ( CDate ( 2018, 3, 15 ) + Day ( 1 ) != CDate ( 2018, 3, 15 ) );
    assert ( !( CDate ( 2018, 3, 15 ) + Day ( 1 ) < CDate ( 2018, 3, 15 ) ) );
    assert ( !( CDate ( 2018, 3, 15 ) + Day ( -1 ) == CDate ( 2018, 3, 15 ) ) );
    assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) != CDate ( 2018, 3, 15 ) );
    assert ( CDate ( 2018, 3, 15 ) + Day ( -1 ) < CDate ( 2018, 3, 15 ) );
    assert ( CDate ( 2018, 3, 15 ) - CDate ( 2000, 1, 1 ) == 6648 );
    assert ( CDate ( 2000, 1, 1 ) - CDate ( 2018, 3, 15 ) == -6648 );
    assert ( CDate ( 2018, 3, 15 ) + Year ( 3 ) + Month ( -18 ) - CDate ( 2000, 1, 1 ) == 7197 );
    assert ( CDate ( 5398, 5, 2 ) - CDate ( 2018, 3, 15 ) == 1234567 );
    assert(toString(CDate(1964, 8, 10) - Year(300)) == "1664-08-10");
    assert(toString(CDate(1964, 8, 10) - Year(364)) == "1600-08-10");

#ifdef TEST_LITERALS
    assert ( toString ( CDate ( 2000, 1, 1 ) )  == "2000-01-01" );
  assert ( toString ( CDate ( 2500, 12, 21 ) )  == "2500-12-21" );
  assert ( toString ( CDate ( 1685, 7, 11 ) )  == "1685-07-11" );
  try
  {
    tmp = CDate ( 1900, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2000, 2, 29 ) )  == "2000-02-29" );
  assert ( toString ( CDate ( 2004, 2, 29 ) )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 4000, 2, 29 );
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1_year )  == "2019-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 7_years )  == "2025-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 73_years )  == "2091-03-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 3_months )  == "2018-06-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1_month )  == "2018-04-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 285_months )  == "2041-12-15" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1_day )  == "2018-03-16" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 12_days )  == "2018-03-27" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 1234567_days )  == "5398-05-02" );
  assert ( toString ( CDate ( 2018, 3, 15 ) + 3_days + 2_years + 3_months + 5_days + 11_months )  == "2021-05-23" );
  try
  {
    tmp = CDate ( 2000, 2, 29 ) + 300_years;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 3, 30 ) + 11_months;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  assert ( toString ( CDate ( 2001, 2, 20 ) + 9_days )  == "2001-03-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + 28_days + 1_month )  == "2000-02-29" );
  assert ( toString ( CDate ( 1999, 1, 1 ) + 1_year + 28_days + 1_month )  == "2000-02-29" );
  assert ( toString ( CDate ( 2001, 1, 1 ) + 1095_days + 28_days + 1_month )  == "2004-02-29" );
  try
  {
    tmp = CDate ( 2001, 1, 1 ) + 28_days + 1_month + 1095_days;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + 28_days + 1_month + 1_year;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  assert ( toString ( tmp - 5_years + 2_months )  == "1995-03-01" );
  assert ( toString ( tmp ) == "2000-01-01" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - 1_year - 3_months - 10_days )  == "1998-09-21" );
  assert ( toString ( CDate ( 2000, 1, 1 ) - 2_years - ( -3_months ) + ( -10_days ) )  == "1998-03-22" );
  assert ( toString ( CDate ( 2000, 1, 1 ) + 59_days - 1_month - 2_years )  == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 ) + 59_days - 2_years - 1_month;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2000, 1, 1 );
  tmp +=  - 2_years - ( -3_months ) + ( -10_days );
  assert ( toString ( tmp ) == "1998-03-22" );
  tmp = CDate ( 2000, 1, 1 );
  tmp += 59_days - 1_month - 2_years;
  assert ( toString ( tmp ) == "1998-01-29" );
  try
  {
    tmp = CDate ( 2000, 1, 1 );
    tmp += 59_days - 2_years - 1_month;
    assert ( "Missing exception" == NULL );
  }
  catch ( const InvalidDateException & e )
  {
  }
  tmp = CDate ( 2018, 3, 15 ) + ( -3_days );
  assert ( toString ( tmp ) == "2018-03-12" );
  assert ( !( CDate ( 2018, 3, 15 ) == CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) != CDate ( 2000, 1, 1 ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2000, 1, 1 ) ) );
  assert ( CDate ( 2018, 3, 15 ) == CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) != CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + 1_day == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + 1_day != CDate ( 2018, 3, 15 ) );
  assert ( !( CDate ( 2018, 3, 15 ) + 1_day < CDate ( 2018, 3, 15 ) ) );
  assert ( !( CDate ( 2018, 3, 15 ) + ( -1_day ) == CDate ( 2018, 3, 15 ) ) );
  assert ( CDate ( 2018, 3, 15 ) + ( -1_day ) != CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) + ( -1_day ) < CDate ( 2018, 3, 15 ) );
  assert ( CDate ( 2018, 3, 15 ) - CDate ( 2000, 1, 1 ) == 6648 );
  assert ( CDate ( 2000, 1, 1 ) - CDate ( 2018, 3, 15 ) == -6648 );
  assert ( CDate ( 2018, 3, 15 ) + 3_years + ( -18_months ) - CDate ( 2000, 1, 1 ) == 7197 );
  assert ( CDate ( 5398, 5, 2 ) - CDate ( 2018, 3, 15 ) == 1234567 );
  ostringstream oss;
  oss << setfill ( 'x' ) << left << hex << CDate ( 2000, 1, 1 ) << ' ' << setw ( 10 ) << 65536;
  assert ( oss . str () == "2000-01-01 10000xxxxx" );
#endif /* TEST_LITERALS */
    return 0;
}
#endif /* __PROGTEST__ */