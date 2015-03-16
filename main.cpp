#include "parser.h"
#include "print_visitor.h"
#include "eval_visitor.h"
#include <iostream>

int main (int argc, char** argv)
{    
  while (!std::cin.eof())
  {
    std::cout << "Enter expression: ";
    std::string line; 
    std::getline(std::cin, line);
    std::cout << "Expression: " << line << std::endl;
    try
    {
      parser p(std::move(line));
      node_ptr tree = p.parse();  
      
      auto pv = std::make_shared<print_visitor>();
      auto ev = std::make_shared<eval_visitor>();
      
      tree->accept(pv);
      std::cout << std::endl;
      tree->accept(ev);
      std::cout << "result: " << ev->result() << std::endl;  
    }
    catch (const std::exception & e)
    {
      std::cerr << e.what() << std::endl;
    }
  }

  return 0;
}