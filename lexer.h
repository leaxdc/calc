#pragma once

#include <functional>
#include <memory>
#include <string>

using lexem_callback = std::function < void (const std::string &)>;

void iterate_lexems(const std::string & data, lexem_callback  callback);