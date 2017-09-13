#include "eval_visitor.h"
#include "node.h"

eval_visitor::eval_visitor():
  _evaluated(false),
  _result(0.0)
{

}

void eval_visitor::visit (node_ptr n)
{
  _result = n->eval();
  _evaluated = true;
}

float eval_visitor::result()const
{
  return _result;
}

bool eval_visitor::evaluated()const
{
  return _evaluated;
}