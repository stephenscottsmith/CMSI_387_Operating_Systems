/**
 * Test fixture for page replacement algorithms.
 */
#include "pageReplacement.h"

#include <assert.h>
#include <string.h>
#include <stdio.h>

#define REF_STR_1 "70120304230321201701"
#define REF_STR_2 "123412512345"
#define REF_STR_3 "37128399273645034162"

/**
 * Utility function for calculating the length of
 * a frame report string.
 */
int getFrameReportLength(const char *refString, int frameCount) {
    return (strlen(refString) + 1) * (frameCount + 1);
}

int main(int argc, char *argv[]) {
    // First test.
    char fr1_3[getFrameReportLength(REF_STR_1, 3)];
    replacePagesFIFO(REF_STR_1, 3, fr1_3);
    assert(strcmp(fr1_3, "---|7--|70-|701|201|201|231|230|430|420|423|023|023|023|013|012|012|012|712|702|701") == 0);
    
    // Do the 4-frame case for the same reference string.
    char fr1_4[getFrameReportLength(REF_STR_1, 4)];
    replacePagesFIFO(REF_STR_1, 4, fr1_4);
    assert(strcmp(fr1_4, "----|7---|70--|701-|7012|7012|3012|3012|3412|3412|3412|3402|3402|3402|3401|2401|2401|2401|2701|2701|2701") == 0);
    
    // Do LRU for 3 frames.
    replacePagesLRU(REF_STR_1, 3, fr1_3);
    assert(strcmp(fr1_3, "---|7--|70-|701|201|201|203|203|403|402|432|032|032|032|132|132|102|102|107|107|107") == 0);
    
    // Do it with 7 frames (maximum specified in the exercise).
    // (this one is actually pretty trivial, since we never access > 7 pages)
    char fr1_7[getFrameReportLength(REF_STR_1, 7)];
    replacePagesLRU(REF_STR_1, 7, fr1_7);
    assert(strcmp(fr1_7, "-------|7------|70-----|701----|7012---|7012---|70123--|70123--|701234-|701234-|701234-|701234-|701234-|701234-|701234-|701234-|701234-|701234-|701234-|701234-|701234-") == 0);
    
    // Do FIFO with the Belady's anomaly-prone reference string.
    char fr2_3[getFrameReportLength(REF_STR_2, 3)];
    replacePagesFIFO(REF_STR_2, 3, fr2_3);
    assert(strcmp(fr2_3, "---|1--|12-|123|423|413|412|512|512|512|532|534|534") == 0);
    
    // More page faults with 4 frames!
    char fr2_4[getFrameReportLength(REF_STR_2, 4)];
    replacePagesFIFO(REF_STR_2, 4, fr2_4);
    assert(strcmp(fr2_4, "----|1---|12--|123-|1234|1234|1234|5234|5134|5124|5123|4123|4523") == 0);
    
    // Let's do LRU on that.
    replacePagesLRU(REF_STR_2, 3, fr2_3);
    assert(strcmp(fr2_3, "---|1--|12-|123|423|413|412|512|512|512|312|342|345") == 0);
    replacePagesLRU(REF_STR_2, 4, fr2_4);
    assert(strcmp(fr2_4, "----|1---|12--|123-|1234|1234|1234|1254|1254|1254|1253|1243|5243") == 0);
    
    // Full-on 7-frame tests with a reference string that touches all 9 pages.
    replacePagesFIFO(REF_STR_3, 7, fr1_7);
    assert(strcmp(fr1_7, "-------|3------|37-----|371----|3712---|37128--|37128--|371289-|371289-|371289-|371289-|371289-|3712896|4712896|4512896|4502896|4503896|4503896|4503196|4503196|4503126") == 0);
    replacePagesLRU(REF_STR_3, 7, fr1_7);
    assert(strcmp(fr1_7, "-------|3------|37-----|371----|3712---|37128--|37128--|371289-|371289-|371289-|371289-|371289-|3712896|3742896|3742596|3742506|3742506|3742506|3741506|3741506|3241506") == 0);
}