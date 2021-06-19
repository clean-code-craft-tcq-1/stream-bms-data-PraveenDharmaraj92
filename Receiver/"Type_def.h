#pragma once
#define UNITTEST 1
#define NoOfParamterSet 6 
#define NoOfPar 2 
#define lengthOfParamset 15
#define infinitesimally_small 0.001
#define movingAvgDataCount 5

#define TempMax  45.f
#define TempMin  0.f

#define chargeRateMax  0.8f
#define chargeRateMin  0.f

typedef enum  par_type
{
  Temperature,
  chargeRate
}par_type;
