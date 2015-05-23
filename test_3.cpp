// test_0.cpp written by JaeHyuk Kwak
#include "stdafx.h"
#include "unit_test_logic.hpp"
using namespace unit_test_logic_ns;
int main( int, const char ** )
{
	fixture f;
	f.test_case( "Predicate test; simple", []
	{
		//test( predicate( ) );
	} );
	return f.failed_count();
}
