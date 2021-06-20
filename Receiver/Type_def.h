#pragma once
#define UNITTEST 1
#define NoOfParamterSet 100  //set according to sender
#define NoOfPar 2 
#define lengthOfParamset 15
#define infinitesimally_small 0.001
#define movingAvgDataCount 5

#define TempMax  110.f // adapting as per sender inputs
#define TempMin  0.f

#define socMax  0.8f // adapting as per sender inputs
#define socMin  0.f

typedef enum  par_type
{
  Temperature,
  soc
}par_type;
