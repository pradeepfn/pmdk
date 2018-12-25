#include <stdio.h>
#include <stdlib.h>

#include "libpmemnvmtsx.h"



const char *pmemobj_errormsg(void)
{
	return "error in pmemobj action";
}

int pmem_msync(const void *addr, size_t len)
{
	printf("calling pmem_sync: not implemented");	
	return 0;
}

void pmem_persist(const void *addr, size_t len)
{
	printf("calling pmem_persist: not implemented");	
}

void pmem_drain(void)
{
	printf("calling pmem_drain: not implemented");	
}

void pmem_deep_flush(const void *addr, size_t len)
{
	printf("calling pmem_deep_flush: not implemented");	
}

int pmem_is_pmem(const void *addr, size_t len)
{
	/* always we are operating on pmem */	
	return 1;
}



PMEMobjpool *pmemobj_create(const char *path, const char *layout, size_t poolsize, mode_t mode)
{
	return (PMEMobjpool *)malloc(sizeof(PMEMobjpool));
}

void pmemobj_close(PMEMobjpool *pop)
{
	free(pop);
}

PMEMoid pmemobj_root(PMEMobjpool *pop, size_t size)
{
	PMEMoid root;
	root.pool_uuid_lo = 0;
	root.off = (uint64_t)malloc(size);
	return root;
}

uint64_t pmemobj_type_num(PMEMoid oid)
{
	return oid.type;
}

void *pmemobj_direct(PMEMoid oid)
{
	return (void *)oid.off;
}

PMEMoid pmemobj_tx_alloc(size_t size, uint64_t type_num)
{
	PMEMoid oid;
	oid.pool_uuid_lo = 0;
	oid.off = (uint64_t)malloc(size);
	oid.type = type_num;
	return oid;
}


int pmemobj_tx_free(PMEMoid oid)
{
	free((void *)oid.off);	
	return 0;
}
			 

int pmemobj_tx_begin(PMEMobjpool *pop, jmp_buf env, ...)
{
	return 0;
}

void pmemobj_tx_commit(void)
{
	return;
}

int pmemobj_tx_end(void)
{
	return 0;
}

int pmemobj_tx_add_range_direct(const void *ptr, size_t size)
{
	return 0;
}



