#include "node.h"
#include <math.h>
#include <stdlib.h>


namespace
{
void validate_args(const std::string &name, const std::vector<node_ptr> &args, int cnt)
{
  if (args.size() != cnt )
  {
    throw std::domain_error("invalid arguments count: " + std::to_string(args.size()) + " for: " + name);
  }
}

}

class div_op: public op_node
{
public:
  div_op():op_node("/", true, 2) {

  }
  float eval() override
  {
    validate_args(name, children, 2);

    return children[0]->eval() / children[1]->eval();
  }  
};

class mul_op: public op_node
{
public:
  mul_op():op_node("*", true, 2) {

  }
  float eval() override
  {
    validate_args(name, children, 2);

    return children[0]->eval() * children[1]->eval();
  }  
};

class add_op: public op_node
{
public:
  add_op():op_node("+", true, 3) {

  }
  float eval() override
  {
    validate_args(name, children, 2);

    return children[0]->eval() + children[1]->eval();
  }  
};

class sub_op: public op_node
{
public:
  sub_op():op_node("-", true, 3) {

  }
  float eval() override
  {
    validate_args(name, children, 1);

    if (children.size() == 1) 
    {
      return -children[0]->eval();
    }
    else
    {
      return children[0]->eval() - children[1]->eval();  
    }    
  }  
};

class pow_op: public op_node
{
public:
  pow_op():op_node("^", true, 1) {

  }
  float eval() override
  {
    validate_args(name, children, 2);

    return pow (children[0]->eval(),children[1]->eval() );
  }  
};

class sin_op: public op_node
{
public:
  sin_op():op_node("sin",false, 0) {

  }
  float eval() override
  {
    validate_args(name, children, 1);

    return sin (children[0]->eval() );
  }  
};

class cos_op: public op_node
{
public:
  cos_op():op_node("cos", false, 0) {

  }
  float eval() override
  {
    validate_args(name, children, 1);

    return cos (children[0]->eval() );
  }  
};

class lg_op: public op_node
{
public:
  lg_op():op_node("ln", false, 0) {

  }
  float eval() override
  {
    validate_args(name, children, 1);

    return log (children[0]->eval() );
  }  
};

class brace_op: public op_node
{
public:
  brace_op():op_node("()",false, 1) {

  }
  float eval() override
  {
    validate_args(name, children, 1);

    return children[0]->eval();
  }  
};

node_ptr node_factory::create_op_node(const std::string & name)
{
  if (name == "/") {    
    return std::make_shared<div_op>();
  } else
  if (name == "*") {    
    return std::make_shared<mul_op>();
  } else
  if (name == "+") {
    return std::make_shared<add_op>();
  } else
  if (name == "-") {
    return std::make_shared<sub_op>();
  } else
  if (name == "^") {
    return std::make_shared<pow_op>();
  } else
  if (name == "sin") {
    return std::make_shared<sin_op>();
  } else
  if (name == "cos") {
    return std::make_shared<cos_op>();
  } else
  if (name == "ln") {
    return std::make_shared<lg_op>();
  } else
  
  throw std::domain_error("unknown operation");
  
}

node_ptr node_factory::create_brace_node()
{   
  return std::make_shared<brace_op>();  
}

node_ptr node_factory::create_value_node(const std::string & val)
{
  return std::make_shared<value_node>(::atof(val.c_str()));
}