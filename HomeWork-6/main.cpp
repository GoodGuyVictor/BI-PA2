#ifndef __PROGTEST__
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <climits>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <deque>
#include <map>
#include <set>
#include <list>
#include <algorithm>
#include <functional>
#include <iterator>
#include <memory>
#include <stdexcept>
using namespace std;
#endif /* __PROGTEST__ */

// enable only if your implementation supports Add ( ) with more than three parameters
// #define MULTIPLE_STOPS


template <typename _T, typename _E>
struct TVertex
{
    typedef pair<_E, TVertex*> ve;
    vector<ve> m_adj;
    _T m_name;
    int m_distanceTo;
    explicit TVertex(_T name) : m_name(name), m_distanceTo(0) {}
};

template <typename _T, typename _E>
class CAccess
{
public:
    CAccess() = default;
    ~CAccess();
    CAccess<_T, _E> & Add(const _E & e, const _T & u1, const _T & u2);

    template <typename _F>
    map<_T, int> Find(const _T & u, int max, _F func) const;
    map<_T, int> Find(const _T & u, int max = 0) const;


    // default constructor
    // destructor
    // Add
    // Find (with optional max and filter)
private:
    map<_T, TVertex<_T, _E>*> m_theMap;
    void addVertex(const _T &name);
    void addEdge(const _T &from, const _T &to, const _E & cost);
};

template<typename _T, typename _E>
CAccess<_T, _E>::~CAccess()
{
    for(auto & it : m_theMap)
        delete it.second;
}

template<typename _T, typename _E>
void CAccess<_T, _E>::addVertex(const _T &name)
{
    auto it = m_theMap.find(name);
    if (it == m_theMap.end())
    {
        TVertex<_T, _E> *v;
        v = new TVertex<_T, _E>(name);
        m_theMap[name] = v;
        return;
    }
}

template<typename _T, typename _E>
void CAccess<_T, _E>::addEdge(const _T &from, const _T &to, const _E & cost)
{
    TVertex<_T, _E> *f = (m_theMap.find(from)->second);
    TVertex<_T, _E> *t = (m_theMap.find(to)->second);
    pair<_E, TVertex<_T, _E> *> edge = make_pair(cost, t);
    f->m_adj.push_back(edge);
}

template<typename _T, typename _E>
CAccess<_T, _E> & CAccess<_T, _E>::Add(const _E &e, const _T &u1, const _T &u2)
{
    auto it = m_theMap.find(u1);
    if(it == m_theMap.end())
        addVertex(u1);
    it = m_theMap.find(u2);
    if(it == m_theMap.end())
        addVertex(u2);

    addEdge(u1, u2, e);
    addEdge(u2, u1, e);

    return *this;
}

template<typename _T, typename _E>
template<typename _F>
map<_T, int> CAccess<_T, _E>::Find(const _T &u, int max, _F func) const
{
    map<_T, int> distanceContainer;
    map<_T, bool> visited;
    _T vertex = u;

    if(m_theMap.find(u) == m_theMap.end()) {
        ostringstream os;
        os << "unknown " << u;
        throw invalid_argument ( os.str() );
    }

    // Mark all the vertices as not visited
    for(auto & it: m_theMap)
        visited[it.first] = false;

    // Create a queue for BFS
    list<_T> queue;

    //Set distanceTo of the current node to zero
    int distanceTo = 0;
    m_theMap.find(vertex)->second->m_distanceTo = 0;
    distanceContainer[vertex] = 0;

    // Mark the current node as visited and enqueue it
    visited[vertex] = true;
    queue.push_back(vertex);

    while(!queue.empty())
    {

        // Dequeue a vertex from queue
        vertex = queue.front();
        queue.pop_front();

        //Get vertex in m_theMap
        auto vtx = m_theMap.find(vertex);

        //Increment distanceTo for its adjacents
        distanceTo = vtx->second->m_distanceTo + 1;

        if(distanceTo > max && max != 0)
            continue;

        // Get all adjacent vertices of the dequeued
        // vertex. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for(auto & adj : vtx->second->m_adj )
        {
            if(func(adj.first))
                if (!visited[adj.second->m_name])
                {
                    adj.second->m_distanceTo = distanceTo;
                    queue.push_back(adj.second->m_name);
                    visited[adj.second->m_name] = true;
                    distanceContainer[adj.second->m_name] = distanceTo;
                }
        }
    }
    return distanceContainer;
}

