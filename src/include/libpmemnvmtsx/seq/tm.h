

#define TM_STARTUP(numThread)         
#define TM_SHUTDOWN()                 
  
#define TM_THREAD_ENTER()             
			                                    
#define TM_THREAD_EXIT()              /* nothing */

#define TX_BEGIN(pop) 
#define TX_ONABORT
#define TX_END        

#define TM_READ(var)           (var)
#define TM_READ_P(var)         (var)
#define TM_READ_F(var)         (var)
  
#define TM_WRITE(var, val)     var = val
#define TM_WRITE_P(var, val)   var = val
#define TM_WRITE_F(var, val)   var = val
