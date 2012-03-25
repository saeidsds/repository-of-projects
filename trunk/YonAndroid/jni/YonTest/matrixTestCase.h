
#ifndef _MATRIX_TEST_CASE_
#define _MATRIX_TEST_CASE_

#pragma comment(lib, "cppunitd.lib")
#pragma comment(lib, "Yon.lib")

#include <cppunit/extensions/HelperMacros.h>
#include "yon.h"

using namespace yon;
using namespace yon::core;

class matrixTestCase : public CPPUNIT_NS::TestFixture
{
	CPPUNIT_TEST_SUITE( matrixTestCase );
	CPPUNIT_TEST( rotateVector );
	CPPUNIT_TEST_SUITE_END();

public:
	void setUp();

protected:
	void rotateVector();
};

#endif