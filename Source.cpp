#include <iostream>
#include <string>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

int sumInt( int a, int b ){
	int result { 0 };
	for ( int i = a; i <= b; ++i ) {
		result += i;
	}
	return result;
}

int sumCube( int a, int b ){
	int result { 0 };
	for ( int i = a; i <= b; ++i ) {
		result += i * i * i;
	}
	return result;
}

double sumPi( int a, int b ){
	double result = 0;
	for ( int i = 1; i <= b; i += 4 ) {
		result += 1 / ( (double)(i) * (double)( i + 2 ) );
	}
	return result;
}


//advanced abstraction. Method 1
template < class T >
T sumGeneric( T a, T b, const function< int( int ) >& func,  const function< void( int& ) >& next ){
	T result( 0 );
	for ( T i = a; i <= b; next( i ) ) {
		result += func( i );
	}
	return result;
}



//advanced abstraction. Method 2
template < class T, class F, class G >
T sumGeneric( T a, T b, F func, G next ){
	T result( 0 );
	for ( T i = a; i <= b; next( i ) ) {
		result += func( i ); 
	}
	return result;
}

template < class T >
class Self{
public:
	T operator()( T x ){ return x;  }
};

template < class T >
class Cube{
public:
	T operator()( T x ){ return x*x*x; }
};

template< class T >
class MyFunc{
public:
	T operator()( T x ){
		return 1 / ( x * ( x + 2 ) );
	}
};

template < class T >
class Inc{
public:
	void operator()( T& x ){ ++x; }
};

template < class T >
class Inc4{
public:
	void operator()( T& x ){ x += 4; }
};


int main(){



	// Method 1
	auto self = []( int i ) -> int { return i; };
	auto inc = []( int& i ) -> void {  ++i; };
	auto cube = []( int i ) -> int { return i * i * i; };

	cout << "----------------------Method 1--------------------------" << endl;
	cout << "Normal Cal:" << endl;
	cout << "sumInt( 1, 50 ):" << sumInt( 1, 50 ) << " sumCube( 1, 50 ):" << sumCube( 1, 50 );

	cout << endl << "High Order Function:" << endl;
	cout << "sumInt( 1, 50 ):" << sumGeneric( 1, 50, self, inc )
		<< " sumCube( 1, 50 ):" << sumGeneric( 1, 50, cube, inc );


	// Method 2
	cout << endl << "----------------------Method 2--------------------------" << endl;
	cout << "Normal Cal:" << endl;
	cout << "sumInt( 1, 50 ):" << sumInt( 1, 50 ) << " sumCube( 1, 50 ):" << sumCube( 1, 50 ) << " sumPi( 1, 50 ):" << sumPi( 1, 50 );

	cout << endl << "High Order Function:" << endl;
	cout << "sumInt( 1, 50 ):" << sumGeneric( 1, 50, Self<int>(), Inc<int>() )
		<< " sumCube( 1, 50 ):" << sumGeneric( 1, 50, Cube<int>(), Inc<int>() )
		<< " sumPi( 1, 50 ):" << sumGeneric( (double)1, (double)50, MyFunc<double>(), Inc4<double>() );

	system( "pause" );
}