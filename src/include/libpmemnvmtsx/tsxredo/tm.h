#ifndef TM_H
#define TM_H 1

extern int  is_log_transaction;

#include "rlog.h"



#define TM_STARTUP(numThread)         rlog_init() 
#define TM_SHUTDOWN()                 rlog_finalize()
  
#define TM_THREAD_ENTER()             ({ \
			                                         long mytid = thread_getId(); \
			                                         bind_thread(mytid); \
			                                      })
#define TM_THREAD_EXIT()              /* nothing */

#define TX_BEGIN(pop) tsxrlog_begin();
#define TX_ONABORT
#define TX_END        tsxrlog_end();

#define TM_READ(var)           ((!is_log_transaction)?(var):rlog_load((rlog_word_t *)(void *)&(var)))
#define TM_READ_P(var)         ((!is_log_transaction)?(var):rlog_load_ptr((void **)(void *)&(var)))
#define TM_READ_F(var)         ((!is_log_transaction)?(var):rlog_load_float((float *)(void *)&(var)))
  
#define TM_WRITE(var, val)     ({  \
		                       if(!is_log_transaction){ \
		                    var=val; \
		                       }else{ \
		                    rlog_store((rlog_word_t *)(void *)&(var),(rlog_word_t)val);\
		                       } \
		                      })
		
#define TM_WRITE_P(var, val)   ({  \
		                    if(!is_log_transaction){ \
		                     var=val; \
		                    }else{ \
		                     rlog_store_ptr((void **)(void *)&(var), val); \
		                    } \
		                    })
#define TM_WRITE_F(var, val)   ({  \
		                    if(!is_log_transaction){ \
		                    var=val; \
		                    }else{ \
		                    rlog_store_float((float *)(void *)&(var), val); \
		                    } \
		                    })

#endif
