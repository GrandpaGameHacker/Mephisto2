#pragma once

void AssertionHandler(const char* File, const char* Function, const char* Assertion, int LineNumber);
#define MEPH_ASSERT(assertion) if(!(assertion)){AssertionHandler(__FILE__, __FUNCTION__, #assertion, __LINE__);}