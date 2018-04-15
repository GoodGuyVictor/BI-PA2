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

/******************************************************************/
class CMail
{
  public:
    CMail( const char * from, const char * to, const char * body );
    ~CMail();

    bool operator == ( const CMail     & x ) const;
    char * getFrom() const { return m_from; }
    char * getTo() const { return m_to; }
    char * getBody() const { return m_body; }
    void free();

  private:
    char * m_from;
    char * m_to;
    char * m_body;
};

CMail::CMail(const char *from, const char *to, const char *body)
{
    size_t from_size = strlen(from) + 1;
    size_t to_size = strlen(to) + 1;
    size_t body_size = strlen(body) + 1;

    m_from = new char[from_size];
    m_to = new char[to_size];
    m_body = new char[body_size];

    strncpy(m_from, from, from_size);
    strncpy(m_to, to, to_size);
    strncpy(m_body, body, body_size);
}

CMail::~CMail()
{
    free();
}

bool CMail::operator==(const CMail &x) const
{
    return strcmp(m_from, x.m_from) == 0
           && strcmp(m_to, x.m_to) == 0
           && strcmp(m_body, x.m_body) == 0;
}

void CMail::free()
{
    delete [] m_from;
    delete [] m_to;
    delete [] m_body;
}
/******************************************************************/

/******************************************************************/
class CUser
{
public:
    explicit CUser(const char * email);
    CUser(const CUser & src);
    ~CUser();

    char * m_email;
//    CMail *** m_inbox;
//    CMail *** m_outbox;
    size_t * m_inbox;
    size_t * m_outbox;
    size_t m_inboxTop;
    size_t m_outboxTop;
    size_t m_inboxSize;
    size_t m_outboxSize;

    void insertOutbox(size_t p);
    void insertInbox(size_t p);
    void reallocOutbox();
    void reallocInbox();
    void free();
};

CUser::CUser(const char *email)
{
    size_t email_len = strlen(email) + 1;
    m_email = new char[email_len];
    strcpy(m_email, email);

    m_inboxSize = 1000;
    m_outboxSize = 1000;
    m_outboxTop = 0;
    m_inboxTop = 0;

    m_inbox = new size_t[m_inboxSize];
    m_outbox = new size_t[m_outboxSize];
}

CUser::CUser(const CUser &src)
{
    size_t email_len = strlen(src.m_email) + 1;
    m_email = new char[email_len];
    strcpy(m_email, src.m_email);

    m_inboxSize = src.m_inboxSize;
    m_outboxSize = src.m_outboxSize;
    m_outboxTop = src.m_outboxTop;
    m_inboxTop = src.m_inboxTop;

    m_inbox = new size_t[m_inboxSize];
    m_outbox = new size_t[m_outboxSize];

    for (size_t i = 0; i < m_inboxTop; ++i) {
        m_inbox[i] = src.m_inbox[i];
    }

    for (size_t i = 0; i < m_outboxTop; ++i) {
        m_outbox[i] = src.m_outbox[i];
    }
}

CUser::~CUser()
{
    free();
}

void CUser::insertOutbox(size_t p)
{
    if(m_outboxTop > m_outboxSize - 1)
        reallocOutbox();
    m_outbox[m_outboxTop] = p;
    m_outboxTop++;
}

void CUser::insertInbox(size_t p)
{
    if(m_inboxTop > m_inboxSize - 1)
        reallocInbox();
    m_inbox[m_inboxTop] = p;
    m_inboxTop++;
}

void CUser::reallocOutbox()
{
    if(m_outboxSize > 10000)
        m_outboxSize += m_outboxSize / 2;
    else
        m_outboxSize += m_outboxSize;

    size_t * tmp = new size_t[m_outboxSize];
    for(size_t i = 0; i < m_outboxTop; i++) {
        tmp[i] = m_outbox[i];
    }
    delete [] m_outbox;
    m_outbox = tmp;
}

void CUser::reallocInbox()
{
    if(m_inboxSize > 10000)
        m_inboxSize += m_inboxSize / 2;
    else
        m_inboxSize += m_inboxSize;

    size_t * tmp = new size_t[m_inboxSize];
    for(size_t i = 0; i < m_inboxTop; i++) {
        tmp[i] = m_inbox[i];
    }
    delete [] m_inbox;
    m_inbox = tmp;
}

void CUser::free()
{
    delete [] m_email;
    delete [] m_inbox;
    delete [] m_outbox;
}
/******************************************************************/

/******************************************************************/
class CEmailsStorage
{
public:

