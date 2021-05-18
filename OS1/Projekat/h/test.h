/**
 * test.h
 *
 * Testing-related utilities.
 */
#ifndef _TEST_H_
#define _TEST_H_
#include <util.h>

void dumbSleep(int delay);
void testResult(unsigned condition);
void testCase(const char* message, unsigned condition);

#endif
