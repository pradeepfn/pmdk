#ifndef TM_H
#define TM_H 1

#include "rlog.h"



#define TM_STARTUP(numThread)         rlog_init() 
#define TM_SHUTDOWN()                 rlog_finalize()
  
#define TM_THREAD_ENTER()             ({ \
			                                         long mytid = thread_getId(); \
			                                         bind_thread(mytid); \
			                                      })
#define TM_THREAD_EXIT()              /* nothing */

#define TX_BEGIN(pop) rlog_begin();
#define TX_ONABORT
#define TX_END        rlog_end();

#define TM_READ(var)           (rlog_load((rlog_word_t *)(void *)&(var)))
#define TM_READ_P(var)         (rlog_load_ptr((void **)(void *)&(var)))
#define TM_READ_F(var)         (rlog_load_float((float *)(void *)&(var)))
  
#define TM_WRITE(var, val)     ({ \
		                      rlog_store((rlog_word_t *)(void *)&(var), (rlog_word_t)val); \
		                      })
#define TM_WRITE_P(var, val)   ({ \
		                      rlog_store_ptr((void **)(void *)&(var), (val)); \
		                      })
#define TM_WRITE_F(var, val)   ({ \
		                      rlog_store_float((float *)(void *)&(var), (val)); \
		                      })

#endif
