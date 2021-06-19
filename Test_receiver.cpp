#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "test/catch.hpp"
#include "Receiver/Receiver.c"
#include "Receiver/Type_def.h"
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

//Input stream of data was read   
TEST_CASE("Input stream of data was read") {
  //eg. of expected input as per sender designed
  //par1;par2;\n
  //10;0.1;\n
  printf("Enter a parameter set in json format: \n ");
  char paramSet[lengthOfParamset];

  // Call function under test
 bool ifReadSuccess = readInputFromConsole(paramSet);
  
  //Expected result
  REQUIRE(ifReadSuccess == true);
}

TEST_CASE("Test if data was extracted correctly")
{
  //Initialize buffer
  float paramBuffer[NoOfPar] = { 0 };
  char paramSet1[] = "98;0.1;\n"; //Input stream

  //Call function under test
  extractParametersFromInputSet(paramSet1, paramBuffer);
  
  //Expected reults
  REQUIRE(paramBuffer[Temperature] == 98);
  REQUIRE((paramBuffer[chargeRate] - 0.1) < infinitesimally_small);
}
