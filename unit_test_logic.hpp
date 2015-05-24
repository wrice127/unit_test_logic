// unit_test_logic.hpp written by Jae Hyuk Kwak
namespace unit_test_logic_ns
{
	using namespace std;

	namespace implementation_ns
	{
		#include "unit_test_logic.test_exception.hpp"
		#include "unit_test_logic.logic_stream.hpp"
		#include "unit_test_logic.predicate_stream.hpp"
		#include "unit_test_logic.test.hpp"
	}
	using namespace implementation_ns;

	#include "unit_test_logic.fixture.hpp"

	template< typename Type >
	const logic_stream< Type > logic( Type &&in )
	{
		logic_stream_static_type_check< Type >();
		return logic_stream< Type >( forward< Type >( in ), true, "" );
	}

	// This macro include could be replaced with template base function.
	// But it wasn't any easier to read.
	#define OPERATOR_SYMBOL ==
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL !=
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL >
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL >=
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL <
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL <=
	#include "unit_test_logic.compare.hpp"
	#undef OPERATOR_SYMBOL

	template< typename Type, typename... Args >
	void test( const logic_stream< Type > &&in, Args&&... args )
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
		throw test_exception_fail( "Expected expection is not thrown" );
	}

	template< typename... Args >
	void test_ignore_exception( function< void() > func )
	{
		using namespace implementation_ns;
		test_ignore_exception_r< Args... >( func );
	}

	template< typename... Args >
	void test_true( bool in, Args... args )
	{
		#define TEST_BOOL_VALUE true
		#include "unit_test_logic.bool.hpp"
		#undef TEST_BOOL_VALUE
	}

	template< typename... Args >
	void test_false( bool in, Args... args )
	{
		#define TEST_BOOL_VALUE false
		#include "unit_test_logic.bool.hpp"
		#undef TEST_BOOL_VALUE
	}

	template< typename... Args >
	void test_success( Args... args )
	{
		#define TEST_UNCONDITION_VALUE success
		#include "unit_test_logic.uncondition.hpp"
		#undef TEST_UNCONDITION_VALUE
	}

	template< typename... Args >
	void test_fail( Args... args )
	{
		#define TEST_UNCONDITION_VALUE fail
		#include "unit_test_logic.uncondition.hpp"
		#undef TEST_UNCONDITION_VALUE
	}

	string lowercase_string( string in )
	{
		transform( in.begin(), in.end(), in.begin(), (int(*)(int)) tolower );
		return in;
	}
	
	// perfect forwarding
	template< typename Function, typename... Args >
	predicate_stream< Args... > predicate( Function&& f, Args&&... args )
	{
		using result_function = typename result_of< Function( Args... ) >::type;
		static_assert( is_same< bool, result_function >::value, "Return type must be bool" );
		const bool out = f( args... );
		return predicate_stream< Args... >( out, forward< Args >( args )... );
	}

	template< typename... Types, typename... Args >
	void test_true( predicate_stream< Types... > &&in, Args&&... args )
	{
		test_predicate( true, move( in ), forward< Args >( args )... );
	}

	template< typename... Types, typename... Args >
	void test_false( predicate_stream< Types... > &&in, Args&&... args )
	{
		test_predicate( false, move( in ), forward< Args >( args )... );
	}
}

#include "unit_test_logic.macro.hpp"
