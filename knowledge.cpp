#ifndef KNOWLEDGE_CPP
#define KNOWLEDGE_CPP 

#include <iostream>
#include <fstream>
#include "strmath.cpp"

using namespace std;

class OBJECT
{
protected:
      string name;
      string description;
public:
      OBJECT()
      {
	
      }
      ~OBJECT()
      {
      
      }
      virtual void set_name(string n)
      {
	name = n;
      }
      virtual void set_desc(string d)
      {
	description = d;
      }
      virtual string get_name()
      {
	return name;
      }
};

class GENERIC_OBJECT : public OBJECT
{
  protected:
    string classification;
  public:
    GENERIC_OBJECT()
    {
    }
    ~GENERIC_OBJECT()
    {
    }
    void set_class(string c)
    {
      classification = c;
    }
};

class FOOD_OBJECT : public OBJECT
{
  protected:
    int taste;
    int serving_size;
    int calories;
  public:
    FOOD_OBJECT()
    {
    }
    ~FOOD_OBJECT()
    {
    }
    void set_taste(int t)
    {
      taste = t;
    }
    void set_cal(int c)
    {
      calories = c;
    }
    void set_serving_size(int o)
    {
      serving_size = o;
    }
};


class ANIMAL
{
protected:
  string name[10];
  int num_names;
  int age;
  OBJECT *likes[100];
  int num_likes;
public:
  ANIMAL()
  {
    cout << "New ANIMAL created.\n";
  }
  ANIMAL(string n)
  {
    name[0] = n;
    cout << "New ANIMAL \"" << name[0] << "\" created.\n"; 
  }
  ~ANIMAL()
  {
    cout << "ANIMAL destroyed.\n";
  }
  virtual void Add_Like(OBJECT *nl)
  {
    if (num_likes < 100)
    {
      likes[num_likes] = nl;
      num_likes++;
    }
  }
  virtual void Display();
};

class HUMAN : public ANIMAL
{
  public:
    HUMAN()
    {
    }
    HUMAN(string n)
    {
      name[0] = n;
    }
    ~HUMAN()
    {
    }
    virtual void Display()
    {
      cout << name[0] << endl;
      cout << "Likes:\n";
      for (int i = 0; i < num_likes; i++)
      {
	cout << likes[i]->get_name() << endl;
      }
    }
};

#endif

    