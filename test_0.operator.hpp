// test_0.operator.cpp written by JaeHyuk Kwak
static_assert( !is_const< decltype( lvalue_inlogic ) >::value, "lvalue_inlogic must not be const type." );
static_assert( !is_const< decltype( lvalue ) >::value, "lvalue must not be const type." );

const decltype( lvalue_inlogic ) const_lvalue_inlogic = lvalue_inlogic;
const decltype( lvalue ) const_lvalue = lvalue;

// R-value in logic
test( logic( 0 ) TESTING_OPERATOR lvalue );
test( logic( 0 ) TESTING_OPERATOR const_lvalue );

// L-value in logic
test( logic( lvalue_inlogic ) TESTING_OPERATOR 0 );
test( logic( lvalue_inlogic ) TESTING_OPERATOR lvalue );
test( logic( lvalue_inlogic ) TESTING_OPERATOR const_lvalue );

// Const L-value in logic
test( logic( const_lvalue_inlogic ) TESTING_OPERATOR 0 );
test( logic( const_lvalue_inlogic ) TESTING_OPERATOR lvalue );
test( logic( const_lvalue_inlogic ) TESTING_OPERATOR const_lvalue );
