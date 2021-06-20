#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#include "Receiver.h"


/*****************************************************************************
F U N C T I O N    D E S C R I P T I O N
------------------------------------------------------------------------------
Function name:  delay                                   *//*!
\brief       Function to introduce wait cycles or delay in seconds
             delay(1) --> wait of 1 sec
*//*--------------------------------------------------------------------------
I N P U T                                                                 *//*!
\param[in]  number_of_seconds : wait time in seconds before 
                                execution of next command
*//*--------------------------------------------------------------------------
O U T P U T                                                             *//*!
\param[out] -
*//*--------------------------------------------------------------------------
A U T H O R  I D E N T I T Y                                             *//*!
\author   $Gagandeep
*//**************************************************************************/
void delay(int number_of_seconds)
{
  // Converting time into milli_seconds
  int milli_seconds = 1000 * number_of_seconds;

  // Storing start time
  clock_t start_time = clock();

  // looping till required time is not achieved
  // which is begin time + wait time in milliseconds 
  while (clock() < start_time + milli_seconds);
}

/*****************************************************************************
F U N C T I O N    D E S C R I P T I O N
------------------------------------------------------------------------------
Function name:  calculateMinValue                                        *//*!
\brief       Function to calculate minimum value of input parameter and
             updates the same. 
*//*--------------------------------------------------------------------------
I N P U T                                                                 *//*!
\param[in]  individualParameter : pointer to value of each parameter
            individualParamMin  : pointer to min value for each parameter

*//*--------------------------------------------------------------------------
O U T P U T                                                                *//*!
\param[out] individualParamMin  : pointer to min value for each parameter 
*//*--------------------------------------------------------------------------
A U T H O R  I D E N T I T Y                                             *//*!
\author   $Gagandeep
*//**************************************************************************/
void calculateMinValue(float *individualParameter, float *individualParamMin) {
   
     /* Update the min value if current value is less */
    if (*individualParamMin > *individualParameter)
    {
      *individualParamMin = *individualParameter;

    }
}

/*****************************************************************************
F U N C T I O N    D E S C R I P T I O N
------------------------------------------------------------------------------
Function name:  calculateMaxValue                                        *//*!
\brief       Function to calculate maximum value of input parameter and
             updates the same. 
*//*--------------------------------------------------------------------------
I N P U T                                                                 *//*!
\param[in]  individualParameter : pointer to value of each parameter
            individualParamMax  : pointer to max value for each parameter

*//*--------------------------------------------------------------------------
O U T P U T                                                                *//*!
\param[out] paramMax[NoOfPar]    : pointer to max value for each parameter
*//*--------------------------------------------------------------------------
A U T H O R  I D E N T I T Y                                             *//*!
\author   $Gagandeep
*//**************************************************************************/

void calculateMaxValue(float *individualParameter, float *individualParamMax) {
  /* Update the maximum value if current value is more */
  if (*individualParamMax < *individualParameter)
  {
    *individualParamMax = *individualParameter;
  }
}

/*****************************************************************************
F U N C T I O N    D E S C R I P T I O N
------------------------------------------------------------------------------
Function name:  simpleMovingAvg                                        *//*!
\brief       Function to simple moving average of movingAvgDataCount no. 
             of parameter data 
*//*--------------------------------------------------------------------------
I N P U T                                                                 *//*!
\param[in]  previousIndividualParValueSet : pointer to value of last  
                                         movingAvgDataCount values of parameter
            movingAvg  : pointer to moving average of parameter

*//*--------------------------------------------------------------------------
O U T P U T                                                                *//*!
\param[out]  movingAvg  : pointer to moving average of parameter
*//*--------------------------------------------------------------------------
A U T H O R  I D E N T I T Y                                             *//*!
\author   $Gagandeep
*//**************************************************************************/
void simpleMovingAvg(float * previousIndividualParValueSet, float *movingAvg) {

  *movingAvg = 0.f;
  float sumOfParValue = 0.f;
  /* Running loop for movingAvgDataCount no. of times for evaluation */
  for (int CounterOfParValue = 0; CounterOfParValue< movingAvgDataCount; CounterOfParValue++) {
   
    sumOfParValue += previousIndividualParValueSet[CounterOfParValue];

  }// end of loop

  /*Update the average of latest movingAvgDataCount values*/
  *movingAvg = sumOfParValue / movingAvgDataCount;
}

