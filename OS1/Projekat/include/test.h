/**
 * test.h
 *
 * Testing-related utilities.
 */
#ifndef _TEST_H_
#define _TEST_H_
#include <iostream.h>

void testUtil();
void testVector();
void testList();
void testThread();
void testKernel();
void testSemaphore();
void testIVT();
void testEvent();

void testResult(unsigned condition);
void testCase(const char* message, unsigned condition);

#endif