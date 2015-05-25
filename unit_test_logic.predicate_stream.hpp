// unit_test_logic.predicate_stream.hpp written by JaeHyuk Kwak
template< typename... >
struct storage;

template<>
struct storage<>
{};

template< typename Type, typename... Rest >
struct storage< Type, Rest... > : storage< Rest... >
{
	Type value;
	storage( Type v, Rest... r )
		: storage< Rest... >( r... ), value( v )
	{}
};


template< typename Type >
void storage_msg_r( stringstream &ss, storage< Type > s )
{
	ss << s.value;
}

template< typename Type1, typename Type2, typename... Rest >
void storage_msg_r( stringstream &ss, storage< Type1, Type2, Rest...> s )
{
	ss << s.storage< Type1, Type2, Rest... >::value;
	ss << ", ";
	ss << s.storage< Type2, Rest... >::value;
}


template< typename Arg >
class predicate_stream
{
	const bool out_;
	const Arg arg_;
public:
	predicate_stream( bool out, Arg &arg )
		: out_( out ), arg_( arg )
	{}
	bool out() const { return out_; }
	Arg arg() const { return arg_; }
};


template< typename In, typename Arg >
class function_logic_stream
{
	const logic_stream< In > ls_;
	const Arg arg_;
public:
	function_logic_stream( bool out, const In &in, string msg, Arg &arg )
		: ls_( out, in, msg ), arg_( arg )
	{}
	bool out() const { return ls_.out(); }
	In in() const { return ls_.in(); }
	string msg() const { return ls_.msg(); }
	Arg arg() const { return arg_; }
};
