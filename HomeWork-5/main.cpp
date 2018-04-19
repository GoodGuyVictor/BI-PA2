#ifndef __PROGTEST__
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <string>
#include <array>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <algorithm>
#include <functional>
#include <iterator>
using namespace std;

class CDate 
{
  public:
                             CDate                         ( int               y,
                                                             int               m,
                                                             int               d )
                             : m_Y ( y ),
                               m_M ( m ),
                               m_D ( d )
    {
    }
    
    int                      CompareTo                     ( const CDate     & other ) const
    {
      if ( m_Y != other . m_Y )
        return ( other . m_Y < m_Y ) - ( m_Y < other . m_Y );
      if ( m_M != other . m_M )
        return ( other . m_M < m_M ) - ( m_M < other . m_M );
      return ( other . m_D < m_D ) - ( m_D < other . m_D );  
    }
    
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CDate     & d )
    {
      return os << d . m_Y << '-' << d . m_M << '-' << d . m_D;
    }
    
  private:
    int                      m_Y;
    int                      m_M;
    int                      m_D;
};
enum class ESortKey
{
  NAME,
  BIRTH_DATE,
  ENROLL_YEAR
};
#endif /* __PROGTEST__ */
class CStudent
{
  public:
                             CStudent                      ( const string    & name,
                                                             const CDate     & born,
                                                             int               enrolled );

    bool                     operator ==                   ( const CStudent  & other ) const;
    bool                     operator !=                   ( const CStudent  & other ) const;
  private:
    string m_name;
    CDate m_birthday;
    int m_enrolled;
};

CStudent::CStudent(const string &name, const CDate &born, int enrolled)
: m_name(name), m_birthday(CDate(born)), m_enrolled(enrolled)
{
}

bool CStudent::operator==(const CStudent &other) const
{
    if(m_name == other.m_name
       && m_birthday.CompareTo(other.m_birthday) == 0
       && m_enrolled == other.m_enrolled)
        return true;
    return false;
}

bool CStudent::operator!=(const CStudent &other) const
{
    return !(operator==(other));
}

class CFilter 
{
  public:
                             CFilter                       ( void );
    CFilter                & Name                          ( const string    & name );
    CFilter                & BornBefore                    ( const CDate     & date );
    CFilter                & BornAfter                     ( const CDate     & date );
    CFilter                & EnrolledBefore                ( int               year );
    CFilter                & EnrolledAfter                 ( int               year );
  private:
    // todo
};

class CSort
{
  public:
                             CSort                         ( void );
    CSort                  & AddKey                        ( ESortKey          key,
                                                             bool              ascending );
    
  private:
    // todo
};

