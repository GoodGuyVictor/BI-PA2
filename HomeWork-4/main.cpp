#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cassert>
#include <cctype>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;
#endif /* __PROGTEST__ */

class CMail
{
  public:
    CMail( const char * from, const char * to, const char * body );
    CMail() = default;
    CMail(const CMail & m);
    ~CMail();

    CMail & operator = (const CMail & m);
    bool operator == ( const CMail     & x ) const;
    char * getFrom() const { return m_from; }
    char * getTo() const { return m_to; }
    char * getBody() const { return m_body; }

  private:
    char * m_from;
    char * m_to;
    char * m_body;
};

CMail::CMail(const char *from, const char *to, const char *body)
{
    size_t from_size = strlen(from);
    size_t to_size = strlen(to);
    size_t body_size = strlen(body);

    m_from = new char[from_size + 1];
    m_to = new char[to_size + 1];
    m_body = new char[body_size + 1];

    strncpy(m_from, from, from_size);
    strncpy(m_to, to, to_size);
    strncpy(m_body, body, body_size);
}

CMail::~CMail()
{
    delete [] m_from;
    delete [] m_to;
    delete [] m_body;
}

bool CMail::operator==(const CMail &x) const
{
    if(strcmp(m_from, x.m_from) == 0
       && strcmp(m_to, x.m_to) == 0
       && strcmp(m_body, x.m_body) == 0)
        return true;
    return false;
}

CMail::CMail(const CMail &m)
: CMail(m.getFrom(), m.getTo(), m.getBody())
{}

CMail & CMail::operator = (const CMail &m)
{
    size_t from_size = strlen(m.getFrom());
    size_t to_size = strlen(m.getTo());
    size_t body_size = strlen(m.getBody());

    m_from = new char[from_size + 1];
    m_to = new char[to_size + 1];
    m_body = new char[body_size + 1];

    strncpy(m_from, m.getFrom(), from_size);
    strncpy(m_to, m.getTo(), to_size);
    strncpy(m_body, m.getBody(), body_size);
    return *this;
}

class CUser
{
public:
    explicit CUser(const char * email);
    CUser() = default;

    char * m_email;
    CMail ** m_inbox;
    CMail ** m_outbox;
    size_t m_inboxTop;
    size_t m_outboxTop;
    size_t m_inboxSize;
    size_t m_outboxSize;

    void insertOutbox(CMail *);
    void insertInbox(CMail *);
    void reallocOutbox();
    void reallocInbox();
};

void CUser::insertOutbox(CMail * m)
{
    m_outbox[m_outboxTop] = m;
    m_outboxTop++;
    if(m_outboxTop > m_outboxSize)
        reallocOutbox();
}

void CUser::insertInbox(CMail * m)
{
    m_inbox[m_inboxTop] = m;
    m_inboxTop++;
    if(m_inboxTop > m_inboxSize)
        reallocInbox();
}

CUser::CUser(const char *email)
{
    size_t email_len = strlen(email);
    m_email = new char[email_len + 1];
    strcpy(m_email, email);

    m_inboxSize = 500;
    m_outboxSize = 500;
    m_outboxTop = 0;
    m_inboxTop = 0;

    m_inbox = new CMail*[m_inboxSize];
    m_outbox = new CMail*[m_outboxSize];
}

class CMailIterator
{
  public:
                             operator bool                 ( void ) const;
    bool                     operator !                    ( void ) const;
    const CMail            & operator *                    ( void ) const;
    CMailIterator          & operator ++                   ( void );
  private:
    // todo
};

class CMailServer
{
  public:
                             CMailServer                   ( void );
                             CMailServer                   ( const CMailServer & src );
    CMailServer            & operator =                    ( const CMailServer & src );
                             ~CMailServer                  ( void );
    void                     SendMail                      ( const CMail     & m );
    CMailIterator            Outbox                        ( const char      * email ) const;
    CMailIterator            Inbox                         ( const char      * email ) const;

  
  private:

    struct TEmails
    {
        size_t m_size;
        size_t m_top;
        CMail * m_list;

        void realloc();
    } m_emails;

    struct TUsers
    {
        size_t m_size;
        size_t m_top;
        CUser * m_list;

        size_t findUser(char * usr) const;
        void addOutbox(CMail * m, size_t pos);
        void addInbox(CMail * m, size_t pos);
        void addNewUser(char * email, size_t pos);
    } m_users;