template<typename _T, typename _E>
map<_T, int> CAccess<_T, _E>::Find(const _T &u, int max) const
{
    map<_T, int> distanceContainer;
    map<_T, bool> visited;
    _T vertex = u;

    if(m_theMap.find(u) == m_theMap.end()) {
        ostringstream os;
        os << "unknown " << u;
        throw invalid_argument ( os.str() );
    }

    // Mark all the vertices as not visited
    for(auto & it: m_theMap)
        visited[it.first] = false;

    // Create a queue for BFS
    list<_T> queue;

    //Set distanceTo of the current node to zero
    int distanceTo = 0;
    m_theMap.find(vertex)->second->m_distanceTo = 0;
    distanceContainer[vertex] = 0;

    // Mark the current node as visited and enqueue it
    visited[vertex] = true;
    queue.push_back(vertex);

    while(!queue.empty())
    {

        // Dequeue a vertex from queue
        vertex = queue.front();
        queue.pop_front();

        //Get vertex in m_theMap
        auto vtx = m_theMap.find(vertex);

        //Increment distanceTo for its adjacents
        distanceTo = vtx->second->m_distanceTo + 1;

        if(distanceTo > max && max != 0)
            continue;

        // Get all adjacent vertices of the dequeued
        // vertex. If a adjacent has not been visited,
        // then mark it visited and enqueue it
        for(auto & adj : vtx->second->m_adj )
        {
            if (!visited[adj.second->m_name])
            {
                adj.second->m_distanceTo = distanceTo;
                queue.push_back(adj.second->m_name);
                visited[adj.second->m_name] = true;
                distanceContainer[adj.second->m_name] = distanceTo;
            }
        }
    }
    return distanceContainer;
}

