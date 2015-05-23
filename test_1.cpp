// test_1.cpp written by JaeHyuk Kwak
#include "stdafx.h"
#include "unit_test_logic.hpp"
using namespace unit_test_logic_ns;
int main( int, const char ** )
{
	fixture f;
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
	f.test_case( "String test; ignore-case", []
	{
		const char *A = "A";
		const char *a = "a";
		test( logic( lowercase_string( A ) ) == lowercase_string( a ) );
	} );
	return f.failed_count();
}
