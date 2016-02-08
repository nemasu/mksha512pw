/*
	Author: nemasu@gmail.com
	License: Public Domain

	Tool to create SHA512 shadow style passwords.
*/

#include <termios.h>
#include <unistd.h>
#include <cstdint>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <linux/random.h>

#define SALT_SIZE 16

using std::stringstream;
using std::cout;
using std::cin;
using std::endl;
using std::string;

const uint8_t SALT_CHARS[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
						 'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
						 '.','/'};

#define SALT_CHARS_LENGTH sizeof(SALT_CHARS)

void
SetTermEcho( bool enable ) {
	termios tty;
    tcgetattr(STDIN_FILENO, &tty);
    if( !enable ) {
        tty.c_lflag &= ~ECHO;
	}
    else {
        tty.c_lflag |= ECHO;
	}

    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

int
main( int argv, char **argc ) {

	stringstream saltStream;
	srand( std::time(0) * getpid() );
	for( uint8_t i = 0; i < SALT_SIZE; ++i ) {
		saltStream << SALT_CHARS[ (std::rand() % SALT_CHARS_LENGTH) ];
	}
	string salt = saltStream.str();

	string passwd, passwd2;
	
	cout << "Password: ";
	SetTermEcho(false);
	cin >> passwd;
	SetTermEcho(true);
	cout << endl;

	cout << "Password again: ";
	SetTermEcho(false);
	cin >> passwd2;
	SetTermEcho(true);
	cout << endl;

	if( passwd != passwd2 ) {
		cout << "Passwords do not match...exiting." << std::endl;
		return -1;
	}

	string key = "$6$" + salt + "$";
	cout << crypt( passwd.c_str(), key.c_str() ) << endl;

	return 0;
}