    CMail ** m_storage;
    size_t m_size;
    size_t m_top;
    size_t refCounter;

    CEmailsStorage();

    ~CEmailsStorage();

    void reallocStorage();
};

CEmailsStorage::CEmailsStorage()
{
    m_size = 1000;
    m_top = 0;
    m_storage = new CMail*[1000];
    refCounter = 1;
}

CEmailsStorage::~CEmailsStorage()
{
    for (size_t i = 0; i < m_top; ++i) {
        delete m_storage[i];
    }
    delete [] m_storage;
    m_size = 0;
    m_top = 0;
}

void CEmailsStorage::reallocStorage()
{
    if(m_size > 10000)
        m_size += m_size / 2;
    else
        m_size += m_size;

    CMail ** tmp = new CMail*[m_size];
    for (size_t i = 0; i < m_top; ++i) {
        tmp[i] = m_storage[i];
    }
    delete [] m_storage;
    m_storage = tmp;
}
/******************************************************************/

/******************************************************************/
class CMailIterator
{
  public:
                             operator bool                 ( void ) const;
    bool                     operator !                    ( void ) const;
    const CMail            & operator *                    ( void ) const;
    CMailIterator          & operator ++                   ( void );
    CMailIterator(size_t * ptr, size_t l, CEmailsStorage * emails);
    CMailIterator(const CMailIterator &src);
    CMailIterator & operator=(const CMailIterator & src);
    ~CMailIterator();
  private:
//    CMail *** m_begin;
//    CMail *** m_current;
    size_t * m_container;
    size_t m_len;
    size_t m_index;
    CEmailsStorage * m_allEmails;
};

CMailIterator::CMailIterator(size_t * ptr, size_t l, CEmailsStorage * emails)
{
    m_allEmails = emails;
    if(l > 0) {
        m_len = l;
        m_index = 0;

        m_container = new size_t[m_len];
        for (size_t i = 0; i < m_len; ++i) {
            m_container[i] = ptr[i];
        }
    }else {
        m_container = NULL;
        m_len = 0;
        m_index = 0;
    }
}

const CMail & CMailIterator::operator*(void) const
{
    size_t i = m_container[m_index];
//    return (*(*(m_container[m_index])));
    return *(m_allEmails->m_storage[i]);
}

CMailIterator::operator bool(void) const
{
    if(m_container == NULL)
        return false;

    return m_index < m_len;
}

CMailIterator & CMailIterator::operator++(void)
{
    ++m_index;
    return *this;
}

bool CMailIterator::operator!(void) const
{
    return !(operator bool());
}

CMailIterator::~CMailIterator()
{
    if(m_container) {
        delete [] m_container;
        m_len = 0;
        m_index = 0;
    }
}

CMailIterator::CMailIterator(const CMailIterator &src)
{
    m_allEmails = src.m_allEmails;
    if(src.m_container) {
        m_len = src.m_len;
        m_index = src.m_index;
        m_container = new size_t[m_len];

        for (size_t i = 0; i < m_len; ++i) {
            m_container[i] = src.m_container[i];
        }
    } else {
        m_container = NULL;
        m_len = 0;
        m_index = 0;
    }
}

CMailIterator &CMailIterator::operator=(const CMailIterator &src)
{
    if(this == &src)
        return *this;

    m_allEmails = src.m_allEmails;
    if(m_len > 0)
        delete [] m_container;

    m_len = src.m_len;
    m_index = src.m_index;
    m_container = new size_t[m_len];
    for (size_t i = 0; i < m_len; ++i) {
        m_container[i] = src.m_container[i];
    }
    return *this;
}

/******************************************************************/

/******************************************************************/
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

    CEmailsStorage * m_allEmails;

    struct TUsers
    {
        size_t m_size;
        size_t m_top;
        CUser ** m_list;

        size_t findUser(const char * usr) const;
        void addOutbox(size_t usr, size_t mail);
        void addInbox(size_t usr, size_t mail);
        void addNewUser(char * email, size_t pos);
        void shiftRight(size_t pos);
        void realloc();
    } m_users;

    void appendEmail(const CMail &);
};

CMailServer::CMailServer(void)
{
    m_allEmails = new CEmailsStorage();

    m_users.m_size = 1000;
    m_users.m_top = 0;
    m_users.m_list = new CUser*[1000];
}

CMailServer::CMailServer(const CMailServer &src)
{
    m_allEmails = src.m_allEmails;
    m_allEmails->refCounter++;

    m_users.m_size = src.m_users.m_size;
    m_users.m_top = src.m_users.m_top;
    m_users.m_list = new CUser*[m_users.m_size];

    for (size_t i = 0; i < m_users.m_top; ++i) {
        m_users.m_list[i] = new CUser(*(src.m_users.m_list[i]));
    }
}

