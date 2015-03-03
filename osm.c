#include "osm.h"
#include <unistd.h>

#define DEFAULT_ITERATIONS 50000
#define MICROSECONDS_TO_NANO 1000000
#define SECONDS_TO_NANO 1000000000
#define REPETITIONS 10
// timeMeasurmentStructure
// OSM_NULLSYSCALL

typedef struct timeval timeval;

/* Initialization function that the user must call
 * before running any other library function.
 * Returns 0 upon success and -1 on failure.
 */
int osm_init()
{

}

/* Time measurement function for an empty function call.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   Zero iterations number is invalid.
   */
double osm_function_time(unsigned int osm_iterations);

inline unsigned int roundUp(unsigned int num, unsigned int divider)
{
    unsigned int remainder = num % divider;
    unsigned int remainderConj = divider - remainder;
    return num + (remainder ? remainderConj : 0);
}
/* Time measurement function for an empty trap into the operating system.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   Zero iterations number is invalid.

   */
double osm_syscall_time(unsigned int osm_iterations)
{

    timeval start = getTime();
    osm_iterations = roundUp(osm_iterations, REPETITIONS);
    unsigned iterations_left = osm_iterations;
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

    timeval end = getTime();

    return timeDiffInNano(start, end, osm_iterations);
}
/*
    @brief returns a timeval struct
    @return current timeval
*/
timeval getTime()
{
    timeval tv;
    gettimeofday(&tv, NULL);
    return tv;
}
/*
    @brief Calculate average time of the operations
    @param tv1 start
    @param tv2 end
    @return tv2 - tv1 in nanoseconds.
*/
double timeDiffInNano(struct timeval tv1, struct timeval tv2, unsigned int iterations)
{
    double secondsDiff = ((double) tv2.tv_sec - tv1.tv_sec);
    double microDiff = ((double) tv2.tv_usec - tv1.tv_usec);
    double nanoDiff = secondsDiff*SECONDS_TO_NANO + microDiff*MICROSECONDS_TO_NANO;
    return nanoDiff / iterations;
}


/* Time measurement function for a simple arithmetic operation.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   Zero iterations number is invalid.
   */
double osm_operation_time(unsigned int osm_iterations)
{

}
/*
typedef struct {
	char machineName[HOST_NAME_MAX];
	int numberOfIterations;
	double instructionTimeNanoSecond;
	double functionTimeNanoSecond;
	double trapTimeNanoSecond;
	double functionInstructionRatio;
	double trapInstructionRatio;
} timeMeasurmentStructure;
*/
timeMeasurmentStructure measureTimes (unsigned int osm_iterations)
{
    timeMeasurmentStructure result = {0};
    if(! gethostname(result.machineName, HOST_NAME_MAX))
    {
        result.machineName[0] = NULL;
    }
    result.numberOfIterations = osm_iterations > 0 ? osm_iterations : DEFAULT_ITERATIONS;
    result.instructionTimeNanoSecond = osm_syscall_time(result.numberOfIterations);
    result.functionTimeNanoSecond = osm_function_time(result.numberOfIterations);
    result.trapTimeNanoSecond = osm_syscall_time(result.numberOfIterations);
    result.functionInstructionRatio = result.functionTimeNanoSecond / result.instructionTimeNanoSecond;
    result.trapInstructionRatio = result.trapTimeNanoSecond / result.instructionTimeNanoSecond;

    return result;


}
