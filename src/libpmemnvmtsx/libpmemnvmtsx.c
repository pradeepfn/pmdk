#include "libpmemnvmtsx.h"



PMEMoid pmemobj_tx_zalloc(size_t size, uint64_t type_num)
{
	return OID_NULL;
}



const char *pmemobj_errormsg(void)
{

	return "error";
}


/* pmem */

int pmem_msync(const void *addr, size_t len)
{

	return 0;
}

void pmem_persist(const void *addr, size_t len)
{

	
}


void pmem_drain(void)
{

}

void pmem_deep_flush(const void *addr, size_t len)
{

}

int pmem_is_pmem(const void *addr, size_t len)
{

	return 0;
}



PMEMobjpool *pmemobj_create(const char *path, const char *layout, size_t poolsize, mode_t mode)
{
	return NULL;
}

void pmemobj_close(PMEMobjpool *pop)
{

}

PMEMoid pmemobj_root(PMEMobjpool *pop, size_t size)
{

	return OID_NULL;
}

uint64_t pmemobj_type_num(PMEMoid oid)
{
	return 0;
}

void *pmemobj_direct(PMEMoid oid)
{
	return NULL;
}

PMEMoid pmemobj_tx_alloc(size_t size, uint64_t type_num)
{

	return OID_NULL;
}


int pmemobj_tx_free(PMEMoid oid)
{
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



