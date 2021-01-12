#include "test.h"


#include <algorithm>
#include <string>


void callprint(std::string str)
{
  std::transform(str.begin(), str.end(),str.begin(), ::toupper);
  print(str);
}

