/**********************************************
STRMATH
Convert strings to integers, floats, doubles
and perform math with them just like variables.

Part of the NICOLE library

Started 9/15/2010

***********************************************/
#ifndef STRMATH_CPP
#define STRMATH_CPP

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdarg>
#include <cstring>

using namespace std;

const string ints = "0123456789";
const int ints_array[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

const string lowalpha = "abcdefghijklmnopqrstuvwxyz"; 
const string upalpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

//a=0 ~~~ z=25; A=26 ~~~ Z=51; anything else=-1
inline int alpha(char c){
    if( c>='a' && c<='z' )
        return c-'a';
    if( c>='A' && c<='Z' )
        return c-'A'+26;
    return -1;
}

inline char to_upper(char c){
    if( c>='a' && c<='z' )
        return c-32;  //same as c-'a'+'A'
    return c;
}

inline char to_lower(char c){
    if( c>='A' && c<='Z' )
        return c+32;  //same as c-'A'+'a'
    return c;
}

inline string up_string(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = to_upper(s[i]);
    }
    return s;
}

inline string low_string(string s)
{
    for (int i = 0; i < s.length(); i++)
    {
        s[i] = to_lower(s[i]);
    }
    return s;
}

inline string beg_string(string s)
{
    s[0] = to_upper(s[0]);
    return s;
}

//Test to see if a char is an integer
inline int is_int(char ch){
    if( ch>='0' && ch<='9' )
        return 1;
    return 0;
}

//Return the integer value of a char
inline int ch_int(char ch){
    if( ch>='0' && ch<='9' )
        return ch-'0';
    return -1;
}

//Convert a string into an integer
inline int str_int(string s)
{
    int isneg = 0;
    int val = 0;
    if (s[0] == '-')
    {
        isneg = 1;
    }
    for (int i = isneg; i< s.length();i++)
    {
      if (is_int(s[i]))
      {
          val *= 10;
          val += ch_int(s[i]);
      }
      else
      {
        break;
      }
    }
    
    val *= isneg*(-2) + 1;

    return val;
}

//Convert a string to a decimal number
inline double str_double(string s)
{
    double val = 0.0;
    int isneg = 0;
    if (s[0] == '-')
        isneg = 1;
    int ad = 0;
    
    for (int i = isneg; i < s.length(); i++)
    {
        if (is_int(s[i]))
        {
            if (!ad)
            {
                val *= 10;
                val += ch_int(s[i]);
            }
            else
            {
                val += (double)ch_int(s[i])/ad;
                ad*=10;
            }
        }
        else
        {
            if (!ad)
            {
                ad = 10;
            }
            else
            {
                break;
            }
        }
    }

    val *= isneg*(-2) + 1;

    return val;
}

class Tokenizer
{
public:
    string breaks;
    string word[999];
    string data;
    int num_words;
    


    void add_break(char *s)
    {
        breaks += s;
    }
    void clear_breaks()
    {
        breaks = "";
    }
    int is_break(char c)
    {
        for(int i = 0; i < breaks.length(); i++)
        {
            if (breaks[i] == c)
                return 1;
        }
        return 0;
    }
    void tokenize()
    {
        int i;
        for (i = 0; i < data.length() && num_words < 999; i++)
        {
            if (!is_break(data[i]))
            {
                word[num_words]+=data[i];
            }
            else
            {
                //cout << "new token " << num_words << " at " << i << ": " << word[num_words] << endl;
                while (i < data.length() && is_break(data[i+1]))
                {
                    i++;
                }
                num_words++;
            }
        }
        if (num_words == 999)
        {
            // excess data
            cout << "excess data!" << endl;
        }
        //cout << num_words << " words parsed.\n";
    }
    void feed(string& s)
    {
        data = s;
        num_words = 0;

        //cout << "new data: " << data << endl;

        for (int i = 0 ; i < 999; i++)
            word[i] = "";
    }
};



#endif

    