    void appendEmail(const CMail &);
};

//binary search
size_t CMailServer::TUsers::findUser(char * usr) const
{
    size_t first = 0;
    size_t last = m_top;

    while (first < last) {
        size_t mid = first + (last - first) / 2;

        if (strcmp(usr, m_list[mid].m_email) < 0
            || strcmp(usr, m_list[mid].m_email) == 0)
            last = mid;
        else
            first = mid + 1;
    }

    return last;
}

void CMailServer::TUsers::addOutbox(CMail * m, size_t pos)
{
    m_list[pos].insertOutbox(m);
}

void CMailServer::TUsers::addInbox(CMail *m, size_t pos)
{
    m_list[pos].insertInbox(m);
}

void CMailServer::TUsers::addNewUser(char * email, size_t pos)
{
    memmove(m_list + pos + 1, m_list + pos, m_top - pos);
    m_list[pos] = CUser(email);
    //todo
}

void CMailServer::TEmails::realloc()
{
    m_size += m_size / 2;
    CMail * tmp = new CMail[m_size];
    for(size_t i = 0; i < m_top; i++) {
        tmp[i] = m_list[i];
    }
    delete [] m_list;
    m_list = tmp;
}

CMailServer::CMailServer(void)
{
    m_emails.m_size = 500;
    m_emails.m_top = 0;
    m_emails.m_list = new CMail[500];

    m_users.m_size = 500;
    m_users.m_top = 0;
    m_users.m_list = new CUser[500];
}

void CMailServer::SendMail(const CMail &m)
{
    appendEmail(m);

    size_t last = m_emails.m_top - 1;
    char * sender = m_emails.m_list[last].getFrom();

    size_t userPos = m_users.findUser(sender);
    if(userPos != m_users.m_top)
        m_users.addOutbox(m_emails.m_list + last, userPos);
    else
        m_users.addNewUser(sender, userPos);

    char * receiver = m_emails.m_list[last].getTo();
    userPos = m_users.findUser(receiver);
    if(userPos != m_users.m_top)
        m_users.addInbox(m_emails.m_list + last, userPos);
    else
        m_users.addNewUser(receiver, userPos);
}

void CMailServer::appendEmail(const CMail &m)
{
    CMail copy(m.getFrom(), m.getTo(), m.getBody());
    if(m_emails.m_top == m_emails.m_size + 1)
        m_emails.realloc();
    size_t top = m_emails.m_top;
    m_emails.m_list[top] = copy;
    m_emails.m_top++;
}

CMailServer::~CMailServer(void)
{
//    for(size_t i = 0; i < m_allEmails.m_top; i++) {
//        delete [] m_allEmails.m_emails[i]->getFrom();
//        delete [] m_allEmails.m_emails[i]->getTo();
//        delete [] m_allEmails.m_emails[i]->getBody();
//        delete m_allEmails.m_emails[i];
//    }

//    for(size_t i = 0; i < m_inbox.m_top; i++) {
//        delete [] (*m_inbox.m_emails[i])->getFrom();
//        delete [] (*m_inbox.m_emails[i])->getTo();
//        delete [] (*m_inbox.m_emails[i])->getBody();
//        delete m_inbox.m_emails[i];
//    }

//    for(size_t i = 0; i < m_outbox.m_top; i++) {
//        delete [] m_outbox.m_emails[i]->getFrom();
//        delete [] m_outbox.m_emails[i]->getTo();
//        delete [] m_outbox.m_emails[i]->getBody();
//        delete m_outbox.m_emails[i];
//    }

//    delete [] m_allEmails.m_emails;
//    delete [] m_inbox.m_emails;
//    delete [] m_outbox.m_emails;
}

//CMail inbox[100];