#ifndef __PROGTEST__
//=================================================================================================
class CTrain
{
public:
    CTrain                        ( const string    & company,
                                    int               speed )
            : m_Company ( company ),
              m_Speed ( speed )
    {
    }
    //---------------------------------------------------------------------------------------------
    string                   m_Company;
    int                      m_Speed;
};
//=================================================================================================
class TrainFilterCompany
{
public:
    TrainFilterCompany            ( const set<string> & companies )
            : m_Companies ( companies )
    {
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain & train ) const
    {
        return m_Companies . find ( train . m_Company ) != m_Companies . end ();
    }
    //---------------------------------------------------------------------------------------------
private:
    set <string>             m_Companies;
};
//=================================================================================================
class TrainFilterSpeed
{
public:
    TrainFilterSpeed              ( int               min,
                                    int               max )
            : m_Min ( min ),
              m_Max ( max )
    {
    }
    //---------------------------------------------------------------------------------------------
    bool                     operator ()                   ( const CTrain    & train ) const
    {
        return train . m_Speed >= m_Min && train . m_Speed <= m_Max;
    }
    //---------------------------------------------------------------------------------------------
private:
    int                      m_Min;
    int                      m_Max;
};
//=================================================================================================
bool                         NurSchnellzug                 ( const CTrain    & zug )
{
    return ( zug . m_Company == "OBB" || zug . m_Company == "DB" ) && zug . m_Speed > 100;
}
//=================================================================================================
int                          main                          ( void )
{
    CAccess<string,CTrain> lines;
    lines . Add ( CTrain (   "DB", 120 ), "Berlin", "Prague"   )
            . Add ( CTrain (   "CD",  80 ), "Berlin", "Prague"   )
            . Add ( CTrain (   "DB", 160 ), "Berlin", "Dresden"  )
            . Add ( CTrain (   "DB", 160 ), "Dresden", "Munchen" )
            . Add ( CTrain (   "CD",  90 ), "Munchen", "Prague"  )
            . Add ( CTrain (   "DB", 200 ), "Munchen", "Linz"    )
            . Add ( CTrain (  "OBB",  90 ), "Munchen", "Linz"    )
            . Add ( CTrain (   "CD",  50 ), "Linz", "Prague"     )
            . Add ( CTrain (   "CD", 100 ), "Prague", "Wien"     )
            . Add ( CTrain (  "OBB", 160 ), "Linz", "Wien"       )
            . Add ( CTrain ( "SNCF", 300 ), "Paris", "Marseille" )
            . Add ( CTrain ( "SNCF", 250 ), "Paris", "Dresden"   )
            . Add ( CTrain ( "SNCF", 200 ), "London", "Calais"   );

   assert ( lines . Find ( "Berlin" ) == (map<string,int>
            {
                    make_pair ( "Berlin", 0 ),
                    make_pair ( "Dresden", 1 ),
                    make_pair ( "Linz", 2 ),
                    make_pair ( "Marseille", 3 ),
                    make_pair ( "Munchen", 2 ),
                    make_pair ( "Paris", 2 ),
                    make_pair ( "Prague", 1 ),
                    make_pair ( "Wien", 2 )
            }) );
    assert ( lines . Find ( "London" ) == (map<string,int>
            {
                    make_pair ( "Calais", 1 ),
                    make_pair ( "London", 0 )
            }) );
    assert ( lines . Find ( "Wien" ) == (map<string,int>
            {
                    make_pair ( "Berlin", 2 ),
                    make_pair ( "Dresden", 3 ),
                    make_pair ( "Linz", 1 ),
                    make_pair ( "Marseille", 5 ),
                    make_pair ( "Munchen", 2 ),
                    make_pair ( "Paris", 4 ),
                    make_pair ( "Prague", 1 ),
                    make_pair ( "Wien", 0 )
            }) );
    assert ( lines . Find ( "Wien", 3 ) == (map<string,int>
            {
                    make_pair ( "Berlin", 2 ),
                    make_pair ( "Dresden", 3 ),
                    make_pair ( "Linz", 1 ),
                    make_pair ( "Munchen", 2 ),
                    make_pair ( "Prague", 1 ),
                    make_pair ( "Wien", 0 )
            }) );
    assert ( lines . Find ( "Wien", 5, NurSchnellzug ) == (map<string,int>
            {
                    make_pair ( "Berlin", 4 ),
                    make_pair ( "Dresden", 3 ),
                    make_pair ( "Linz", 1 ),
                    make_pair ( "Munchen", 2 ),
                    make_pair ( "Prague", 5 ),
                    make_pair ( "Wien", 0 )
            }) );
    assert ( lines . Find ( "Prague", 3,  TrainFilterCompany ( { "CD", "DB" } ) ) == (map<string,int>
            {
                    make_pair ( "Berlin", 1 ),
                    make_pair ( "Dresden", 2 ),
                    make_pair ( "Linz", 1 ),
                    make_pair ( "Munchen", 1 ),
                    make_pair ( "Prague", 0 ),
                    make_pair ( "Wien", 1 )
            }) );
    assert ( lines . Find ( "Munchen", 4, TrainFilterSpeed ( 160, 250 ) ) == (map<string,int>
            {
                    make_pair ( "Berlin", 2 ),
                    make_pair ( "Dresden", 1 ),
                    make_pair ( "Linz", 1 ),
                    make_pair ( "Munchen", 0 ),
                    make_pair ( "Paris", 2 ),
                    make_pair ( "Wien", 2 )
            }) );
    assert ( lines . Find ( "Munchen", 4, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
            {
                    make_pair ( "Berlin", 2 ),
                    make_pair ( "Linz", 2 ),
                    make_pair ( "Munchen", 0 ),
                    make_pair ( "Prague", 1 ),
                    make_pair ( "Wien", 2 )
            }) );
    assert ( lines . Find ( "London", 20, [] ( const CTrain & x ) { return x . m_Company == "CD"; } ) == (map<string,int>
            {
                    make_pair ( "London", 0 )
            }) );
    try
    {
        auto res = lines . Find ( "Salzburg" );
        assert ( "No exception thrown" == NULL );
    }
    catch ( const invalid_argument & e )
    {
        assert ( string ( e . what () ) == "unknown Salzburg" );
    }
#ifdef MULTIPLE_STOPS
    lines . Add ( CTrain ( "RZD",  80 ), "Prague", "Kiev", "Moscow", "Omsk", "Irkutsk", "Vladivostok" );
  lines . Add ( CTrain ( "LAV", 160 ), "Malaga", "Cordoba", "Toledo", "Madrid", "Zaragoza", "Tarragona", "Barcelona", "Montpellier", "Marseille" );
  assert ( lines . Find ( "Madrid" ) == (map<string,int>
  {
    make_pair ( "Barcelona", 1 ),
    make_pair ( "Berlin", 4 ),
    make_pair ( "Cordoba", 1 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 6 ),
    make_pair ( "Kiev", 6 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Madrid", 0 ),
    make_pair ( "Malaga", 1 ),
    make_pair ( "Marseille", 1 ),
    make_pair ( "Montpellier", 1 ),
    make_pair ( "Moscow", 6 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 6 ),
    make_pair ( "Paris", 2 ),
    make_pair ( "Prague", 5 ),
    make_pair ( "Tarragona", 1 ),
    make_pair ( "Toledo", 1 ),
    make_pair ( "Vladivostok", 6 ),
    make_pair ( "Wien", 6 ),
    make_pair ( "Zaragoza", 1 )
  }) );
  assert ( lines . Find ( "Omsk", 4 ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 2 ),
    make_pair ( "Moscow", 1 ),
    make_pair ( "Munchen", 2 ),
    make_pair ( "Omsk", 0 ),
    make_pair ( "Paris", 4 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 ),
    make_pair ( "Wien", 2 )
  }) );
  assert ( lines . Find ( "Moscow", 10, TrainFilterCompany ( { "RZD", "DB" } ) ) == (map<string,int>
  {
    make_pair ( "Berlin", 2 ),
    make_pair ( "Dresden", 3 ),
    make_pair ( "Irkutsk", 1 ),
    make_pair ( "Kiev", 1 ),
    make_pair ( "Linz", 5 ),
    make_pair ( "Moscow", 0 ),
    make_pair ( "Munchen", 4 ),
    make_pair ( "Omsk", 1 ),
    make_pair ( "Prague", 1 ),
    make_pair ( "Vladivostok", 1 )
  }) );
#endif /* MULTIPLE_STOPS */
    return 0;
}
#endif  /* __PROGTEST__ */