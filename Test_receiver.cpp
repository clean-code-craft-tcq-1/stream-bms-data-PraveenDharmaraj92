
#include "Receiver\Receiver.c"
#include "Receiver\Type_def.h"
#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

//NULL pointer is passed to read input parameter stream 
TEST_CASE("NULL pointer is passed to read input stream ") {

  // Call function under test
  bool ifTrueReadSuccess = readInputFromConsole(NULL);

  //Expected result
  REQUIRE(ifTrueReadSuccess == false);
}
