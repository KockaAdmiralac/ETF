/**
 * util.h
 *
 * Interface of project-wide utility functions and macros.
 */
#ifndef _UTIL_H_
#define _UTIL_H_

// Common boolean expressions not present in this standard of C++.
#define true 1
#define false 0
// https://thedailywtf.com/articles/what_is_truth_0x3f_
#define FILE_NOT_FOUND 2

// Interrupt control macros.
#define lock asm cli
#define unlock asm sti

// Common pointer type.
#define nullptr 0

unsigned ensure(unsigned condition, const char *message);
unsigned getPSW();
unsigned getBit(unsigned number, unsigned bit);
int syncPrint(const char *format, ...);

#endif
