/************************************* 
 *  Luca Nogarotto - SYWARE LTD
 *  February 2022
 *
 *  Coderbyte - Array PlusMinus exercise
 *  -------------------------------
 *  Write a function plusMinus(num), with the num parameter being a combination of 1 or
 *  more single digits. Determine if it is possible to separate the digits with either
 *  a plus or minus sign to get the final expression to equal zero.
 *  For example: if num is 35132 then it's possible to separate the digits the following
 *  way, 3 - 5 + 1 + 3 - 2, and this expression equals zero. Your program should return
 *  a string of the signs you used, so for this example your program should return the
 *  string "-++-".
 *  If it's not possible to get the digit expression to equal zero, return the string
 *  "not possible".
 *  If there are multiple ways to get the final expression to equal zero, choose the one
 *  that contains more minus characters. For example: if num is 26712 your program should
 *  return "-+--" and not "+-+-".
 **************************************/

#include "stdlib.h"
#include "stdio.h"

//#define DEBUG

#if defined(DEBUG)
    #define debugPrint printf
#else
    #define debugPrint(...)
#endif

typedef enum
{
    DIFF,
    SUM
} Operation;

static int FindNumOfDigits(int num)
{
    int numDigits = 0;
    
    debugPrint("%d has ", num);
    while(num != 0)
    {
        numDigits++;
        num /= 10;
    }
    debugPrint("%d digits\n", numDigits);
    
    return numDigits;
}

static void SeparateDigits(int num, int *arr, const int numDigits)
{
    int i;
    
    for(i = 0; i < numDigits; i++)
    {
        arr[numDigits - i - 1] = num % 10;
        num /= 10;
    }
    
    for(i = 0; i < numDigits; i++)
    {
        debugPrint("%d ", arr[i]);
    }
    debugPrint("\n");
}

static int Calc(const int const *arr, const int arrLength, char *resString, int currRes, int currIdx, const Operation op)
{
	int newRes = currRes;
	
	currIdx++;
	
    // Are the digits finished ?
	if(currIdx < arrLength)
	{
        // Subtract/Add current indexed value
        debugPrint("current result = %d", currRes);
        if(op == DIFF)
        {
            currRes -= arr[currIdx];
            debugPrint(" - ");
        }
        else
        {
            currRes += arr[currIdx];
            debugPrint(" + ");
		}
        debugPrint("arr[%d] = %d\n", currIdx, currRes);
		
        // Next calculation recursively
		newRes = Calc(arr, arrLength, resString, currRes, currIdx, DIFF);
		
		if(newRes != 0)
		{
			newRes = Calc(arr, arrLength, resString, currRes, currIdx, SUM);
		}
		if(newRes == 0)
		{
            if(op == DIFF)
            {
                resString[currIdx - 1] = '-';
            }
            else
            {
                resString[currIdx - 1] = '+';
            }
		}
	}
	
	return newRes;
}


int ArrayPlusMinus(const int num)
{
	int newRes;
    
    // Find number of digits
    int arrLength = FindNumOfDigits(num);
    
    // Separate digits
    int *arr = malloc(sizeof(int) * arrLength);
    SeparateDigits(num, arr, arrLength);
    
    // Prepare (and terminate) signs string
    char *resString = malloc(sizeof(char) * arrLength);
    resString[arrLength - 1] = 0;
    
    // Calculation - priority to subtraction
    newRes = Calc(arr, arrLength, resString, arr[0], 0, DIFF);
	
	if(newRes != 0)
	{
		newRes = Calc(arr, arrLength, resString, arr[0], 0, SUM);
	}
	
	if(newRes == 0)
	{
		printf("%s\n", resString);
	}
	else
	{
		printf("not possible\n");
	}
	
	return newRes;
}


int main(void)
{
	int num = 26712;
	
    int res = ArrayPlusMinus(num);
    
	debugPrint("result = %d\n", res);
	
	return 0;
}