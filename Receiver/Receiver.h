#pragma once
#include "Type_def.h"

void ReceiverMain();
bool readInputFromConsole(char *Paramset);
void extractParametersFromInputSet(char *paramSet, float *paramBuffer);
void delay(int number_of_seconds);
void calculateMaxValue(float *individualParameter, float *individualParamMax);
void calculateMinValue(float *individualParameter, float *individualParamMin);
void simpleMovingAvg(float *previousIndividualParValueSet, float movingAvg);
void reportfailure(int readFailureCounter);
#if (UNITTEST == 1)
void scanf_mock(const char *format,char *ptr);
#endif
