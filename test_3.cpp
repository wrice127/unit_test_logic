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
		//test_false( predicate( is_same_int, 0, 1 ) );
	} );

	f.test_case_must_fail( "Predicate test; simple", []
	{
		TEST_TRUE( predicate( is_same_int, 0, 1 ) );
	} );

	f.test_case( "call test; simple", []
	{
		//test( call( max_int, 3, 4 ) == 4 );
	} );

	f.test_case_must_fail( "call test; simple", []
	{
		//test( call( max_int, 3, 4 ) == 3 );
	} );

	return f.failed_count();
}
