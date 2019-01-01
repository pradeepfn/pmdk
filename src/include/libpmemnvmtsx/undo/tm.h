
#include "ulog.h"



#define TM_STARTUP(numThread)         ulog_init() 
#define TM_SHUTDOWN()                 ulog_finalize()
  
#define TM_THREAD_ENTER()             ({ \
			                                         long mytid = thread_getId(); \
			                                         bind_thread(mytid); \
			                                      })
#define TM_THREAD_EXIT()              /* nothing */

#define TX_BEGIN(pop) ulog_begin();
#define TX_ONABORT
#define TX_END        ulog_end();

#define TM_READ(var)           (var)
#define TM_READ_P(var)         (var)
#define TM_READ_F(var)         (var)
  
#define TM_WRITE(var, val)     ({ulog_store((ulog_word_t *)(void *)&(var), (ulog_word_t)val); var=val;})
#define TM_WRITE_P(var, val)   ({ulog_store_ptr((void **)(void *)&(var), val); var=val;})
#define TM_WRITE_F(var, val)   ({ulog_store_float((float *)(void *)&(var), val); var=val;})
