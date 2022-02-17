/************************************* 
 *  Luca Nogarotto - SYWARE LTD
 *  February 2022
 *
 *  Coderbyte - Array Jump exercise
 *  -------------------------------
 *  Have the function ArrayJumping(arr) take the array of numbers stored in arr
 *  and first determine the largest element in the array,
 *  and then determine whether or not you can reach that same element within
 *  the array by moving left or right continuously according to whatever integer
 *  is in the current spot. If you can reach the same spot within the array,
 *  then your program should output the least amount of jumps it took.
 *  For example: if the input is [2, 3, 5, 6, 1] you'll start at the spot where
 *  6 is and if you jump 6 spaces to the right while looping around the array you
 *  end up at the last element where the 1 is. Then from here you jump 1 space to
 *  the left and you're back where you started, so your program should output 2.
 *  If it's impossible to end up back at the largest element in the array your
 *  program should output -1. The largest element in the array will never equal
 *  the number of elements in the array. The largest element will be unique. 
 *  Input:1,2,3,4,2
 *  Output:3
 *  Input:1,7,1,1,1,1
 *  Output:2
 **************************************/

#include "stdio.h"
#include "stdlib.h"

//#define DEBUG

#if defined(DEBUG)
    #define debugPrint printf
#else
    #define debugPrint(...)
#endif


typedef enum
{
    LEFT,
    RIGHT
} JumpDirection;


// Find index of bigger element within an array
static int FindMaxIdx(const int *arr, const int arrLength)
{
	int i, maxIdx = 0;
    
	for(i = 0; i < arrLength; i++)
	{
		if(arr[i] > arr[maxIdx])
		{
			maxIdx = i;
		}
	}
    
	debugPrint("maxIdx = %d\n", maxIdx);
    
	return maxIdx;
}


// Calculate necessary jumps using recursion
static int CountJumps(const int *arr, const int arrLength, const int maxIdx, int currIdx, int jumpsCount, const JumpDirection dir)
{
    int leftJumps, rightJumps, res;
    
    // This is one more jump
	jumpsCount++;
	
    // Jump to next array index based on currently indexed array value
	debugPrint("jump %d: currIdx = %d, ", jumpsCount, currIdx);
	if(dir == LEFT)
	{
		currIdx = currIdx - (arr[currIdx] % arrLength);
		if(currIdx < 0) currIdx += arrLength;
        debugPrint("left jumped to idx %d\n", currIdx);
	}
	else
	{
		currIdx = (currIdx + (arr[currIdx] % arrLength)) % arrLength;
        debugPrint("right jumped to idx %d\n", currIdx);
	}
	
	// Calculate path recursively
	if(currIdx != maxIdx)
	{
        // Have all possibilities been tried?
		if(jumpsCount < arrLength)
		{
			leftJumps = CountJumps(arr, arrLength, maxIdx, currIdx, jumpsCount, LEFT);
			debugPrint("left jump = %d\n", leftJumps);
			rightJumps = CountJumps(arr, arrLength, maxIdx, currIdx, jumpsCount, RIGHT);
			debugPrint("right jump = %d\n", rightJumps);
			
			if((leftJumps != -1) && (rightJumps != -1))
			{
                // Multiple paths available, choose the shorter
                if(leftJumps < rightJumps)
                {
                    res = leftJumps;
                }
                else
                {
                    res = rightJumps;
                }
			}
			else
			{
                // There may be one path available
				if(leftJumps != -1)
                {
                    res = leftJumps;
                }
				else
                {
                    res = rightJumps;
                }
			}
		}
		else
		{
            // Could not find a possible path - end recursion
			res = -1;
		}
	}
	else
	{
        // Path found - end recursion
		res = jumpsCount;
	}
    
    return res;
}


int ArrayJumpsExercise(const int *arr, const int arrLength)
{
	int maxIdx, leftJumps, rightJumps, res;
	
    // Find index with max value
    maxIdx = FindMaxIdx(arr, arrLength);
	
    // Calculate jumps necessary to end up at maxIdx again
	leftJumps = CountJumps(arr, arrLength, maxIdx, maxIdx, 0, LEFT);
	debugPrint("total left jumps %d\n", leftJumps);
	rightJumps = CountJumps(arr, arrLength, maxIdx, maxIdx, 0, RIGHT);
	debugPrint("total right jumps %d\n", rightJumps);
	
    if((leftJumps != -1) && (rightJumps != -1))
    {
        // Multiple paths available, choose the shorter
        if(leftJumps < rightJumps)
        {
            res = leftJumps;
        }
        else
        {
            res = rightJumps;
        }
    }
    else
    {
        // There may be one path available
        if(leftJumps != -1)
        {
            res = leftJumps;
        }
        else
        {
            res = rightJumps;
        }
    }

	return res;
}


int main(void)
{

	int arr[] = {1,2,4,1,1}; // should print 2
    //int arr[] = {1,2,7,2,1}; // should print -1

	printf("%d\n", ArrayJumpsExercise(arr, sizeof(arr)/sizeof(int)));
	
	return 0;
}