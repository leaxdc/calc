#include "print_visitor.h"
#include "node.h"
#include <iostream>

void print_visitor::visit (node_ptr n)
{
  for (auto & node: n->children)
  {
    visit(node);
  }
  std::cout << n->to_string() << " ";
}