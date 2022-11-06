#pragma once
void AssertionHandlerMessage(const char* File, const char* Function, const char* Assertion, int LineNumber, const char* Message);
void AssertionHandler(const char* File, const char* Function, const char* Assertion, int LineNumber);
#define MEPH_ASSERT(assertion) if(!(assertion)){AssertionHandler(__FILE__, __FUNCTION__, #assertion, __LINE__);}
#define MEPH_ASSERT_M(assertion, message) if(!(assertion)){AssertionHandlerMessage(__FILE__, __FUNCTION__, #assertion, __LINE__, message);}