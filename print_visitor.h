#pragma once

#include "visitor.h"

class print_visitor: public visitor
{
public:
  print_visitor()=default;
  void visit (node_ptr n) override;
};