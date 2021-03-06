#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <string>
#include <stdio.h>

namespace stf
{
	class MyOFStream;

	std::string & rw(std::string  &_s);
	std::string & add(std::string  &_s);
	MyOFStream &endl(MyOFStream &);
	std::string &dec(std::string &);
	std::string &oct(std::string &);
	std::string &hex(std::string &);
	std::string &bin(std::string &);

	class MyOFStream
	{
		typedef MyOFStream & (*manip) (MyOFStream &);
		typedef std::string & (*strString)(std::string&);
		FILE *file;
		std::string name;
		std::string flag;
		strString intTypeOut;

		void write(std::string);
		void bin(int);

		MyOFStream& operator =(const MyOFStream &) = delete;
		MyOFStream(const MyOFStream&) = delete;
	public:
		MyOFStream();
		MyOFStream(const std::string &, strString = &rw);
		~MyOFStream();

		void open(const std::string &, strString = &rw);
		void flush();
		void close();
		operator bool();

		MyOFStream &operator<< (const std::string &);
		MyOFStream &operator<< (const char*);
		MyOFStream &operator<< (char);
		MyOFStream &operator<< (int);
		MyOFStream &operator<< (double);
		MyOFStream &operator<< (bool);
		MyOFStream &operator<< (const manip &);
		MyOFStream &operator<< (const strString &);

		MyOFStream & setf(strString);
		MyOFStream & unsetf();
		friend MyOFStream & stf::endl(MyOFStream &);
	};
}