#ifndef __PROGTEST__
int main ( void )
{

  char from[100], to[100], body[1024];

  assert ( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "peter", "progtest deadline" ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "progtest deadline", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "john", "progtest deadline" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "peter", "progtest deadline", "john" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "john", "peter" ) ) );
  assert ( !( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "progtest deadline", "peter", "john" ) ) );
  CMailServer s0;
  s0 . SendMail ( CMail ( "john", "peter", "some important mail" ) );
  strncpy ( from, "john", sizeof ( from ) );
  strncpy ( to, "thomas", sizeof ( to ) );
  strncpy ( body, "another important mail", sizeof ( body ) );
  s0 . SendMail ( CMail ( from, to, body ) );
  strncpy ( from, "john", sizeof ( from ) );
  strncpy ( to, "alice", sizeof ( to ) );
  strncpy ( body, "deadline notice", sizeof ( body ) );
  s0 . SendMail ( CMail ( from, to, body ) );
  s0 . SendMail ( CMail ( "alice", "john", "deadline confirmation" ) );
    s0 . SendMail ( CMail ( "peter", "alice", "PR bullshit" ) );
  /*CMailIterator i0 = s0 . Inbox ( "alice" );
  assert ( i0 && *i0 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i0 && *i0 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ! ++i0 );

  CMailIterator i1 = s0 . Inbox ( "john" );
  assert ( i1 && *i1 == CMail ( "alice", "john", "deadline confirmation" ) );
  assert ( ! ++i1 );

  CMailIterator i2 = s0 . Outbox ( "john" );
  assert ( i2 && *i2 == CMail ( "john", "peter", "some important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "thomas", "another important mail" ) );
  assert ( ++i2 && *i2 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ! ++i2 );

  CMailIterator i3 = s0 . Outbox ( "thomas" );
  assert ( ! i3 );

  CMailIterator i4 = s0 . Outbox ( "steve" );
  assert ( ! i4 );

  CMailIterator i5 = s0 . Outbox ( "thomas" );
  s0 . SendMail ( CMail ( "thomas", "boss", "daily report" ) );
  assert ( ! i5 );

  CMailIterator i6 = s0 . Outbox ( "thomas" );
  assert ( i6 && *i6 == CMail ( "thomas", "boss", "daily report" ) );
  assert ( ! ++i6 );

  CMailIterator i7 = s0 . Inbox ( "alice" );
  s0 . SendMail ( CMail ( "thomas", "alice", "meeting details" ) );
  assert ( i7 && *i7 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i7 && *i7 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ! ++i7 );

  CMailIterator i8 = s0 . Inbox ( "alice" );
  assert ( i8 && *i8 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i8 && *i8 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i8 && *i8 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ! ++i8 );

  CMailServer s1 ( s0 );
  s0 . SendMail ( CMail ( "joe", "alice", "delivery details" ) );
  s1 . SendMail ( CMail ( "sam", "alice", "order confirmation" ) );
  CMailIterator i9 = s0 . Inbox ( "alice" );
  assert ( i9 && *i9 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i9 && *i9 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i9 && *i9 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i9 && *i9 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( ! ++i9 );

  CMailIterator i10 = s1 . Inbox ( "alice" );
  assert ( i10 && *i10 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i10 && *i10 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i10 && *i10 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i10 && *i10 == CMail ( "sam", "alice", "order confirmation" ) );
  assert ( ! ++i10 );

  CMailServer s2;
  s2 . SendMail ( CMail ( "alice", "alice", "mailbox test" ) );
  CMailIterator i11 = s2 . Inbox ( "alice" );
  assert ( i11 && *i11 == CMail ( "alice", "alice", "mailbox test" ) );
  assert ( ! ++i11 );

  s2 = s0;
  s0 . SendMail ( CMail ( "steve", "alice", "newsletter" ) );
  s2 . SendMail ( CMail ( "paul", "alice", "invalid invoice" ) );
  CMailIterator i12 = s0 . Inbox ( "alice" );
  assert ( i12 && *i12 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i12 && *i12 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i12 && *i12 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i12 && *i12 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( ++i12 && *i12 == CMail ( "steve", "alice", "newsletter" ) );
  assert ( ! ++i12 );

  CMailIterator i13 = s2 . Inbox ( "alice" );
  assert ( i13 && *i13 == CMail ( "john", "alice", "deadline notice" ) );
  assert ( ++i13 && *i13 == CMail ( "peter", "alice", "PR bullshit" ) );
  assert ( ++i13 && *i13 == CMail ( "thomas", "alice", "meeting details" ) );
  assert ( ++i13 && *i13 == CMail ( "joe", "alice", "delivery details" ) );
  assert ( ++i13 && *i13 == CMail ( "paul", "alice", "invalid invoice" ) );
  assert ( ! ++i13 );
*/
  return 0;
}
#endif /* __PROGTEST__ */