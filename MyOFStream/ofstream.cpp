#include "ofstream.h"

MyOFStream::MyOFStream() : name(" "), flag("w"), intTypeOut(stf::dec)
{
}

MyOFStream::MyOFStream(std::string _name, strString _flag) : intTypeOut(stf::dec)
{
	open(_name, _flag);
}

MyOFStream::~MyOFStream()
{
	if (this->file) close();
}

void MyOFStream::open(std::string _name, strString _flag)
{
	name = _name;
	flag = _flag(flag);

	if (!this->file) {
		file = fopen(name.c_str(), flag.c_str());
	}
}

void MyOFStream::write(std::string _output)
{
	if (this->file)
		fprintf(file, "%s", _output.c_str());
}

void MyOFStream::flush()
{
	fflush(file);
}

void MyOFStream::close()
{
	if (file)
	{
		fclose(file);
		this->file = nullptr;
	}
}

MyOFStream::operator bool()
{
	return this->file;
}

MyOFStream & MyOFStream::operator<<(std::string _output)
{
	write(_output);

	return *this;
}

MyOFStream & MyOFStream::operator<<(const char *_output)
{
	write(_output);

	return *this;
}

MyOFStream & MyOFStream::operator<<(char _output)
{
	std::string buff;
	buff = _output;
	write(buff);

	return *this;
}

void MyOFStream::bin(int _output)
{
	std::string bin;

	while (_output != 0) {
		bin += char((_output & 0x01) + '0');
		_output >>= 1;
	}

	write(bin);
}

MyOFStream &MyOFStream::operator<<(int _output)
{
	char *buffer = new char[25];

	std::string typeOut;
	intTypeOut(typeOut);

	if (typeOut == "%b") bin(_output);

	else {
		sprintf(buffer, typeOut.c_str(), _output);
		write(buffer);
	}

	delete[] buffer;

	return *this;
}

MyOFStream &MyOFStream::operator<<(double _output)
{
	char *buffer = new char[25];

	sprintf(buffer, "%f", _output);

	write(buffer);
	delete[] buffer;

	return *this;
}

MyOFStream & MyOFStream::operator<<(bool _output)
{
	_output ? write("1") : write("0");

	return *this;
}

MyOFStream &MyOFStream::operator<<(manip _m)
{
	if (file)
		return (*_m) (*this);
}

MyOFStream &MyOFStream::operator<<(strString _s)
{
	intTypeOut = _s;
	return *this;
}

MyOFStream &MyOFStream::setf(strString _s)
{
	intTypeOut = _s;
	return *this;
}

MyOFStream &MyOFStream::unsetf()
{
	intTypeOut = stf::dec;

	return *this;
}

std::string & fof::rw(std::string & _s)
{
	_s = "w";
	return _s;
}

std::string & fof::add(std::string & _s)
{
	_s = "a";
	return _s;
}

MyOFStream &stf::endl(MyOFStream &_s)
{
	_s.write("\n");
	_s.flush();

	return _s;
}

std::string & stf::dec(std::string & _s)
{
	_s = "%i";
	return _s;
}

std::string &stf::oct(std::string &_s)
{
	_s = "%o";
	return _s;
}

std::string &stf::hex(std::string &_s)
{
	_s = "%x";
	return _s;
}

std::string &stf::bin(std::string &_s)
{
	_s = "%b";
	return _s;
}