CMailServer & CMailServer::operator=(const CMailServer &src)
{
    if(this == &src)
        return *this;


    m_allEmails->refCounter--;
    if(m_allEmails->refCounter == 0)
        delete m_allEmails;
    m_allEmails = src.m_allEmails;
    m_allEmails->refCounter++;


    for (size_t i = 0; i < m_users.m_top; i++) {
        delete m_users.m_list[i];
    }
    delete [] m_users.m_list;

    m_users.m_size = src.m_users.m_size;
    m_users.m_top = src.m_users.m_top;
    m_users.m_list = new CUser*[m_users.m_size];

    for (size_t i = 0; i < m_users.m_top; ++i) {
        m_users.m_list[i] = new CUser(*(src.m_users.m_list[i]));
    }
    return *this;
}

CMailServer::~CMailServer(void)
{
    //handling emails
    m_allEmails->refCounter--;
    if(m_allEmails->refCounter == 0)
        delete m_allEmails;

    //deleting users
    for (size_t i = 0; i < m_users.m_top; i++) {
        delete m_users.m_list[i];
    }
    delete [] m_users.m_list;
    m_users.m_size = 0;
    m_users.m_top = 0;
}

void CMailServer::SendMail(const CMail &m)
{
    appendEmail(m);

    size_t last = m_allEmails->m_top - 1;
    char * sender = m_allEmails->m_storage[last]->getFrom();
    char * receiver = m_allEmails->m_storage[last]->getTo();
    size_t userPos;

    userPos = m_users.findUser(sender);
    if(userPos != m_users.m_top) {
        if(strcmp(m_users.m_list[userPos]->m_email, sender) == 0) {
            m_users.addOutbox(userPos, last);
        }
        else {
            m_users.addNewUser(sender, userPos);
            m_users.addOutbox(userPos, last);
        }
    }
    else {
        m_users.addNewUser(sender, userPos);
        m_users.addOutbox(userPos, last);
    }

    userPos = m_users.findUser(receiver);
    if(userPos != m_users.m_top) {
        if(strcmp(m_users.m_list[userPos]->m_email, receiver) == 0)
            m_users.addInbox(userPos, last);
        else {
            m_users.addNewUser(receiver, userPos);
            m_users.addInbox(userPos, last);
        }
    }
    else {
        m_users.addNewUser(receiver, userPos);
        m_users.addInbox(userPos, userPos);
    }
}

CMailIterator CMailServer::Inbox(const char *email) const
{
    if(strcmp(email, "") == 0)
        return CMailIterator(NULL, 0, NULL);

    size_t userPos = m_users.findUser(email);

    if(userPos == m_users.m_top)
        return CMailIterator(NULL, 0, NULL);

    if(strcmp(m_users.m_list[userPos]->m_email, email) == 0)
        return CMailIterator(m_users.m_list[userPos]->m_inbox, m_users.m_list[userPos]->m_inboxTop, m_allEmails);

    return CMailIterator(NULL, 0, NULL);
}

CMailIterator CMailServer::Outbox(const char *email) const
{
    if(strcmp(email, "") == 0)
        return CMailIterator(NULL, 0, NULL);

    size_t userPos = m_users.findUser(email);

    if(userPos == m_users.m_top)
        return CMailIterator(NULL, 0, NULL);

    if(strcmp(m_users.m_list[userPos]->m_email, email) == 0)
        return CMailIterator(m_users.m_list[userPos]->m_outbox, m_users.m_list[userPos]->m_outboxTop, m_allEmails);

    return CMailIterator(NULL, 0, NULL);
}

//binary search
size_t CMailServer::TUsers::findUser(const char * usr) const
{
    size_t first = 0;
    size_t last = m_top;

    while (first < last) {
        size_t mid = first + (last - first) / 2;

        if (strcmp(usr, m_list[mid]->m_email) < 0
            || strcmp(usr, m_list[mid]->m_email) == 0)
            last = mid;
        else
            first = mid + 1;
    }

    return last;
}

void CMailServer::TUsers::addOutbox(size_t usr, size_t mail)
{
    m_list[usr]->insertOutbox(mail);
}

void CMailServer::TUsers::addInbox(size_t usr, size_t mail)
{
    m_list[usr]->insertInbox(mail);
}

