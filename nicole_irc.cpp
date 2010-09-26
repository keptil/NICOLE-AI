#ifndef NICOLE_IRC_CPP
#define NICOLE_IRC_CPP

#include <iostream>			// for the STL string
#include <cstdlib>			// For EXIT_SUCCESS, system(), exit(), srand() etc.
#include <cstring>			// For memset(), strlen(), strerror etc.
#include <cstdio>
#include <errno.h>			// For errno in the bail() function
#include <arpa/inet.h>		// For inet_addr, servaddr, AF_INET, htons(), PF_INET, socket()
//#include <time.h>			// For time() which I dont think I use yet
#include <sys/utsname.h>	// For struct utsname
#include <string>

using namespace std;

const string CRLF = "\r\f";
static pid_t pid;

#ifndef MAX_MESSAGE_SIZE
#define MAX_MESSAGE_SIZE 512
#endif

#ifndef MAX_NICK_SIZE
#define MAX_NICK_SIZE 9
#endif

inline void bail(const char *c)
{												// This function is used to print out messages when we use EXIT. Something went wrong.
    if (errno!=0)		// If errno is set, print out the message.
    {
        fputs(strerror(errno), stderr);
        fputs(": ", stderr);
    }
    fputs(c, stderr);	// Print out error message returned from function
    fputc('\n', stderr);		// Newline.. c-style ..
    exit(1);		// Exit in error and tell the OS we did it.
}

inline void forkdaemon()
{
   if ((pid = fork()) == -1) bail("fork()");   // Fork a new process
   else if (pid > 0) exit(0);		// If I am parent the exit nicely
   setsid();							// Run process in new session
}

#define USERNAME "NICOLE_AI"
#define PASSWORD "veritech3"

class IRC_INTERFACE
{
  private:
      char prefix;			// IRC command prefix
      int servsockd;			// Socket descriptor used to connect to IRC
      int servport;			// Port for IRC server
      int bytesread;			// Returncode from read
      int written;			// Returncode from write
	string servIP;			// Buffer for IRC server IP
	struct sockaddr_in servaddr;	// Address struct for IRC connection
	string nick;			//	Buffer for the irc nick. RFC 2812 says max 9 chars
	char readbuf[MAX_MESSAGE_SIZE];	// Readbuffer. RFC 2812 says max 512 chars including CRLF
	char writebuf[MAX_MESSAGE_SIZE];	// Writebuffer
	string channel;		// string containing channel
	string password;		// Password for bot to connect ti IRC server with
	string realname;		// Real name
	string privateme;		// Buffer for catching private messages ":<nick> !"
  public:
        void write_message()
        {
	  cout << "OUT: " << writebuf << endl;
	  written = write(servsockd, writebuf, strlen(writebuf));
	  if (written == -1) bail("write()");
	}
	void loginpass(void)	// Register IRC session by sending PASS
	{
	  password = "PASS " + password + "\r\n";
	  memset(&writebuf, 0, sizeof writebuf);
	  password.copy(writebuf, sizeof writebuf);
	  write_message();
	}
	void setuser(void)		// Set IRC user
	{
	  realname = "USER NICOLE_AI 0 0 :nicole_ai\r\n";
	  memset(&writebuf, 0, sizeof writebuf);
	  realname.copy(writebuf, sizeof writebuf);
	  write_message();
	}
	void joinchannel()	// Join channel on IRC server
	{
	  string jmsg = "JOIN #drift\r\n";
	  memset(&writebuf, 0, sizeof writebuf);
	  jmsg.copy(writebuf, sizeof writebuf);
	  write_message();
	}
	void quit()			// Send quit to server
	{
	  string qmsg = "QUIT : NICOLE_AI shutting down\r\n";
	  memset(&writebuf, 0, sizeof writebuf);
	  qmsg.copy(writebuf, sizeof writebuf);
	  write_message();
	}
	void set_nick(void)
	{
	  nick = "NICK nicole_ai\r\n";
	  memset(&writebuf, 0, sizeof writebuf);
	  nick.copy(writebuf, sizeof writebuf);
	  write_message();
	}
	void sendpong(string dat)
	{
	  string pong = "PONG " + dat + "\r\n";
	  memset(&writebuf, 0, sizeof writebuf);
	  pong.copy(writebuf, sizeof writebuf);
	  write_message();
	}
	string myself()
	{
	  return privateme;
	}
	void privmsg(string msg)
	{
	  msg = "PRIVMSG #" + channel + " :" + msg + "\r\n";
	  memset(&writebuf, 0, sizeof writebuf);
	  msg.copy(writebuf, sizeof writebuf);
	  write_message();
	}
	string read_msg()
	{
	  memset(&readbuf, 0, sizeof readbuf);
	  bytesread = read(servsockd, readbuf, sizeof readbuf-1);
	  if (bytesread == -1) bail("read()");
	  string retmsg = readbuf;
	  return retmsg;
	}
	void connectirc(void)	// Create connection and connect it 
	{
	  int success = 0;
	  servaddr.sin_family = AF_INET;
	  servaddr.sin_addr.s_addr = inet_addr(servIP.c_str());
	  servaddr.sin_port = htons(servport);
	  
	  servsockd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	  if (servsockd == -1) bail("socket()");
	  
	  success = connect(servsockd, (const sockaddr *)&servaddr, sizeof servaddr);
	  if (success == -1) bail("connect()");
	  
	  setuser();
	  
	  //set_nick();
	  //joinchannel();
	  //privmsg("Joining in...");
	}
	void disconnirc(void)
	{
	  quit();
	  close(servsockd);
	}
	IRC_INTERFACE()
	{
	  nick = realname = "NICOLE_AI";
	  privateme = " :NICOLE_AI !";
	  password = "NICOLE_AI";
	  servport = 6667;
	  servIP = "209.251.184.237";
	  channel = "drift";
	  connectirc();
	}
	~IRC_INTERFACE()
	{
	  disconnirc();
	  exit(0);
	}
};

#endif
