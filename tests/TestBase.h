#ifndef LIB_RATSS_TESTS_TEST_BASE_H
#define LIB_RATSS_TESTS_TEST_BASE_H
#pragma once
#include <cppunit/ui/text/TestRunner.h>
#include <cppunit/extensions/HelperMacros.h>
#include <cppunit/Asserter.h>
#include <cppunit/TestAssert.h>
#include <cppunit/TestResult.h>

#include <libratss/constants.h>
#include <libratss/Conversion.h>

namespace LIB_RATSS_NAMESPACE {
namespace tests {
	
std::size_t numBits(mpq_class const & v);
std::size_t numBits(mpz_class const & v);

class TestBase: public CppUnit::TestFixture {
// CPPUNIT_TEST_SUITE( Test );
// CPPUNIT_TEST( test );
// CPPUNIT_TEST_SUITE_END();
public:
	TestBase();
	virtual ~TestBase();
public:
	static void init(int argc, char ** argv);
private:
	static int argc;
	static char ** argv;
	
};

}} //end namespace ratss::tests

/*
int main(int argc, char ** argv) {
	ratss::tests::TestBase::init(argc, argv);
	srand( 0 );
	CppUnit::TextUi::TestRunner runner;
	runner.addTest(  Test::suite() );
	bool ok = runner.run();
	return ok ? 0 : 1;
}
*/

#endif
