#ifndef __PROGTEST__

#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <cmath>
#include <cassert>
#include <typeinfo>
#include <unistd.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <vector>
#include <list>
#include <string>
#include <map>
#include <set>
#include <unordered_map>
#include <unordered_set>
#include <functional>
#include <memory>
#include <algorithm>
#include <type_traits>
using namespace std;

class CRect
{
public:
    CRect                         ( double            x,
                                    double            y,
                                    double            w,
                                    double            h )
            : m_X ( x ),
              m_Y ( y ),
              m_W ( w ),
              m_H ( h )
    {
    }
    friend ostream         & operator <<                   ( ostream         & os,
                                                             const CRect     & x )
    {
        return os << '(' << x . m_X << ',' << x . m_Y << ',' << x . m_W << ',' << x . m_H << ')';
    }
    double                   m_X;
    double                   m_Y;
    double                   m_W;
    double                   m_H;
};
#endif /* __PROGTEST__ */

class CUnit
{
public:
    int m_id;
    CRect m_position;
    CUnit() = default;
    CUnit(const CRect & pos);
    CUnit(int id, const CRect & pos);
    virtual void Print(ostream &) const = 0;
    friend ostream & operator << (ostream & os, const CUnit & item);
};

CUnit::CUnit(const CRect &pos)
: m_position(pos)
{
}

CUnit::CUnit(int id, const CRect &pos)
: m_id(id), m_position(pos)
{
}

ostream &operator << (ostream &os, const CUnit &item)
{
    item.Print(os);
    return os;
}

class CWindow : public CUnit
{
public:
    CWindow                       ( const string    & title,
                                    const CRect     & absPos );

    void Print(ostream &) const override;
    CWindow & Add (const CUnit & unit);
    CUnit * Search(int id) const;
    // Add
    // Search
    // SetPosition
private:
    string m_title;
    vector<CUnit *> m_units;
};

CWindow::CWindow(const string &title, const CRect &absPos)
: CUnit(absPos), m_title(title)
{
}

void CWindow::Print(ostream & os) const
{
    os << "Window \"" << m_title << "\" " << m_position << "\n";
    if(!m_units.empty())
        for (const auto & it : m_units) {
            os << "+- ";
            it->Print(os);
        }
}

CWindow &CWindow::Add(const CUnit & unit)
{
    CUnit * tmp = const_cast<CUnit*> (&unit);
    tmp->m_position.m_X = tmp->m_position.m_X * m_position.m_W + m_position.m_X;
    tmp->m_position.m_Y = tmp->m_position.m_Y * m_position.m_H + m_position.m_Y;
    tmp->m_position.m_H = tmp->m_position.m_H * m_position.m_H;
    tmp->m_position.m_W = tmp->m_position.m_W * m_position.m_W;
    m_units.push_back(tmp);
    return *this;
}

CUnit *CWindow::Search(int id) const
{
    for(auto & it: m_units)
        if(it->m_id == id)
            return it;
    return NULL;
}

class CButton : public CUnit
{
public:
    CButton                       ( int               id,
                                    const CRect     & relPos,
                                    const string    & name );
    void Print(ostream &) const override;
private:
    string m_name;
};

CButton::CButton(int id, const CRect &relPos, const string &name)
: CUnit(id, relPos), m_name(name)
{
}

void CButton::Print(ostream & os) const
{
    os << "[" << m_id << "] Button \"" << m_name << "\" " << m_position << "\n";
}

class CInput : public CUnit
{
public:
    CInput                        ( int               id,
                                    const CRect     & relPos,
                                    const string    & value );
    void Print(ostream &) const override;
    string GetValue() const;
    void SetValue(const string &);
    // SetValue
    // GetValue
private:
    string m_value;
};

CInput::CInput(int id, const CRect &relPos, const string &value)
: CUnit(id, relPos), m_value(value)
{
}

void CInput::Print(ostream & os) const
{
    os << "[" << m_id << "] Input \"" << m_value << "\" " << m_position << "\n";
}

string CInput::GetValue() const
{
    return m_value;
}

void CInput::SetValue(const string & value)
{
    m_value = value;
}

class CLabel : public CUnit
{
public:
    CLabel                        ( int               id,
                                    const CRect     & relPos,
                                    const string    & label );
    void Print(ostream &) const override;

private:
    string m_label;

};

CLabel::CLabel(int id, const CRect &relPos, const string &label)
: CUnit(id, relPos), m_label(label)
{
}

void CLabel::Print(ostream & os) const
{
    os << "[" << m_id << "] Label \"" << m_label << "\" " << m_position << "\n";
}

class CComboBox : public CUnit
{
public:
    CComboBox                     ( int               id,
                                    const CRect     & relPos );
    void Print(ostream &) const override;
    CComboBox & Add(const string &);
    int GetSelected() const;
    void SetSelected(int);
    // GetSelected
    // SetSelected
    // Add
private:
    int m_selected;
    vector<string> m_items;
};

CComboBox::CComboBox(int id, const CRect &relPos)
: CUnit(id, relPos), m_selected(0)
{
}

void CComboBox::Print(ostream &os) const
{
    os << "[" << m_id << "] ComboBox \"" << "\" " << m_position << "\n";
    for(int i = 0; i < m_items.size(); i++) {
        if(i == m_selected)
            os << "+->" << m_items[i] << "<\n";
        else
            os << "+- " << m_items[i] << "\n";
    }
}

