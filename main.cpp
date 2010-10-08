#include <iostream>
#include <string>
#include "strmath.cpp"
#include "nicole_server.cpp"

using namespace std;

int main()
{
  Tokenizer token;
  token.add_break("!, :");
  SERVER_INTERFACE *servint = new SERVER_INTERFACE();
  cout << "Waiting for connections...\n";
  while (!servint->Listen())
  {
    cout << "Waiting for connections.\n";
  }
  cout << "Connection received, starting.\n";
  while (1)
  {
    cout << "Reading input from client application.\n";
    string *a = new string;
    *a = servint->read_input();
    if (*a != "")
    {
      cout << *a << endl;
      token.feed(*a);
      token.tokenize();
    }
    if (!(low_string(token.word[5]).find("hello") == string::npos) && !(low_string(token.word[6]).find("nicole") == string::npos))
    {
      string tmp = "SEND Hello, " + token.word[1] + "! ";
      servint->send(tmp);
    }
    cout << "End of loop.\n"; 
    servint->send(" 0 ");
    delete a;
  }
    delete servint;
}

