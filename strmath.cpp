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

inline int alpha(char c)
{
    for (int i = 0; i < 26; i++)
    {
        if (lowalpha[i] == c)
        {
            return i;
        }
        if (upalpha[i] == c)
        {
            i+26;
        }
     }
     return -1;
}

inline char to_upper(char c)
{
    if (alpha(c) < 26 && alpha(c) != -1)
    {
        c = upalpha[alpha(c)];
    }
    return c;
}

inline char to_lower(char c)
{
    for (int i = 0; i < 26; i++)
    {
        if (upalpha[i] == c)
        {
            c = lowalpha[i];
            break;
        }
    }
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
inline int is_int(char ch)
{
    for (int i = 0; i < 10; i++)
    {
        if (ints[i] == ch)
        {
            return 1;
        }
    }
    return 0;
}

//Return the integer value of a char
inline int ch_int(char ch)
{
    for (int i = 0; i < 10; i++)
    {
        if (ints[i] == ch)
        {
            return ints_array[i];
        }
    }
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
    if (isneg)
    {
        val *= -1;
    }
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
    if (isneg)
        val *= -1;
    return val;
}

//A printf() style of string creation
//DOES NOT WORK YET, DO NOT USE
inline string var_str(char *s, ...)
{
    char str[1024];
    cout << "proc vars...\n";
    va_list ap;
    va_start(ap, s);
    vsprintf(str, s, ap);
    va_end(ap);
    cout << "convert to string...\n";
    string tmp = "";
    for (int i = 0; i < strlen(str); i++)
    {
        tmp += str[i];
    }
    return tmp;
}



class Tokenizer
{
public:
    string breaks;
    string word[20];
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
        for (int i = 0; i < data.length(); i++)
        {
            if (!is_break(data[i]))
            {
                word[num_words]+=data[i];
            }
            else
            {
                while (is_break(data[i+1]))
                {
                    i++;
                }
                num_words++;
            }
        }
        cout << num_words << " words parsed.\n";
    }
    void feed(string s)
    {
        data = s;
        num_words = 0;
    }
};



#endif

    