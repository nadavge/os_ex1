#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <stdio.h>
#include "osm.h"
#define DEFAULT_ITERATIONS 50000
#define MICROSECONDS_TO_NANO 1000
#define SECONDS_TO_NANO 1000000000
#define REPETITIONS 10
#define GET_TIME(tv) if(gettimeofday(&tv, 0) == -1) return -1

typedef struct timeval timeval;

/**
* @brief Rounds up a number to be a multiple of another number
*
* @param num the number to round up
* @param base the number to serve as the base
*
* @return 
*/
inline unsigned int roundUp(unsigned int num, unsigned int base)
{
    unsigned int remainder = num % base;
    unsigned int remainderConj = base - remainder;
    return num + (remainder ? remainderConj : 0);
}

/**
* @brief Returns the average iteration time based on start time, stop time and iteration count
*
* @param tv1 the first timevalue
* @param tv2 the second timevalue
* @param iterations the number of iterations to average on
*
* @return the average iteration time in nanoseconds
*/
double timeDiffInNano(timeval tv1, timeval tv2, unsigned int iterations)
{
    double secondsDiff = (tv2.tv_sec - tv1.tv_sec);
    double microDiff = (tv2.tv_usec - tv1.tv_usec);
    double nanoDiff = (secondsDiff*SECONDS_TO_NANO) + (microDiff*MICROSECONDS_TO_NANO);
    return nanoDiff/iterations;
}

/* Initialization function that the user must call
 * before running any other library function.
 * Returns 0 upon success and -1 on failure.
 */
int osm_init()
{
    return 0;
}

/*
*    @brief empty function
*/
void __attribute__((noinline)) emptyFunction()
{
}

/* Time measurement function for an empty function call.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   Zero iterations number is invalid.
   */
double osm_function_time(unsigned int osm_iterations)
{
    if (osm_iterations == 0)
    {
        return -1;
    }

    timeval start = {0};
    timeval end = {0};
    
    osm_iterations = roundUp(osm_iterations, REPETITIONS);
    unsigned iterations_left = osm_iterations;

    GET_TIME(start);

    while(iterations_left > 0)
    {
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();
        emptyFunction();

	iterations_left -= REPETITIONS;
    }

    GET_TIME(end);

    return timeDiffInNano(start, end, osm_iterations);
}
/* Time measurement function for an empty trap into the operating system.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   Zero iterations number is invalid.

   */
double osm_syscall_time(unsigned int osm_iterations)
{
    if (osm_iterations == 0)
    {
        return -1;
    }

    timeval start = {0};
    timeval end = {0};

    osm_iterations = roundUp(osm_iterations, REPETITIONS);
    unsigned iterations_left = osm_iterations;

    GET_TIME(start);
    while(iterations_left > 0)
    {
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;
        OSM_NULLSYSCALL;

        iterations_left -= REPETITIONS;
    }

    GET_TIME(end);

    return timeDiffInNano(start, end, osm_iterations);
}

/* Time measurement function for a simple arithmetic operation.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   Zero iterations number is invalid.
   */
double osm_operation_time(unsigned int osm_iterations)
{
    if (osm_iterations == 0)
    {
        return -1;
    }
    
    timeval start = {0};
    timeval end = {0};

    osm_iterations = roundUp(osm_iterations, REPETITIONS);
    unsigned iterations_left = osm_iterations;
    register int a = 1337;

    GET_TIME(start);
    while(iterations_left > 0)
    {
	a += a;
	a += a;
	a += a;
	a += a;
	a += a;
	a += a;
	a += a;
	a += a;
	a += a;
	a += a;

	iterations_left -= REPETITIONS;
    }

    GET_TIME(end);

    // It is used here to require a to be calculated and not removed on optimization
    int b = a;
    // Put to avoid warnings in compilation
    a = b;

    return timeDiffInNano(start, end, osm_iterations);
}

/* Time measurement function that runs all of the functions in the file,
	gets number of iteration and returns a struct with the relevant times,
	-1 on fail in case of fail in some of the tests (or 0 in case of the machine name).
   */
timeMeasurmentStructure measureTimes (unsigned int osm_iterations)
{
    timeMeasurmentStructure result = {{0}};
    if(!gethostname(result.machineName, HOST_NAME_MAX))
    {
        result.machineName[0] = 0;
    }
    result.numberOfIterations = osm_iterations > 0 ? osm_iterations : DEFAULT_ITERATIONS;
    result.instructionTimeNanoSecond = osm_operation_time(result.numberOfIterations);
    result.functionTimeNanoSecond = osm_function_time(result.numberOfIterations);
    result.trapTimeNanoSecond = osm_syscall_time(result.numberOfIterations);
    result.functionInstructionRatio = result.functionTimeNanoSecond / result.instructionTimeNanoSecond;
    result.trapInstructionRatio = result.trapTimeNanoSecond / result.instructionTimeNanoSecond;

    return result;
}
