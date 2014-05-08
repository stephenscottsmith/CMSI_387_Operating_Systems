/**
 * Interface for page replacement functions.
 */
#ifndef __PAGE_REPL__
#define __PAGE_REPL__

/**
 * Performs FIFO page replacement on the given reference string and
 * given frame count, and places the results in frameReport.
 */
void replacePagesFIFO(const char *refString, int frameCount, char *frameReport);

/**
 * Performs LRU page replacement on the given reference string and
 * given frame count, and places the results in frameReport.
 */
void replacePagesLRU(const char *refString, int frameCount, char *frameReport);

#endif