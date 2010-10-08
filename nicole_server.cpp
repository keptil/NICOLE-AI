#ifndef NICOLE_SERVER_CPP
#define NICOLE_SERVER_CPP

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
#include "strmath.cpp"

using namespace std;

#define MAX_CONNECTIONS 5

class SERVER_INTERFACE
{
public:
  int num_connections;
  int sockfd[MAX_CONNECTIONS];
  int portno[MAX_CONNECTIONS];
  int clilen[MAX_CONNECTIONS];
  struct sockaddr_in serv_addr, cli_addr[MAX_CONNECTIONS];
  char buffer[256];
  SERVER_INTERFACE()
  {
    sockfd[0] = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
      cout << "Error creating sockfd[0].\n";
    }
    portno[0] = 3301;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno[0]);
    if (bind(sockfd[0], (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
      cout << "Error on binding sockfd[0] to serv_addr.\n";
    }
  }
  ~SERVER_INTERFACE()
  {
    cout << "Shutting down server interface.\n";
    for (int i = 0; i < num_connections; i++)
    {
      close(sockfd[i]);
    }
  }
  int Listen()
  {
    listen(sockfd[0], 5);
    clilen[0] = sizeof(cli_addr[0]);
    socklen_t len = sizeof(cli_addr[0]);
    sockfd[1] = accept(sockfd[0], (struct sockaddr *) &cli_addr[0], &len);
    if (sockfd[1] < 0)
    {
      cout << "Error on accept.\n";
      return 0;
    }
    num_connections++;
    return 1;
  }
  string read_input()
  {
    memset(&(buffer[0]), 0, 256);
    int i = read(sockfd[1], buffer, 255);
    if (i < 0)
    {
      cout << "Could not read.\n";
      return string("E1001");
    }
    string tmp = string(buffer);
    return tmp;
  }
  void send(string out)
  {
    memset(&(buffer[0]), 0, 256);
    int len = out.copy(buffer, 255);
    buffer[len] = 0;
    int writ = write(sockfd[1], buffer, strlen(buffer));
    if (writ < 0)
    {
      cout << "Error sending message.\n";
    }
  }
};

#endif
    
    
    