// unit_test_logic.hpp written by Jae Hyuk Kwak
namespace unit_test_logic_ns
{
	using namespace std;

	namespace implementation_ns
	{
		#include "unit_test_logic.exception.hpp"
		#include "unit_test_logic.logic_stream.hpp"
		#include "unit_test_logic.predicate_stream.hpp"
		#include "unit_test_logic.logic_compare.hpp"
		#include "unit_test_logic.test.hpp"
		#include "unit_test_logic.value_range.hpp"
	}
	using namespace implementation_ns;

	#include "unit_test_logic.fixture.hpp"

	template< typename Type >
	const logic_stream< Type > logic( Type &&in )
	{
		return logic_stream< Type >( true, in, "" ); // don't forward
	}

	template< typename Type, typename... Args >
	void test( const logic_stream< Type > &in, Args&&... args )
	{
		test_logic( in, args... );
	}

	template< typename LHS, typename Arg, typename... Args >
	void test( const function_logic_stream< LHS, Arg > &in, Args&&... args )
	{
		stringstream ss;
		if ( constexpr size_t nArgs = sizeof...( Args ) )
		{
			using namespace implementation_ns;
			msg_r( ss, args... );
			ss << ": ";
		}
		ss << "arguments( ";
		storage_msg_r( ss, in.arg() );
		ss << " )";
		test_logic( in, ss.str() );
	}

	template< typename... Args >
	void test_true( bool in, Args&&... args )
	{
		test_boolean< true >( in, args... );
	}

	template< typename... Args >
	void test_false( bool in, Args&&... args )
	{
		test_boolean< false >( in, args... );
	}

	template< typename... Args >
	void test_success( Args&&... args )
	{
		test_unconditional< true, test_exception_success >( forward< Args >( args )... );
	}

	template< typename... Args >
	void test_fail( Args&&... args )
	{
		test_unconditional< false, test_exception_fail >( forward< Args >( args )... );
	}

	template< typename Arg, typename... Args >
	void test_true( const predicate_stream< Arg > &in, Args&&... args )
	{
		test_predicate< true >( in, forward< Args >( args )... );
	}

	template< typename Arg, typename... Args >
	void test_false( const predicate_stream< Arg > &in, Args&&... args )
	{
		test_predicate< false >( in, forward< Args >( args )... );
	}

	string lowercase_string( string in )
	{
		transform( in.begin(), in.end(), in.begin(), (int(*)(int)) tolower );
		return in;
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


	template< typename Function, typename... Args >
	const predicate_stream< storage< Args... > > predicate( Function&& f, Args&&... args )
	{
		using return_type = typename result_of< Function( Args&&... ) >::type;
		static_assert( is_same< bool, return_type >::value, "Return type must be bool" );
		const bool out = f( forward< Args >( args )... ); // perfect forwarding
		storage< Args... > arg( args... ); // don't forward
		return predicate_stream< storage< Args... > >( out, arg );
	}

	template< typename Function, typename... Args >
	const function_logic_stream< typename result_of< Function( Args&&... ) >::type, storage< Args... > > function_logic( Function&& f, Args&&... args )
	{
		using return_type = typename result_of< Function( Args&&... ) >::type;
		static_assert( !is_same< bool, return_type >::value, "Return type should not be bool" );
		const return_type in = f( forward< Args >( args )... ); // perfect forwarding
		storage< Args... > arg( args... ); // don't forward
		return function_logic_stream< return_type, storage< Args... > >( true, in, "", arg ); // don't forward
	}

	template< typename Object, typename Function, typename... Args >
	const function_logic_stream< typename result_of< Function( Object, Args&&... ) >::type, storage< Args... > > member_logic( Object *obj, Function&& f, Args&&... args )
	{
		using return_type = typename result_of< Function( Object, Args&&... ) >::type;
		static_assert( !is_same< bool, return_type >::value, "Return type should not be bool" );
		const return_type in = (obj->*f)( forward< Args >( args )... ); // perfect forwarding
		storage< Args... > arg( args... ); // don't forward
		return function_logic_stream< return_type, storage< Args... > >( true, in, "", arg ); // don't forward
	}

	#define STRINGFICATION( S )			#S
	#define OPERATOR_SYMBOL( SYMBOL )	operator_common( lhs, forward< RHS >( rhs ), []( const LHS &lhs, const RHS &rhs ) { return lhs SYMBOL rhs; }, STRINGFICATION( SYMBOL ) )
	template< typename LHS, typename RHS >
	const logic_stream< LHS > operator==( const logic_stream< LHS > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( == );
	}

	template< typename LHS, typename RHS >
	const logic_stream< LHS > operator!=( const logic_stream< LHS > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( != );
	}

	template< typename LHS, typename RHS >
	const logic_stream< LHS > operator>( const logic_stream< LHS > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( > );
	}

	template< typename LHS, typename RHS >
	const logic_stream< LHS > operator>=( const logic_stream< LHS > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( >= );
	}

	template< typename LHS, typename RHS >
	const logic_stream< LHS > operator<( const logic_stream< LHS > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( < );
	}

	template< typename LHS, typename RHS >
	const logic_stream< LHS > operator<=( const logic_stream< LHS > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( <= );
	}
	#undef OPERATOR_SYMBOL

	#define OPERATOR_SYMBOL( SYMBOL )	operator_common( lhs, forward< RHS >( rhs ), []( const LHS &lhs, const RHS &rhs ) { return lhs SYMBOL rhs; }, STRINGFICATION( SYMBOL ), lhs.arg() )
	template< typename LHS, typename Arg, typename RHS >
	const function_logic_stream< LHS, Arg > operator==( const function_logic_stream< LHS, Arg > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( == );
	}

	template< typename LHS, typename Arg, typename RHS >
	const function_logic_stream< LHS, Arg > operator!=( const function_logic_stream< LHS, Arg > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( != );
	}

	template< typename LHS, typename Arg, typename RHS >
	const function_logic_stream< LHS, Arg > operator>( const function_logic_stream< LHS, Arg > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( > );
	}

	template< typename LHS, typename Arg, typename RHS >
	const function_logic_stream< LHS, Arg > operator>=( const function_logic_stream< LHS, Arg > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( >= );
	}

	template< typename LHS, typename Arg, typename RHS >
	const function_logic_stream< LHS, Arg > operator<( const function_logic_stream< LHS, Arg > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( < );
	}

	template< typename LHS, typename Arg, typename RHS >
	const function_logic_stream< LHS, Arg > operator<=( const function_logic_stream< LHS, Arg > &lhs, RHS &&rhs )
	{
		return OPERATOR_SYMBOL( <= );
	}
	#undef OPERATOR_SYMBOL
	#undef STRINGFICATION

	value_error< double > operator"" _value_error( long double e )
	{
		return value_error< double >( e );
	}

	value_range< double > operator+( double v, value_error< double > e )
	{
		const double delta = e.error;
		return value_range< double >( v - delta, v + delta );
	}

	value_range< double > operator*( double v, value_error< double > e )
	{
		const double delta = v * e.error;
		return value_range< double >( v - delta, v + delta );
	}

	bool operator==( double lhs, value_range< double > rhs )
	{
		return lhs >= rhs.value_low && lhs <= rhs.value_high;
	}

	bool operator!=( double lhs, value_range< double > rhs )
	{
		return !( lhs == rhs );
	}

	template< typename Type >
	ostream& operator<<( ostream& os, const value_range< Type > r )
	{
		return os << "[ " << r.value_low << ", " << r.value_high << " ]";
	}
}

#include "unit_test_logic.macro.hpp"
