#pragma once

#include "node.h"
#include <exception>
#include <functional>

class parser
{
  std::string _data;  
public:
  parser()=delete;
  parser(parser&)=delete;
  parser(parser&&)=delete;
  parser(const std::string & str):_data(str) {

  }

  parser(const std::string && str):_data(std::move(str)) {

  }
  
  node_ptr parse();

};