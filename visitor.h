#pragma once

#include <memory>

class node;
using node_ptr = std::shared_ptr<node>;

class visitor
{
public:
  virtual ~visitor(){}
  virtual void visit (node_ptr n) = 0;

};

using visitor_ptr = std::shared_ptr<visitor>;