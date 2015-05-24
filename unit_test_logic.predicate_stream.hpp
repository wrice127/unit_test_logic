template< typename... >
struct storage;

template< typename Type >
struct storage< Type >
{
	Type value;
	storage( Type v ) : value( v )
	{}
};

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


template< typename... Args >
class predicate_stream
{
	const bool out_;
	const storage< Args... > args_;
public:
	predicate_stream( bool out, Args&&... args )
		: out_( out ), args_( args... )
	{}
	bool out() const { return out_; }
	string args() const
	{
		stringstream ss;
		storage_msg_r( ss, args_ );
		return ss.str();
	}
};
