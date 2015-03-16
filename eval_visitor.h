#pragma once

#include "visitor.h"

class eval_visitor: public visitor
{
  float _result;
  bool _evaluated;
public:
  eval_visitor();
  void visit (node_ptr n) override;
  bool evaluated()const;
  float result()const;
};