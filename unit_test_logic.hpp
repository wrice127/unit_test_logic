// unit_test_logic.hpp written by Jae Hyuk Kwak
namespace unit_test_logic_ns
{
	using namespace std;

	namespace implementation_ns
	{
		#include "unit_test_logic.exception.hpp"
		#include "unit_test_logic.logic_stream.hpp"
		#include "unit_test_logic.predicate_stream.hpp"
		#include "unit_test_logic.test.hpp"
		#include "unit_test_logic.compare.hpp"
	}
	using namespace implementation_ns;

	#include "unit_test_logic.fixture.hpp"

	template< typename Type >
	const logic_stream< Type > logic( Type &&in )
	{
		logic_stream_static_type_check< Type >();
		return logic_stream< Type >( in, true, "" ); // don't forward
	}

	#define STRINGFICATION( S ) #S
	#define OPERATOR_SYMBOL( SYMBOL ) operator_common( lhs, forward< RHS >( rhs ), []( LHS lhs, RHS rhs ) { return lhs SYMBOL rhs; }, STRINGFICATION( SYMBOL ) )
	template< typename LHS, typename RHS >
	logic_stream< LHS > operator==( logic_stream< LHS > lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( == );
	}

	template< typename LHS, typename RHS >
	logic_stream< LHS > operator!=( logic_stream< LHS > lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( != );
	}

	template< typename LHS, typename RHS >
	logic_stream< LHS > operator>( logic_stream< LHS > lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( > );
	}

	template< typename LHS, typename RHS >
	logic_stream< LHS > operator>=( logic_stream< LHS > lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( >= );
	}

	template< typename LHS, typename RHS >
	logic_stream< LHS > operator<( logic_stream< LHS > lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( < );
	}

	template< typename LHS, typename RHS >
	logic_stream< LHS > operator<=( logic_stream< LHS > lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( <= );
	}
	#undef OPERATOR_SYMBOL
	#undef STRINGFICATION

	template< typename Type, typename... Args >
	void test( const logic_stream< Type > in, Args&&... args )
	{
		if ( in.out() ) return;

		if ( constexpr size_t nArgs = sizeof...( Args ) )
		{
			stringstream ss;
			using namespace implementation_ns;
			msg_r( ss, args... );
			throw test_exception_fail( ss.str() + ": " + in.msg() );
		} else throw test_exception_fail( in.msg() );
	}

	template< typename... Args >
	void test_must_throw_exception( function< void() > func )
	{
		using namespace implementation_ns;
		if ( test_must_throw_exception_r< Args... >( func ) )
			return;
		throw test_exception_fail( "Expected exception is not thrown" );
	}

	template< typename... Args >
	void test_ignore_exception( function< void() > func )
	{
		using namespace implementation_ns;
		test_ignore_exception_r< Args... >( func );
	}

	template< typename... Args >
	void test_true( bool in, Args&&... args )
	{
		test_boolean( true, in, args... );
	}

	template< typename... Args >
	void test_false( bool in, Args&&... args )
	{
		test_boolean( false, in, args... );
	}

	template< typename... Args >
	void test_success( Args&&... args )
	{
		test_unconditional< test_exception_success >( true, forward< Args >( args )... );
	}

	template< typename... Args >
	void test_fail( Args&&... args )
	{
		test_unconditional< test_exception_fail >( false, forward< Args >( args )... );
	}

	string lowercase_string( string in )
	{
		transform( in.begin(), in.end(), in.begin(), (int(*)(int)) tolower );
		return in;
	}
	
	template< typename Function, typename... Args >
	predicate_stream< Args... > predicate( Function f, Args&&... args )
	{
		using result_function = typename result_of< Function( Args&&... ) >::type;
		static_assert( is_same< bool, result_function >::value, "Return type must be bool" );
		const bool out = f( forward< Args >( args )... ); // perfect forwarding
		return predicate_stream< Args... >( out, args... ); // don't forward
	}

	template< typename... Types, typename... Args >
	void test_true( const predicate_stream< Types... > in, Args&&... args )
	{
		test_predicate( true, in, forward< Args >( args )... );
	}

	template< typename... Types, typename... Args >
	void test_false( const predicate_stream< Types... > in, Args&&... args )
	{
		test_predicate( false, in, forward< Args >( args )... );
	}
}

#include "unit_test_logic.macro.hpp"
