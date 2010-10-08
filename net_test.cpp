#include <iostream>
#include "nicole_irc.cpp"
#include "nicole_client.cpp"
#include "strmath.cpp"

using namespace std;

int main()
{
  cout << "Launching NICOLE IRC Interface.\n";
  forkdaemon();
  Tokenizer token, servtoken;
  cout << "Creating irci.\n";
  IRC_INTERFACE *irci = new IRC_INTERFACE;
  cout << "Creating connection to brain.\n";
  CLIENT_INTERFACE *cint = new CLIENT_INTERFACE;
  string * work;
  string *in_server;
  token.add_break("# +");
  servtoken.add_break(" \n\r");
  int loopme = 1;
  cout << "Starting loop.\n";
  int is_in = 0;
  while(loopme)
  {
    cout << "Reading from IRC.\n";
    work = irci->read_msg(1234);
    work->reserve();
    token.feed(*work);
    token.tokenize();
    
    cout << "Processing...\n";
    if (*work != "")
    {
      cout << *work << endl;
      //string to_server = "IRC "+*work;
    }

    if (!(work->find("Found your hostname") == string::npos))
    {
      //irci->loginpass();
      irci->set_nick();
      irci->setuser();
    }
    
    if (!(work->find("/MOTD") == string::npos))
    {
      irci->joinchannel();
      irci->privmsg("Signing in...");
      is_in = 1;
    }
    if (!(work->find(":!killnicole") == string::npos))
    {
      irci->privmsg("Goodbye, cruel world!");
      break;
    }
    if (!(work->find(":!rejoin") == string::npos))
    {
      string cmd = "JOIN #drift\r\n";
      irci->out_str(cmd);
    }
    if (!(work->find("PING :") == string::npos))
    {
        string pongdat = "";
        for (int i = 0; i < token.word[1].length(); i++)
        {
            pongdat += token.word[1][i];
        }
        irci->sendpong(pongdat);
    }
    if (!(work->find(":!hello") == string::npos)) irci->privmsg("Hello");
    if (!(work->find(":!restart") == string::npos))
    {
      system("./net_test");
      loopme = 0;
      break;
    }
    
    if (!(work->find(irci->myself()) == string::npos))
    {
      irci->privmsg("Private message received.");
    }
    if (is_in)
    {
    string to_server = "IRC " + *work;
      cint->out_str(to_server);
    cout << "Reading from Brain.\n";
    in_server = cint->read_msg(1234);
    if (*in_server != "")
      cout << *in_server << endl;
    servtoken.feed(*in_server);
    servtoken.tokenize();
    cout << "Processing...\n";
    if (servtoken.word[0] == "SEND")
    {
      string tmp;
      for (int i = 1; i < servtoken.num_words; i++)
      {
	tmp += servtoken.word[i] + " ";
      }
      irci->privmsg(tmp);
    }
    cout << "Tokens from brain:\n";
    for (int i = 0; i < servtoken.num_words; i++)
    {
     cout << servtoken.word[i] << ' ';
    }
    if (!(in_server->find("SEND") == string::npos))
    {
      irci->privmsg("SEND command from Brain.");
    }
    cout << endl;
    }  
    delete work;

    sleep(1);
    cout << "Done.\n";
  }
  
  delete irci;
  delete cint;
  
}
