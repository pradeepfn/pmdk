
#include "tsxseq.h"



#define TM_STARTUP(numThread)         tsxseqinit() 
#define TM_SHUTDOWN()                 tsxseqfinalize()
  
#define TM_THREAD_ENTER()             ({ \
			                                         long mytid = thread_getId(); \
			                                         bind_thread(mytid); \
			                                      })
#define TM_THREAD_EXIT()              /* nothing */

#define TX_BEGIN(pop) tsxseqbegin();
#define TX_ONABORT
#define TX_END        tsxseqend();

#define TM_READ(var)           (var)
#define TM_READ_P(var)         (var)
#define TM_READ_F(var)         (var)
  
#define TM_WRITE(var, val)     var = val
#define TM_WRITE_P(var, val)   var = val
#define TM_WRITE_F(var, val)   var = val
