#ifndef _LIBNVMTSX_H
#define _LIBNVMTSX_H

#include <stddef.h>
#include <setjmp.h>
#include "libpmemnvmtsx/base.h"


//pmem
void pmem_persist(const void *addr, size_t len);
int pmem_msync(const void *addr, size_t len);
void pmem_drain(void);
void pmem_deep_flush(const void *addr, size_t len);
int pmem_is_pmem(const void *addr, size_t len);


const char *pmemobj_errormsg(void);
PMEMobjpool *pmemobj_create(const char *path, const char *layout, size_t poolsize, mode_t mode);
void pmemobj_close(PMEMobjpool *pop);

PMEMoid pmemobj_root(PMEMobjpool *pop, size_t size);

uint64_t pmemobj_type_num(PMEMoid oid);
void *pmemobj_direct(PMEMoid oid);

PMEMoid pmemobj_tp_zalloc(size_t size, uint64_t type_num);
PMEMoid pmemobj_tx_alloc(size_t size, uint64_t type_num);
int pmemobj_tx_free(PMEMoid oid);

int pmemobj_tx_begin(PMEMobjpool *pop, jmp_buf env, ...);
void pmemobj_tx_commit(void);
int pmemobj_tx_end(void);
int pmemobj_tx_add_range_direct(const void *ptr, size_t size);
int pmemobj_tx_add_range(PMEMoid oid, uint64_t off, size_t size);
#endif
