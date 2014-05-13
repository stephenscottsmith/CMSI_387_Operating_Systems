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
    // JD: Note how the bitwise-"&" is^^^^^^^^ unnecessary because of the right shift.
	int four_bits_farthest_right = (logical & PAGESIZE);

    // JD: This max check can be unhardcoded through got use of
    //     some #define's in addressTranslation.h
	if (logical < 0 || logical >= 256) {
        return ERR_OUT_OF_RANGE;
    } else if (ptr[four_bits_farthest_left].valid == 0) {
		return ERR_INVALID;
	} else {
		return (((ptr[four_bits_farthest_left].frame) << PAGEBITS) + four_bits_farthest_right);
	}
}