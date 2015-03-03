#include "osm.h"


// timeMeasurmentStructure
// OSM_NULLSYSCALL

/* Initialization function that the user must call
 * before running any other library function.
 * Returns 0 uppon success and -1 on failure.
 */
int osm_init();

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

timeMeasurmentStructure measureTimes (unsigned int osm_iterations);