void CMailServer::TUsers::addNewUser(char * email, size_t pos)
{
    if(pos == m_top)
        m_list[pos] = new CUser(email);
    else {
        shiftRight(pos);
        m_list[pos] = new CUser(email);
    }
    m_top++;
}

void CMailServer::TUsers::shiftRight(size_t pos)
{
    if(m_top > m_size - 1)
        realloc();
    for (size_t i = m_top; i > pos; i--)
        m_list[i] = m_list[i - 1];
}

void CMailServer::TUsers::realloc()
{
    if(m_size > 10000)
        m_size += m_size / 2;
    else
        m_size += m_size;

    CUser ** tmp = new CUser*[m_size];
    for (size_t i = 0; i < m_top; ++i) {
        tmp[i] = m_list[i];
    }
    delete [] m_list;
    m_list = tmp;
}

void CMailServer::appendEmail(const CMail &m)
{
    CMail * copy = new CMail(m.getFrom(), m.getTo(), m.getBody());
    if(m_allEmails->m_top > m_allEmails->m_size - 1)
        m_allEmails->reallocStorage();
    size_t top = m_allEmails->m_top;
    m_allEmails->m_storage[top] = copy;
    m_allEmails->m_top++;
}
/******************************************************************/

#ifndef __PROGTEST__
int main ( void )
{

  char from[100], to[100], body[1024];

//    CMailServer s10;
//
//    for (int i = 0; i < 3000; ++i) {
//        s10 . SendMail ( CMail ( "john", "peter", "some important mail" ) );
//    }
//
//    CMailServer s11(s10);
//
//    for (int i = 0; i < 2000; ++i) {
//        s11 . SendMail ( CMail ( "alice", "peter", "some important mail" ) );
//    }
//
//    CMailServer s20;
//
//    for (int i = 0; i < 2000; ++i) {
//        s20 . SendMail ( CMail ( "peter", "thomas", "some  mail" ) );
//    }
//
//
//    CMailServer s30(s20);
//
//    for (int i = 0; i < 2000; ++i) {
//        s30 . SendMail ( CMail ( "jan", "victor", "some  mail" ) );
//    }
//
//    CMailServer s40(s11);
//
//    for (int i = 0; i < 2000; ++i) {
//        s30 . SendMail ( CMail ( "jan", "victor", "some  mail" ) );
//    }
//
//    s10 = s20;
//    s11 = s20;
//    s40 = s30;
//
//
//    s20 = s11;
//
//    s10 = s11;
//
//    for (int i = 0; i < 2000; ++i) {
//        s20 . SendMail ( CMail ( "peter", "thomas", "some  mail" ) );
//    }
//
//
//    s10 = s30;
//
//    s11 . SendMail ( CMail ( "jan", "victor", "some  mail" ) );
//
//    CMailServer ss;
//    CMailIterator si1 = ss.Inbox("");
//
//    for (int i = 0; i < 100; ++i) {
//        ss . SendMail ( CMail ( "john", "alex" , "some important mail" ) );
//    }
//    for (int i = 0; i < 100; ++i) {
//        ss . SendMail ( CMail ( "alex", "john" , "some important mail" ) );
//    }
//    for (int i = 0; i < 100; ++i) {
//        ss . SendMail ( CMail ( "zed", "john" , "some important mail" ) );
//    }
//    for (int i = 0; i < 100; ++i) {
//        ss . SendMail ( CMail ( "peter", "zed" , "some important mail" ) );
//    }
//    for (int i = 0; i < 99; ++i) {
//        ss . SendMail ( CMail ( "zed", "peter" , "some important mail" ) );
//    }
//
//    ss . SendMail ( CMail ( "john", "alex" , "some important mail" ) );
//
//
//    CMailServer ss1 (ss);
//    for (int i = 0; i < 200; ++i) {
//        ss1 . SendMail ( CMail ( "kalr", "karl" , "some important mail" ) );
//    }
//    ss = ss;

  assert ( CMail ( "john", "peter", "progtest deadline" ) == CMail ( "john", "peter", "progtest deadline" ) );
  assert ( !( CMail ( "john", "", "progtest deadline" ) == CMail ( "john", "progtest deadline", "peter" ) ) );
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
  CMailIterator i0 = s0 . Inbox ( "alice" );
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

    CMailIterator i99 = s0.Inbox("zzzzzzalksjfalsdjf430ug34hgjfjlfs");
    assert(!i99);
    i99 = s0.Outbox("zzzzzzzsajdf99j34fgngj358jg54jgo3l4j");
    assert(!i99);

    i13 = s0.Inbox("alice");

  return 0;
}
#endif /* __PROGTEST__ */