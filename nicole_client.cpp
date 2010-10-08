#ifndef NICOLE_CLIENT_CPP
#define NICOLE_CLIENT_CPP

#include <iostream>			// for the STL string
#include <cstdlib>			// For EXIT_SUCCESS, system(), exit(), srand() etc.
#include <cstring>			// For memset(), strlen(), strerror etc.
#include <cstdio>
#include <errno.h>			// For errno in the bail() function
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>		// For inet_addr, servaddr, AF_INET, htons(), PF_INET, socket()
//#include <time.h>			// For time() which I dont think I use yet
#include <sys/utsname.h>	// For struct utsname
#include <string>

using namespace std;

#ifndef MAX_MESSAGE_SIZE
#define MAX_MESSAGE_SIZE 512
#endif

#ifndef MAX_NICK_SIZE
#define MAX_NICK_SIZE 9
#endif

inline void cbail(const char *c)
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

class CLIENT_INTERFACE
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
    
    void out_str(string & s)
    {
        //cout << s.c_str() << endl;

        memset(&(writebuf[0]), 0, MAX_MESSAGE_SIZE);
	    int len = s.copy(writebuf, MAX_MESSAGE_SIZE - 1);
	    writebuf[len] = 0;
	    cout << "OUT: " << writebuf << endl;
        written = write(servsockd, writebuf, strlen(writebuf));
	    if (written == -1) cbail("write()");
    }

    void write_message()
    {
	  cout << "OUT: " << writebuf << endl;
	  written = write(servsockd, writebuf, strlen(writebuf));
	  if (written == -1) cbail("write()");
	}
	
    string& myself()
	{
	  return privateme;
	}
	
    void privmsg(string msg)
	{
	  msg = "PRIVMSG #" + channel + " :" + msg + "\r\n";
	  out_str(msg);
	  //memset(&writebuf, 0, sizeof writebuf);
	  //msg.copy(writebuf, sizeof writebuf);
	  //write_message();
	}

    string * read_msg(unsigned int out)
	{
      unsigned int * tmp = &out;
        memset(&(readbuf[0]), 0, MAX_MESSAGE_SIZE);
	  bytesread = read(servsockd, readbuf, MAX_MESSAGE_SIZE - 1);
	  if (bytesread == -1) cbail("read()");
	  string * retval = new string(readbuf);
	  //cout << readbuf;
      return retval;
	}
	
    void connect_to_server(void)	// Create connection and connect it
	{
	  int success = 0;
	  servaddr.sin_family = AF_INET;
	  servaddr.sin_addr.s_addr = inet_addr(servIP.c_str());
	  servaddr.sin_port = htons(servport);

	  servsockd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	  if (servsockd == -1) cbail("socket()");

	  success = connect(servsockd, (const sockaddr *)&servaddr, sizeof servaddr);
	  if (success == -1) cbail("connect()");
	  cout << "Connection to brain made.\n";
	  string greet = "HELLO\n";
	  out_str(greet);
	  
	  //setuser();
	  
	  //set_nick();
	  //joinchannel();
	  //privmsg("Joining in...");
	}
	
    CLIENT_INTERFACE()
	{
	  nick = realname = "NICOLEAI";
	  privateme = " :NICOLEAI !";
	  servport = 3301;
	  servIP = "127.0.0.1";
	  connect_to_server();
	  readbuf[0] = 0;
	  writebuf[0] = 0;
	}
	
    ~CLIENT_INTERFACE()
	{
	  exit(0);
	}
};

#endif
