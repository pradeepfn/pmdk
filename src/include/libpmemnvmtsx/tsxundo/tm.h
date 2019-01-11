#ifndef TM_H
#define TM_H 1

extern int  is_log_transaction;


#include "ulog.h"



#define TM_STARTUP(numThread)         ulog_init() 
#define TM_SHUTDOWN()                 ulog_finalize()
  
#define TM_THREAD_ENTER()             ({ \
			                                         long mytid = thread_getId(); \
			                                         bind_thread(mytid); \
			                                      })
#define TM_THREAD_EXIT()              /* nothing */

#define TX_BEGIN(pop) tsxulog_begin();
#define TX_ONABORT
#define TX_END        tsxulog_end();

#define TM_READ(var)           (var)
#define TM_READ_P(var)         (var)
#define TM_READ_F(var)         (var)
  
#define TM_WRITE(var, val)     ({  \
		                                            if(!is_log_transaction){ \
		                                                var=val; \
		                                            }else{ \
		                                                ulog_store((ulog_word_t *)(void *)&(var),(ulog_word_t)val); \
		                                                var=val;\
		                                            } \
		                                        })
#define TM_WRITE_P(var, val)	({  \
		                                            if(!is_log_transaction){ \
		                                                var=val; \
		                                            }else{ \
		                                                ulog_store_ptr((void **)(void *)&(var), val); \
		                                                var=val;\
		                                            } \
		                                        })
#define TM_WRITE_F(var, val)   ({  \
		                                            if(!is_log_transaction){ \
		                                                var=val; \
		                                            }else{ \
		                                                ulog_store_float((float *)(void *)&(var), val); \
		                                                var=val;\
		                                            } \
		                                        })

#endif