class CStudyDept 
{
  public:
                             CStudyDept                    ( void );
    bool                     AddStudent                    ( const CStudent  & x );
    bool                     DelStudent                    ( const CStudent  & x );
    list<CStudent>           Search                        ( const CFilter   & flt,
                                                             const CSort     & sortOpt ) const;
    set<string>              Suggest                       ( const string    & name ) const;
  private:
    // todo
};
#ifndef __PROGTEST__
int main ( void )
{

//    string str1 = "Jan Jakub Ryba";
//    string str2 = "RYBA jan JaKuB";
//    string str3 = "Jan Jakub Ryba";
//    cout << boolalpha << (str1 == str3) << endl;
//
//    size_t h1 = hash<string>()(str1);
//
//    transform(str1.begin(), str1.end(), str1.begin(), ::tolower);
//    transform(str2.begin(), str2.end(), str2.begin(), ::tolower);
//    cout << str1 << endl;
//    cout << str2 << endl;
//    cout << endl;
//
//    size_t h2 = hash<string>()(str1);
//    cout << h1 << endl;
//    cout << h2 << endl;


//  CStudyDept x0;
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2010 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2010 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1997, 6, 17), 2010 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1997, 6, 17), 2010 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1980, 4, 11), 2016 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1980, 4, 11), 2016 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2016 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1980, 4, 11), 2016 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2010 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2010 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "James Bond", CDate ( 1997, 6, 17), 2016 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "James Bond", CDate ( 1997, 6, 17), 2016 ) ) );
  assert ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) != CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2016 ) );
  assert ( ! ( CStudent ( "James Bond", CDate ( 1980, 4, 11), 2010 ) == CStudent ( "Peter Peterson", CDate ( 1997, 6, 17), 2016 ) ) );
  /*assert ( x0 . AddStudent ( CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ) ) );
  assert ( x0 . AddStudent ( CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ) ) );
  assert ( x0 . Search ( CFilter (), CSort () ) == (list<CStudent>
  {
    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 ),
    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 )
  }) );
  assert ( x0 . Search ( CFilter (), CSort () . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 )
  }) );
  assert ( x0 . Search ( CFilter (), CSort () . AddKey ( ESortKey::NAME, false ) ) == (list<CStudent>
  {
    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 ),
    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 )
  }) );
  assert ( x0 . Search ( CFilter (), CSort () . AddKey ( ESortKey::ENROLL_YEAR, false ) . AddKey ( ESortKey::BIRTH_DATE, false ) . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "Peter John Taylor", CDate ( 1984, 1, 17), 2017 ),
    CStudent ( "John Peter Taylor", CDate ( 1983, 7, 13), 2014 ),
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 ),
    CStudent ( "Peter Taylor", CDate ( 1982, 2, 23), 2011 )
  }) );
  assert ( x0 . Search ( CFilter () . Name ( "james bond" ), CSort () . AddKey ( ESortKey::ENROLL_YEAR, false ) . AddKey ( ESortKey::BIRTH_DATE, false ) . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 )
  }) );
  assert ( x0 . Search ( CFilter () . BornAfter ( CDate ( 1980, 4, 11) ) . BornBefore ( CDate ( 1983, 7, 13) ) . Name ( "John Taylor" ) . Name ( "james BOND" ), CSort () . AddKey ( ESortKey::ENROLL_YEAR, false ) . AddKey ( ESortKey::BIRTH_DATE, false ) . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 )
  }) );
  assert ( x0 . Search ( CFilter () . Name ( "james" ), CSort () . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
  }) );
  assert ( x0 . Suggest ( "peter" ) == (set<string>
  {
    "John Peter Taylor",
    "Peter John Taylor",
    "Peter Taylor"
  }) );
  assert ( x0 . Suggest ( "bond" ) == (set<string>
  {
    "Bond James",
    "James Bond"
  }) );
  assert ( x0 . Suggest ( "peter joHn" ) == (set<string>
  {
    "John Peter Taylor",
    "Peter John Taylor"
  }) );
  assert ( x0 . Suggest ( "peter joHn bond" ) == (set<string>
  {
  }) );
  assert ( x0 . Suggest ( "pete" ) == (set<string>
  {
  }) );
  assert ( x0 . Suggest ( "peter joHn PETER" ) == (set<string>
  {
    "John Peter Taylor",
    "Peter John Taylor"
  }) );
  assert ( ! x0 . AddStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
  assert ( x0 . DelStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
  assert ( x0 . Search ( CFilter () . BornAfter ( CDate ( 1980, 4, 11) ) . BornBefore ( CDate ( 1983, 7, 13) ) . Name ( "John Taylor" ) . Name ( "james BOND" ), CSort () . AddKey ( ESortKey::ENROLL_YEAR, false ) . AddKey ( ESortKey::BIRTH_DATE, false ) . AddKey ( ESortKey::NAME, true ) ) == (list<CStudent>
  {
    CStudent ( "James Bond", CDate ( 1982, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 8, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 17), 2013 ),
    CStudent ( "Bond James", CDate ( 1981, 7, 16), 2013 ),
    CStudent ( "James Bond", CDate ( 1981, 7, 16), 2012 ),
    CStudent ( "John Taylor", CDate ( 1981, 6, 30), 2012 )
  }) );
  assert ( ! x0 . DelStudent ( CStudent ( "James Bond", CDate ( 1981, 7, 16), 2013 ) ) );
   */
  return 0;
}
#endif /* __PROGTEST__ */