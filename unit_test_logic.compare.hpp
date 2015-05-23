// unit_test_logic.compare.hpp written by Jae Hyuk Kwak
#define STRINGFICATION2( s ) #s
#define STRINGFICATION( s ) STRINGFICATION2( s )
template< typename LHS, typename RHS >
const logic_stream< LHS > operator OPERATOR_SYMBOL ( const logic_stream< LHS > &&lhs, RHS &&rhs )
{
	static_assert( !is_same< bool, RHS >::value, "bool-type is not allowed." );
	static_assert( !is_same< bool&, RHS >::value, "bool-type is not allowed." );
	static_assert( !is_same< const bool&, RHS >::value, "bool-type is not allowed." );

	logic_stream_static_type_check< LHS >();
	LHS in = lhs.in();
	if ( false == lhs.out() ) return move( lhs ); // already false
	if ( in OPERATOR_SYMBOL rhs ) return move( lhs ); // evaluate

	stringstream ss;
	ss << "Given '" << in << "' is not '" STRINGFICATION( OPERATOR_SYMBOL ) "' to '" << rhs << "'";
	return logic_stream< LHS >( forward< LHS >( in ), false, ss.str() );
}
#undef STRINGFICATION
#undef STRINGFICATION2
