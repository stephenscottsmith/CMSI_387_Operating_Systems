/**
 * Implementation of the software paging unit.
 */
#include "addressTranslation.h"

#include <stdio.h>
#include <stdlib.h>

static pagetable *ptr = NULL; // ptr = "page table register"

void setPageTable(pagetable *pt) {
    ptr = pt;
}

int getPhysical(int logical) {
	int four_bits_farthest_left = ((logical & PAGEMASK) >> PAGEBITS);
	int four_bits_farthest_right = (logical & PAGESIZE);

	if (logical < 0 || logical >= 256) {
        return ERR_OUT_OF_RANGE;
    } else if (ptr[four_bits_farthest_left].valid == 0) {
		return ERR_INVALID;
	} else {
		return (((ptr[four_bits_farthest_left].frame) << PAGEBITS) + four_bits_farthest_right);
	}
}