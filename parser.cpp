
#include "parser.h"
#include "node.h"
#include "lexer.h"
#include <deque>
#include <iostream>

namespace 
{

using node_stack = std::deque<node_ptr>;
using node_stack_ptr = std::shared_ptr<node_stack>;
using stack_stack = std::deque<node_stack_ptr>;

bool is_value (const std::string & val)  
{
  for (auto &c: val)
  {
      if ( ! ( (c >= '0' && c <= '9') || c == '.')  )
      {
        return false;
      }
  }
  return true;
}

node_ptr prev_op_node(node_stack_ptr stack)
{
  auto it = std::find_if(stack->rbegin(), stack->rend(), [](node_ptr  node) {
    return node->is_operator;
  });

  return it == stack->rend() ? nullptr: *it;
}

node_ptr unwind(node_stack_ptr stack, node_ptr cur_node = nullptr)
{  
  if (!stack->size())
  {
    return nullptr;
  }

  node_ptr result;

  while (stack->size() > 1)
  {
    auto top = stack->back();
    stack->pop_back();

    auto & prev = stack->back();
    if (cur_node && prev->priority > cur_node->priority )
    {
      stack->push_back(top);
      break;
    }
    prev->children.push_back(top);    
  }
  

  return stack->back();
}


}

node_ptr parser::parse()
{
  stack_stack nstack;
  nstack.push_back(std::make_shared<node_stack>());

  node_stack_ptr stack = nstack.back();  

  iterate_lexems(_data, [&](const std::string & lexem) {
            
    if (is_value(lexem))
    {      
      stack->push_back(node_factory::create_value_node(lexem));
    } 
    else if (lexem == "(")
    { 
      auto node = node_factory::create_brace_node();
      stack->push_back(node);
      nstack.push_back(std::make_shared<node_stack>());
      stack = nstack.back();
    } 
    else if (lexem == ")" )
    {
      if (nstack.size() < 2)
      {
        throw std::domain_error("unmatched ) bracket(s)");
      }
      auto node = unwind(nstack.back());
      nstack.pop_back();
      stack = nstack.back();
      stack->back()->children.push_back(node);
    }
    else 
    {      
      auto node = node_factory::create_op_node(lexem);      

      if (!stack->empty())
      {
        auto top = stack->back();      
        auto prev_op = prev_op_node(stack);

        if (prev_op && prev_op->priority <= node->priority)
        {                      
          top = unwind(stack, node);        
        }
              
        node->children.push_back(top);      
        
        stack->pop_back();                  
      }      
      stack->push_back(node);
    }         
  });
  
  if (nstack.size() != 1)
  {
    throw std::domain_error("unmatched ( bracket(s)");
  }
  return unwind(stack);
}