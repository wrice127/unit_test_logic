// unit_test_logic.logic_stream.hpp written by JaeHyuk Kwak
template< typename Type >
void logic_stream_static_type_check()
{
	static_assert( !is_same< Type, bool >::value, "Type, 'bool', is not allowed on logic_stream." );
	static_assert( !is_same< Type, bool & >::value, "Type, 'bool&', is not allowed on logic_stream." );
	static_assert( !is_same< Type, const bool & >::value, "Type, 'const bool&', is not allowed on logic_stream." );
}

template< typename Type >
class logic_stream
{
	const Type in_; // initial value we are testing
	const bool out_; // testing result so far
	const string msg_;
public:
	logic_stream( Type &&in, bool out, string msg )
		: in_( in ), out_( out ), msg_( msg )
	{
		logic_stream_static_type_check< Type >();
	}
	const Type in() const { return in_; }
	bool out() const { return out_; }
	string msg() const { return msg_; }
};
