// test_3.cpp written by JaeHyuk Kwak
#include "stdafx.h"
#include "unit_test_logic.hpp"

bool is_same_int( int lhs, int rhs )
{
	return lhs == rhs;
}

int max_int( int lhs, int rhs )
{
	return lhs > rhs ? lhs : rhs;
}

int main( int, const char ** )
{
	using namespace unit_test_logic_ns;
	fixture f;

	f.test_case( "Predicate test; simple", []
	{
		test_true( predicate( is_same_int, 0, 0 ) );
		test_false( predicate( is_same_int, 0, 1 ) );
#if defined( COMPILE_FAIL_TEST ) && COMPILE_FAIL_TEST == 1
		// return type of function for predicate must be bool
		test_true( predicate( max_int, 0, 0 ) );
#endif
	} );

	f.test_case_must_fail( "Predicate test; simple", []
	{
		int lhs = 0;
		const int rhs = 1;
		TEST_TRUE( predicate( is_same_int, lhs, rhs ) );
	} );

	f.test_case( "function_logic test; simple", []
	{
		test( function_logic( max_int, 3, 4 ) == 4 );
	} );

	f.test_case_must_fail( "function_logic test; simple", []
	{
		test( function_logic( max_int, 3, 4 ) == 3 );
	} );

	return f.failed_count();
}
