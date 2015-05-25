// unit_test_logic.logic_stream.hpp written by JaeHyuk Kwak
template< typename Type >
void logic_stream_static_type_check()
{
	static_assert( !is_same< Type, bool >::value, "Type, 'bool', is not allowed on logic_stream." );
	static_assert( !is_same< Type, bool & >::value, "Type, 'bool&', is not allowed on logic_stream." );
	static_assert( !is_same< Type, const bool & >::value, "Type, 'const bool&', is not allowed on logic_stream." );
}

template< typename In >
class logic_stream
{
	const bool out_; // testing result so far
	const In in_; // initial value we are testing
	const string msg_;
public:
	logic_stream( bool out, const In &in, string msg )
		: out_( out ), in_( in ), msg_( msg )
	{
		logic_stream_static_type_check< In >();
	}
	bool out() const { return out_; }
	const In in() const { return in_; }
	string msg() const { return msg_; }
};