/*****************************************************************************
F U N C T I O N    D E S C R I P T I O N
------------------------------------------------------------------------------
Function name:  Receivermain                                            *//*!
\brief       Main recevier functionality which execute the entire flow:
             -> reading input streaming data from console 
             -> extracting the parameter from input stream string
             -> Calculates Min and Max 
             -> Calculates simple moving average             
*//*--------------------------------------------------------------------------
I N P U T                                                               *//*!
\param[in] -
\param[in] -
*//*--------------------------------------------------------------------------
O U T P U T                                                             *//*!
\param[out] -
*//*--------------------------------------------------------------------------
A U T H O R  I D E N T I T Y                                             *//*!
\author   $Gagandeep
*//**************************************************************************/
void Receivermain()
{
  char paramSet[lengthOfParamset];
  float previousParamValueBuffer[NoOfPar][movingAvgDataCount] = { 0.f };
  float paramMin[NoOfPar] = { TempMax,socMax };
  float paramMax[NoOfPar] = { TempMin,socMin };
  float movingAvg[NoOfPar] = {0.f};

  /* Reading the input stream */
  for (int paramSetCounter = 0; paramSetCounter < NoOfParamterSet; paramSetCounter++) {
    
    /* Read one input set if the read is successful process parameters further*/
    bool ifTrueReadSuccess = readInputFromConsole(paramSet);
    if (ifTrueReadSuccess)
    {
      /* Initialize individual parameter buffer to zero */
      float paramBuffer[NoOfPar] = { 0.f };

      /*Converts data stream to individual parameter data*/
      extractParametersFromInputSet(paramSet, paramBuffer);
     
      /* Running loop for each parameter evaluation */
      for (int parameterCount = 0; parameterCount< NoOfPar; parameterCount++) {
        
        //Overwrites buffer of previous value set
        previousParamValueBuffer[parameterCount][paramSetCounter%movingAvgDataCount] = paramBuffer[parameterCount];
        /* Calculates Min and Max value */
        calculateMinValue(&paramBuffer[parameterCount], &paramMin[parameterCount]);
        calculateMaxValue(&paramBuffer[parameterCount], &paramMax[parameterCount]);
        
        /* Calculte simple moving average of movingAvgDataCount values */

        //Since for very first evaluation a set of movingAvgDataCount data is required 
        if (paramSetCounter >= movingAvgDataCount)
        {
          simpleMovingAvg(previousParamValueBuffer[parameterCount], &movingAvg[parameterCount]);
        }
      }// end of loop for each parameter

      printf(" Current Min value of Temp : %f, ChargeRate : %f \n ", paramMin[Temperature], paramMin[soc]);
      printf(" Current Max value of Temp : %f, ChargeRate : %f \n ", paramMin[Temperature], paramMin[soc]);
      printf(" Current SMA value of Temp : %f, ChargeRate : %f \n ", movingAvg[Temperature], movingAvg[soc]);

    }
    /* Wait for 1 sec before next input is streamed */
    delay(1);

  }
  
}

/*****************************************************************************
F U N C T I O N    D E S C R I P T I O N
------------------------------------------------------------------------------
Function name:  readInputFromConsole                                   *//*!
\brief       Reads input string of parameters from the console input  
             The format of string is:
             par1;par2;\n as defined by sender (json)

*//*--------------------------------------------------------------------------
I N P U T                                                               *//*!
\param[in]  Paramset : set of parameter 
*//*--------------------------------------------------------------------------
O U T P U T                                                             *//*!
\param[out] 
*//*--------------------------------------------------------------------------
A U T H O R  I D E N T I T Y                                             *//*!
\author   $Gagandeep
*//**************************************************************************/
bool  readInputFromConsole(char *paramSet) {
  
  int len=0; //Length of string
  if (paramSet != NULL)
  {
    scanf("%s",paramSet);
    len = strlen(paramSet);
    
    paramSet[len] = '\n';
    paramSet[len + 1] = '\0';
   
    return true; 
  }

  return false; // read was not successful as the pointer was NULL
}

/*****************************************************************************
F U N C T I O N    D E S C R I P T I O N
------------------------------------------------------------------------------
Function name:  extractParametersFromInputSet                                   *//*!
\brief       Used to extract each parameter from input set Paramset and 
             stored in the paramBuffer array.
             
*//*--------------------------------------------------------------------------
I N P U T                                                               *//*!
\param[in]  Paramset : raw input string of parameterset
\param[in]  paramBuffer: Array of 2 to store individual parameter
*//*--------------------------------------------------------------------------
O U T P U T                                                             *//*!
\param[out] paramBuffer: Array of 2 to store individual parameter
*//*--------------------------------------------------------------------------
A U T H O R  I D E N T I T Y                                             *//*!
\author   $Gagandeep
*//**************************************************************************/

void extractParametersFromInputSet(char *paramSet, float *paramBuffer)
{
  int i = 0, j = 0; //index counter

  char par[lengthOfParamset]; //string for each parameter 
  int parNum = 0;  //count of parameters

  /* Read till we reach end of string */
  while ((paramSet[i] != '\n')){
    
    /* Read each parameter */
    for (j = 0;paramSet[i] != ';';j++, i++)
    {
      par[j] = paramSet[i];
    }

    par[j] = '\0'; //Adding end of string
    
    /* Convert string to float number to evaluate further */
    paramBuffer[parNum] = atof(par);
    
    printf("Paramter value = %f\n", paramBuffer[parNum]); //for debug purpose

    /* Iterate to next parameter in the buffer*/ 
    parNum++; 

    /*Escape Comma separated character*/
    i++;
  }

}
