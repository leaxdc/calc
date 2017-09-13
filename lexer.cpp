#include "lexer.h"
#include <sstream>
#include <algorithm>

void iterate_lexems(const std::string & data, lexem_callback  callback)
{
  if (data.empty())
  {
    callback(std::string());
    return;
  }

  std::string accum;

  for (auto & c: data)
  {
    switch (c)
    {
      case '(':
      case ')':
      case '+':
      case '-':
      case '/':
      case '*':
      case '^':      
        {
          if (!accum.empty()) 
          {
            callback(accum);        
            accum.clear();
          }
          std::stringstream ss;
          ss << c;
          callback(ss.str());        
        }
        break;        
      case ' ':
      case '\t':
        if (!accum.empty()) 
        {
          callback(accum);
          accum.clear();
        }
        break;

      default:
        if ((c >= 'a' && c <= 'z') ||
            (c >= '0' && c <= '9') || c == '.')
        {
          accum += c;  
        } else if (c != ' ' && c != '\t')
        {
          throw std::domain_error("invalid character: " + std::to_string(c));
        }
    }
  }
  if (!accum.empty()) 
  {
    callback(accum); 
  }
}
