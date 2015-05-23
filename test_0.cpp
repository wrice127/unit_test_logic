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
		test( ( logic( 0 ) != 1 ) != 2, "0 != 1 && 0 != 2" );
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
	return f.failed_count();
}
