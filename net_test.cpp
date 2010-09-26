#include <iostream>
#include "nicole_irc.cpp"
#include "strmath.cpp"

using namespace std;

int main()
{
  cout << "Launching NICOLE IRC Interface.\n";
  forkdaemon();
  Tokenizer token;
  cout << "Creating irci.\n";
  IRC_INTERFACE *irci = new IRC_INTERFACE;
  string work;
  token.add_break("# +");
  work.reserve(MAX_MESSAGE_SIZE);
  int loopme = 1;
  cout << "Starting loop.\n";
  while(loopme)
  {
    work.clear();
    work = irci->read_msg();
    work.reserve();
    token.feed(work);
    token.tokenize();
    if (work != "")
    {
      cout << work << endl;
    }
    
    if (!(work.find("Found your hostname") == string::npos))
    {
      irci->loginpass();
      irci->set_nick();
      //irci->setuser();
      irci->joinchannel();
      irci->privmsg("Signing in...");
    }
    
    if (!(work.find(":!end") == string::npos)) break;
    if (!(work.find("PING :") == string::npos))
    {
      string pongdat;
      for (int i = 12; i < token.word[1].length(); i++)
      {
	pongdat += token.word[1][i];
      }
      irci->sendpong(pongdat);
    }
    if (!(work.find(":!hello") == string::npos)) irci->privmsg("Hello");
    if (!(work.find(":!restart") == string::npos))
    {
      system("./net_test");
      loopme = 0;
      break;
    }
    if (!(work.find("ERROR") == string::npos))
    {
      cout << "Connection error.\n";
      loopme = 0;
      break;
    }
    
    if (!(work.find(irci->myself()) == string::npos))
    {
      irci->privmsg("Private message received.");
    }
    sleep(1);
  }
  
  delete irci;
  
}
