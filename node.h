#pragma once

#include "visitor.h"

#include <memory>
#include <string>
#include <vector>
#include <exception>

// typedef <typename T>
struct node: std::enable_shared_from_this<node>

{      
  std::vector<node_ptr> children;
  int priority;
  double value;  
  bool is_operator;
  std::string name;

  node(int p, double v, bool is_op, const std::string & n): priority(p), value(v ), is_operator(is_op), name(n)
  {

  }
  node(const node&) = delete;
  node(const node&&) = delete;


  virtual ~node() {}  
  virtual void accept(visitor_ptr visitor)
  {
    visitor->visit(shared_from_this());    
  }  

  virtual float eval() = 0;  
  virtual std::string to_string()const = 0;
};

struct value_node: node
{    
  value_node(double val): node(0, val, false, std::string())
  {

  }

  float eval() override
  {
    return value;
  }
  std::string to_string() const override
  {
    return std::to_string(value);
  }
};

struct op_node: node
{   
  op_node() = delete;
  op_node(const std::string &n, bool op, int p = 0): node(p, 0.0, op, n)
  {    

  } 
  std::string to_string() const override
  {
    return name;
  }
};

class node_factory
{
public:  
  static node_ptr create_op_node(const std::string & name);
  static node_ptr create_brace_node();
  static node_ptr create_value_node(const std::string & val);
};
