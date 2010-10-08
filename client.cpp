#include <iostream>
#include "nicole_client.cpp"
#include "strmath.cpp"

using namespace std;

int main()
{
  cout << "Launching NICOLE CLIENT Interface.\n";
  //forkdaemon();
  Tokenizer token;
  cout << "Creating irci.\n";
  CLIENT_INTERFACE *irci = new CLIENT_INTERFACE;
  string * work;
  token.add_break("# +");
  int loopme = 1;
  cout << "Starting loop.\n";
  while(loopme)
  {
    //work.clear();
    cout << "r0 ";
    work = irci->read_msg(1234);
    cout << "r3 ";
    work->reserve();
    cout << "t0 ";
    token.feed(*work);
    token.tokenize();
    cout << "t1 ";
    if (*work != "")
    {
      cout << *work << endl;
    }
    
    
    
    
    
    delete work;

    sleep(1);
  }
  
  delete irci;
  
}
