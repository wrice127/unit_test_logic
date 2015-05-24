// unit_test_logic.compare.hpp written by Jae Hyuk Kwak
template< typename LHS, typename RHS, typename Compare >
logic_stream< LHS > operator_common( logic_stream< LHS > lhs, RHS &&rhs, Compare compare, const char *symbol )
{
	static_assert( !is_same< bool, RHS >::value, "bool-type is not allowed." );
	static_assert( !is_same< bool&, RHS >::value, "bool-type is not allowed." );
	static_assert( !is_same< const bool&, RHS >::value, "bool-type is not allowed." );

	logic_stream_static_type_check< LHS >();
	LHS in = lhs.in();
	if ( false == lhs.out() ) return lhs; // already false
	if ( compare( in, rhs ) ) return lhs;

	stringstream ss;
	ss << "Given '" << in << "' is not '" << symbol <<  "' to '" << rhs << "'";
	return logic_stream< LHS >( in, false, ss.str() );
}
