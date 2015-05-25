// unit_test_logic.compare.hpp written by Jae Hyuk Kwak
template< typename LHS, typename RHS, typename Compare, typename... Args >
LHS operator_common( LHS lhs, RHS &&rhs, Compare compare, const char *symbol, Args... args )
{
	static_assert( !is_same< bool, RHS >::value, "bool-type is not allowed." );
	static_assert( !is_same< bool&, RHS >::value, "bool-type is not allowed." );
	static_assert( !is_same< const bool&, RHS >::value, "bool-type is not allowed." );

	logic_stream_static_type_check< LHS >();
	auto in = lhs.in();
	if ( false == lhs.out() ) return lhs; // already false
	if ( compare( in, rhs ) ) return lhs;

	stringstream ss;
	ss << "Given '" << in << "' is not '" << symbol <<  "' to '" << rhs << "' as expected.";
	return LHS( false, in, ss.str(), args... );
}
