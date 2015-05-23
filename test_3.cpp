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
		( predicate( is_same_int, 3, 3 ) );
		//test( predicate( is_same_int, 3, 3 ) );
	} );

	f.test_case_must_fail( "Predicate test; simple", []
	{
		//test( predicate( is_same_int, 3, 4 ) );
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