CComboBox &CComboBox::Add(const string & item)
{
    m_items.push_back(item);
    return *this;
}

int CComboBox::GetSelected() const
{
    return m_selected;
}

void CComboBox::SetSelected(int selected)
{
    m_selected = selected;
}

// output operators

#ifndef __PROGTEST__
template <typename _T>
string toString ( const _T & x )
{
    ostringstream oss;
    oss << x;
    return oss . str ();
}

int main ( void )
{
//    assert ( sizeof ( CButton ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
//    assert ( sizeof ( CInput ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );
//    assert ( sizeof ( CLabel ) - sizeof ( string ) < sizeof ( CComboBox ) - sizeof ( vector<string> ) );

    CWindow a ( "Sample window", CRect ( 10, 10, 600, 480 ) );
    a . Add ( CButton ( 1, CRect ( 0.1, 0.8, 0.3, 0.1 ), "Ok" ) ) . Add ( CButton ( 2, CRect ( 0.6, 0.8, 0.3, 0.1 ), "Cancel" ) );
    a . Add ( CLabel ( 10, CRect ( 0.1, 0.1, 0.2, 0.1 ), "Username:" ) );
    a . Add ( CInput ( 11, CRect ( 0.4, 0.1, 0.5, 0.1 ), "chucknorris" ) );
    a . Add ( CComboBox ( 20, CRect ( 0.1, 0.3, 0.8, 0.1 ) ) . Add ( "Karate" ) . Add ( "Judo" ) . Add ( "Box" ) . Add ( "Progtest" ) );
    cout << toString(a);
    /*assert ( toString ( a ) ==
             "Window \"Sample window\" (10,10,600,480)\n"
                     "+- [1] Button \"Ok\" (70,394,180,48)\n"
                     "+- [2] Button \"Cancel\" (370,394,180,48)\n"
                     "+- [10] Label \"Username:\" (70,58,120,48)\n"
                     "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
                     "+- [20] ComboBox (70,154,480,48)\n"
                     "   +->Karate<\n"
                     "   +- Judo\n"
                     "   +- Box\n"
                     "   +- Progtest\n" );
    CWindow b = a;
    assert ( toString ( *b . Search ( 20 ) ) ==
             "[20] ComboBox (70,154,480,48)\n"
                     "+->Karate<\n"
                     "+- Judo\n"
                     "+- Box\n"
                     "+- Progtest\n" );
    assert ( dynamic_cast<CComboBox &> ( *b . Search ( 20 ) ) . GetSelected () == 0 );
    dynamic_cast<CComboBox &> ( *b . Search ( 20 ) ) . SetSelected ( 3 );
    assert ( dynamic_cast<CInput &> ( *b . Search ( 11 ) ) . GetValue () == "chucknorris" );
    dynamic_cast<CInput &> ( *b . Search ( 11 ) ) . SetValue ( "chucknorris@fit.cvut.cz" );
    b . Add ( CComboBox ( 21, CRect ( 0.1, 0.5, 0.8, 0.1 ) ) . Add ( "PA2" ) . Add ( "OSY" ) . Add ( "Both" ) );
    assert ( toString ( b ) ==
             "Window \"Sample window\" (10,10,600,480)\n"
                     "+- [1] Button \"Ok\" (70,394,180,48)\n"
                     "+- [2] Button \"Cancel\" (370,394,180,48)\n"
                     "+- [10] Label \"Username:\" (70,58,120,48)\n"
                     "+- [11] Input \"chucknorris@fit.cvut.cz\" (250,58,300,48)\n"
                     "+- [20] ComboBox (70,154,480,48)\n"
                     "|  +- Karate\n"
                     "|  +- Judo\n"
                     "|  +- Box\n"
                     "|  +->Progtest<\n"
                     "+- [21] ComboBox (70,250,480,48)\n"
                     "   +->PA2<\n"
                     "   +- OSY\n"
                     "   +- Both\n" );
    assert ( toString ( a ) ==
             "Window \"Sample window\" (10,10,600,480)\n"
                     "+- [1] Button \"Ok\" (70,394,180,48)\n"
                     "+- [2] Button \"Cancel\" (370,394,180,48)\n"
                     "+- [10] Label \"Username:\" (70,58,120,48)\n"
                     "+- [11] Input \"chucknorris\" (250,58,300,48)\n"
                     "+- [20] ComboBox (70,154,480,48)\n"
                     "   +->Karate<\n"
                     "   +- Judo\n"
                     "   +- Box\n"
                     "   +- Progtest\n" );
    b . SetPosition ( CRect ( 20, 30, 640, 520 ) );
    assert ( toString ( b ) ==
             "Window \"Sample window\" (20,30,640,520)\n"
                     "+- [1] Button \"Ok\" (84,446,192,52)\n"
                     "+- [2] Button \"Cancel\" (404,446,192,52)\n"
                     "+- [10] Label \"Username:\" (84,82,128,52)\n"
                     "+- [11] Input \"chucknorris@fit.cvut.cz\" (276,82,320,52)\n"
                     "+- [20] ComboBox (84,186,512,52)\n"
                     "|  +- Karate\n"
                     "|  +- Judo\n"
                     "|  +- Box\n"
                     "|  +->Progtest<\n"
                     "+- [21] ComboBox (84,290,512,52)\n"
                     "   +->PA2<\n"
                     "   +- OSY\n"
                     "   +- Both\n" );*/
    return 0;
}
#endif /* __PROGTEST__ */