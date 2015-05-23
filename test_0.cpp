// test_0.cpp written by JaeHyuk Kwak
#include "stdafx.h"
#include "unit_test_logic.hpp"
using namespace unit_test_logic_ns;
int main( int, const char ** )
{
	fixture f;
	f.test_case( "Boolean test", []
	{
		test_true( true );
		test_true( 2 <= 3 );
		test_false( false );
	} );
	f.test_case( "Equality test; simple", []
	{
		test( logic( 0 ) == 0 );
		test( logic( 3 ) == 3 );
		test( logic( 0 ) == 0.f, "Forwarding different types except bool" );
	} );
	f.test_case( "Inequality test; simple", []
	{
		test( logic( 0 ) != 1 );
		test( logic( 0 ) != 1.f, "Forwarding different types except bool" );
		test( ( logic( 0 ) != 1 ) != 2, "3 != 4 && 3 != 5" );
	} );
	f.test_case( "Compare '>' test; simple", []
	{
		test( logic( 3 ) > 2 );
		test( logic( 3 ) > 2 > 1 );
	} );
	f.test_case( "Compare '>=' test; simple", []
	{
		test( logic( 3 ) >= 3 );
		test( logic( 3 ) >= 3 >= 2 );
	} );
	f.test_case( "Compare '<' test; simple", []
	{
		test( logic( 3 ) < 4 );
		test( logic( 3 ) < 4 < 5 );
	} );
	f.test_case( "Compare '<=' test; simple", []
	{
		test( logic( 3 ) <= 3 );
		test( logic( 3 ) <= 3 <= 4 );
	} );
	f.test_case( "Unconditional success", []
	{
		test_success();
	} );
	f.test_case_must_fail( "Unconditional fail", []
	{
		test_fail();
	} );
	f.test_case( "Logic OR test; simple", []
	{
		test_true( ( logic( 0 ) == 0 ).out() || false );
		test_true( ( logic( 0 ) == 1 ) .out()|| true );
		test_true( false || ( logic( 0 ) == 0 ).out() );
		test_true( true || ( logic( 0 ) == 1 ).out() );
	} );
	{
		const char *str = "content";
		const char *str2 = "_content" + 1;
		f.test_case( "C-string test; raw-string pointer", [&]
		{
			test( logic( str ) == str );
			test( logic( str ) != str2 );
		} );
		f.test_case_must_fail( "C-string test; raw-string pointer", [&]
		{
			test( logic( str ) == str2, "the content of C-string will be shown" );
		} );
		f.test_case( "std::string test", [&]
		{
			test( logic( string( str ) ) == str2 );
		} );
		f.test_case_must_fail( "std::string test", [&]
		{
			test( logic( string( str ) ) != str2 );
		} );
	}
	f.test_case( "String test; ignore-case", []
	{
		const char *A = "A";
		const char *a = "a";
		test( logic( lowercase_string( A ) ) == lowercase_string( a ) );
	} );
	f.test_case( "Exception catch test", []
	{
		test_must_throw_exception< invalid_argument >( []
		{
			throw invalid_argument( "" );
		} );
	} );
	f.test_case_must_fail( "Exception catch test", []
	{
		test_must_throw_exception< invalid_argument >( []
		{} );
	} );
	f.test_case( "Exception ignore test", []
	{
		test_ignore_exception< invalid_argument >( []
		{
			throw invalid_argument( "" );
		} );
	} );
	f.test_case( "Exception ignore test; no exception thrown", []
	{
		test_ignore_exception< invalid_argument >( []
		{} );
	} );

	// Macro below could be replaced with a template function,
	// but it wasn't any easier to read.
	f.test_case( "Equality test; int", []
	{
		int lvalue_inlogic = 0;
		int lvalue = 0;
		#define TESTING_OPERATOR ==
		#include "test_0.operator.hpp"
		#undef TESTING_OPERATOR
	} );
	f.test_case( "Equality test; float", []
	{
		float lvalue_inlogic = 0.f;
		int lvalue = 0.f;
		#define TESTING_OPERATOR ==
		#include "test_0.operator.hpp"
		#undef TESTING_OPERATOR
	} );
	f.test_case( "Inequality test; int", []
	{
		int lvalue_inlogic = 2;
		int lvalue = 1;
		#define TESTING_OPERATOR !=
		#include "test_0.operator.hpp"
		#undef TESTING_OPERATOR
	} );
	f.test_case( "Inequality test; float", []
	{
		float lvalue_inlogic = 2;
		int lvalue = 1;
		#define TESTING_OPERATOR !=
		#include "test_0.operator.hpp"
		#undef TESTING_OPERATOR
	} );
	f.test_case( "Compare '>' test; int", []
	{
		int lvalue_inlogic = 1;
		int lvalue = -1;
		#define TESTING_OPERATOR >
		#include "test_0.operator.hpp"
		#undef TESTING_OPERATOR
	} );
	f.test_case( "Compare '>' test; float", []
	{
		float lvalue_inlogic = 1.f;
		int lvalue = -1;
		#define TESTING_OPERATOR >
		#include "test_0.operator.hpp"
		#undef TESTING_OPERATOR
	} );
	f.test_case( "Equality test bool", []
	{
		// rvalue-bool type on equality test is not allowed.
		// It is to prevent mistakes that can be caused by precedence.
		//
		// Because operator>= has higher precedence,
		// "logic( 0 ) == 0 >= 0" is same to "logic( 0 ) == true".
		//
		// The intention would be "( logic( 0 ) == 0 ) >= 0",
		// which should result in true because "0 == 0" and "0 >= 0".
		// Note that the second zero and 3rd zero are not compared.
		//
		// But due to the operator precedence, what actually happens is
		// "logic( 0 ) == true",
		// which results in false after type-casting 0 to bool.

#if defined( COMPILE_FAIL_TEST ) && COMPILE_FAIL_TEST == 1
		test( logic( 0 ) == false, "wouldn't compile to prevent mistake." );
#endif
#if defined( COMPILE_FAIL_TEST ) && COMPILE_FAIL_TEST == 2
		test( logic( 0 ) == 0 >= 0, "mistake that needs to be prevented." );
#endif
#if defined( COMPILE_FAIL_TEST ) && COMPILE_FAIL_TEST == 3
		bool lvalue = false;
		test( logic( 0 ) == lvalue, "L-Value" );
#endif
#if defined( COMPILE_FAIL_TEST ) && COMPILE_FAIL_TEST == 4
		const bool const_lvalue = false;
		test( logic( 0 ) == const_lvalue, "L-Value const" );
#endif

		test_true( 0 == false, "workaround #1" );
		test( ( logic( 0 ) == 0 ) >= 0, "workaround #2" );
	} );
	f.test_case( "Message test", []
	{
		test_true( true, "Message to show when failed" );
		test_true( true, "Message", " to", " show", " when", " failed" );
		test( logic( 3 ) != 4.f, "int( ", 3, " ) != ", 4.f );
	} );
	f.test_case( "Boolean test with Macro", []
	{
		TEST_TRUE( true );
		TEST_TRUE( true );
		TEST_TRUE( 2 <= 3 );
		TEST_FALSE( false, "Message when succeed." );
		TEST_TRUE( true, "Message when failed." );
	} );
	f.test_case_must_fail( "Boolean test with Macro", []
	{
		TEST_TRUE( 2 >= 3 );
	} );
	f.test_case( "Unconditional success with Macro", []
	{
		TEST_SUCCESS();
	} );
	f.test_case_must_fail( "Unconditional fail with Macro", []
	{
		TEST_FAIL();
	} );
	f.test_case( "bool type is not allowed in logic_stream", []
	{
#if defined( COMPILE_FAIL_TEST ) && COMPILE_FAIL_TEST == 5
		test( logic( true ), "R-Value" );
#endif

#if defined( COMPILE_FAIL_TEST ) && COMPILE_FAIL_TEST == 6
		bool lvalue = true;
		test( logic( lvalue ), "L-Value" );
#endif

#if defined( COMPILE_FAIL_TEST ) && COMPILE_FAIL_TEST == 7
		const bool const_lvalue = true;
		test( logic( const_lvalue ), "L-Value const" );
#endif
	} );
	return f.failed_count();
}
