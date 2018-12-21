#ifndef _LIBNVMTSX_H
#define _LIBNVMTSX_H

#include "libnvmtsx/base.h"


uint64_t pmemobj_type_num(PMEMoid oid);
int pmemobj_tx_add_range_direct(const void *ptr, size_t size);
int pmemobj_tx_free(PMEMoid oid);
PMEMoid pmemobj_tx_alloc(size_t size, uint64_t type_num);
void *pmemobj_direct(PMEMoid oid);
int pmemobj_tx_add_range_direct(const void *ptr, size_t size);
PMEMoid pmemobj_tx_alloc(size_t size, uint64_t type_num);
PMEMoid pmemobj_tx_zalloc(size_t size, uint64_t type_num);
int pmemobj_tx_free(PMEMoid oid);

#endif
