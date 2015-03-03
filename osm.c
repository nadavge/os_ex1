#include "osm.h"
#include <unistd.h>

#define DEFAULT_ITERATIONS 50000
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
double osm_syscall_time(unsigned int osm_iterations);


/* Time measurement function for a simple arithmetic operation.
   returns time in nano-seconds upon success,
   and -1 upon failure.
   Zero iterations number is invalid.
   */
double osm_operation_time(unsigned int osm_iterations);
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
