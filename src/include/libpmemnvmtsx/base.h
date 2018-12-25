#ifndef _LIBPMEMNVMTSX_BASE_H
#define _LIBPMEMNVMTSX_BASE_H

#include <stdint.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

#define PMEMOBJ_MIN_POOL ((size_t)(1024 * 1024 * 8)) /* 8 MiB */
//typedef int mode_t;

typedef struct pmemoid {
		uint64_t pool_uuid_lo;
		uint64_t off;
		uint64_t type; // we carry the type
} PMEMoid;


#define POBJ_ROOT(pop, t) (\
		  (TOID(t))pmemobj_root((pop), sizeof(t)))


#define TOID_EQUALS(lhs, rhs)\
	  ((lhs).oid.off == (rhs).oid.off &&\
		     (lhs).oid.pool_uuid_lo == (rhs).oid.pool_uuid_lo)

#define POBJ_ROOT_TYPE_NUM 0
#define _toid_struct
#define _toid_union
#define _toid_enum

/*
   * Typed OID
   */
  #define TOID(t)\
  union _toid_##t##_toid
  
  #ifdef __cplusplus
  #define _TOID_CONSTR(t)\
  _toid_##t##_toid()\
  { }\
  _toid_##t##_toid(PMEMoid _oid) : oid(_oid)\
  { }
  #else
  #define _TOID_CONSTR(t)
  #endif
  
  /*
   * Declaration of typed OID
   */
  #define _TOID_DECLARE(t, i)\
  typedef uint8_t _toid_##t##_toid_type_num[(i) + 1];\
  TOID(t)\
  {\
    _TOID_CONSTR(t)\
    PMEMoid oid;\
    t *_type;\
    _toid_##t##_toid_type_num *_type_num;\
  }
  
  /*
   * Declaration of typed OID of an object
   */
  #define TOID_DECLARE(t, i) _TOID_DECLARE(t, i)

#define TOID_DECLARE_ROOT(t) _TOID_DECLARE(t, POBJ_ROOT_TYPE_NUM)

static const PMEMoid OID_NULL = { 0, 0, 0};
#define TOID_NULL(t)  ((TOID(t))OID_NULL)
#define TOID_IS_NULL(o) ((o).oid.off == 0)
#define OID_IS_NULL(o)  ((o).off == 0)
#define OID_IS_NULL(o)  ((o).off == 0)
#define OID_EQUALS(lhs, rhs)\
	((lhs).off == (rhs).off &&\
	   (lhs).pool_uuid_lo == (rhs).pool_uuid_lo)

#define TOID_TYPE_NUM_OF(o) (sizeof(*(o)._type_num) - 1)
#define TOID_TYPE_NUM(t) (sizeof(_toid_##t##_toid_type_num) - 1)
//#define TOID_VALID(o) (TOID_TYPE_NUM_OF(o) == pmemobj_type_num((o).oid))
#define OID_INSTANCEOF(o, t) (TOID_TYPE_NUM(t) == pmemobj_type_num(o))


#define TOID_VALID(o) (1)
//#define OID_INSTANCEOF(o, t) (TOID_TYPE_NUM(t) == TOID_TYPE_NUM_OF(o))

#define TOID_ASSIGN(o, value)(\
      {\
        (o).oid = value;\
        (o); /* to avoid "error: statement with no effect" */\
      })  


#define DIRECT_RW(o) (\
{__typeof__(o) _o; _o._type = NULL; (void)_o;\
(__typeof__(*(o)._type) *)pmemobj_direct((o).oid); })
#define DIRECT_RO(o) ((const __typeof__(*(o)._type) *)pmemobj_direct((o).oid))

#define D_RW  DIRECT_RW
#define D_RO  DIRECT_RO

struct pmemobjpool {
  void *addr;
  int is_pmem;
};


typedef struct pmemobjpool PMEMobjpool;

/* transaction API */

#define TX_BEGIN(pop)
#define TX_ONABORT
#define TX_END

#define TX_NEW(t)\
  ((TOID(t))pmemobj_tx_alloc(sizeof(t), TOID_TYPE_NUM(t)))

#define TX_ZNEW(t)\
 	((TOID(t))pmemobj_tx_alloc(sizeof(t), TOID_TYPE_NUM(t)))
//#define TX_ZNEW(t) ((TOID(t))pmemobj_tx_zalloc(sizeof(t), TOID_TYPE_NUM(t)))

#define TX_FREE(o)\
  pmemobj_tx_free((o).oid)


#define TX_ADD_FIELD(o, field) TX_ADD_DIRECT(&(D_RO(o)->field))
#define TX_ADD_DIRECT(p) pmemobj_tx_add_range_direct(p, sizeof(*p))

#endif
