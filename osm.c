#include "osm.h"
#include <unistd.h>

#define DEFAULT_ITERATIONS 50000
#define MICRO 1000000
// timeMeasurmentStructure
// OSM_NULLSYSCALL

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

/* Time measurement function for an empty trap into the operating system.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   Zero iterations number is invalid.

   */
double osm_syscall_time(unsigned int osm_iterations)
    double
{



}
/*
    @brief returns a timeval struct
    @return current timeval
*/
struct timeval getTime()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return tv;
}
/*
    @brief Calculate the time difference between 2 timevalues (tv2 - tv1);
    @param tv1 first timeval
    @param tv2 second timeval
    @return tv2 - tv1 in microseconds.
*/
long calculateTimeDiff(struct timeval tv1, struct timeval tv2)
{
    return (tv2.tv_sec - tv1.tv_sec)*MICRO + (tv2.tv_usec - tv1.tv_usec);
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
