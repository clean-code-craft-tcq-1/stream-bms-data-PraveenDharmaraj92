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


TEST_CASE( "Max parameter evaluation"){
  
  const int NoOfTest2 = 2;
  float paramMax =0.f;
  
  typedef struct inputMatrix3_st {
                                   float parameterValue;
                                   float parameterMax;
  } InputMaxSet;

  InputMaxSet InputSet2[NoOfTest2] = {
    { chargeRateMax, chargeRateMin + 0.2f },
    { chargeRateMin, chargeRateMin + 0.2f }
  };

  float OutputParMax[NoOfTest2] = { chargeRateMax, chargeRateMin + 0.2f };

  for (int TestCaseCounter = 0;TestCaseCounter < NoOfTest2; TestCaseCounter++)
  {
    paramMax = InputSet2[TestCaseCounter].parameterMax;
    //Call function under test 
    calculateMaxValue(&InputSet2[TestCaseCounter].parameterValue, &paramMax);

    REQUIRE(paramMax == OutputParMax[TestCaseCounter]);
  }
}//End Of Max parameter evaluation
  
TEST_CASE( "Min parameter evaluation"){
  
  const int NoOfTest1 = 2;
   float paramMin = 0.f;
  //Input matrix structure
  typedef struct inputMatrix2_st {
    float parameterValue;
    float parameterMin;
  } InputMinSet;

  //Input output variable data
  InputMinSet InputSet1[NoOfTest1] = {
                                     {TempMin, TempMin + 10},
                                     {TempMax, TempMin+5}
  };

  float OutputParMin[NoOfTest1] = { TempMin, TempMin + 5 };
  
  for (int TestCaseCounter = 0;TestCaseCounter< NoOfTest1; TestCaseCounter++)
  {
    paramMin = InputSet1[TestCaseCounter].parameterMin;
    
    //Call function under test 
    calculateMinValue(&InputSet1[TestCaseCounter].parameterValue, &paramMin);

    REQUIRE(paramMin == OutputParMin[TestCaseCounter]);
  }
}//End Of Min parameter evaluation

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
