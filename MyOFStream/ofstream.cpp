#include "ofstream.h"

stf::MyOFStream::MyOFStream() : 
	name(" "), flag("w"), intTypeOut(stf::dec)
{
}

stf::MyOFStream::MyOFStream(const std::string &_name, strString _flag) : intTypeOut(stf::dec)
{
	open(_name, _flag);
}

stf::MyOFStream::~MyOFStream()
{
	if (this->file) close();
}

void stf::MyOFStream::open(const std::string &_name, strString _flag)
{
	name = _name;
	flag = _flag(flag);

	if (!this->file) {
		file = fopen(name.c_str(), flag.c_str());
	}
}

void stf::MyOFStream::write(std::string _output)
{
	if (this->file)
		fprintf(file, "%s", _output.c_str());
}

void stf::MyOFStream::flush()
{
	fflush(this->file);
}

void stf::MyOFStream::close()
{
	if (this->file)
	{
		fclose(this->file);
		this->file = nullptr;
	}
}

stf::MyOFStream::operator bool()
{
	return this->file;
}

stf::MyOFStream & stf::MyOFStream::operator<<(const std::string &_output)
{
	write(_output);

	return *this;
}

stf::MyOFStream & stf::MyOFStream::operator<<(const char *_output)
{
	write(_output);

	return *this;
}

stf::MyOFStream & stf::MyOFStream::operator<<(char _output)
{
	char *buff = new char[2];
	buff[0] = _output;
	buff[1] = 0;
	write(buff);

	return *this;
}

void stf::MyOFStream::bin(int _output)
{
	std::string bin;

	while (_output != 0) {
		bin += char((_output & 0x01) + '0');
		_output >>= 1;
	}

	write(bin);
}

stf::MyOFStream & stf::MyOFStream::operator<<(int _output)
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

stf::MyOFStream & stf::MyOFStream::operator<<(double _output)
{
	char *buffer = new char[25];

	sprintf(buffer, "%f", _output);

	write(buffer);
	delete[] buffer;

	return *this;
}

stf::MyOFStream & stf::MyOFStream::operator<<(bool _output)
{
	_output ? write("1") : write("0");

	return *this;
}

stf::MyOFStream & stf::MyOFStream::operator<<(const manip &_m)
{
	if (this->file)
		return (*_m) (*this);
}

stf::MyOFStream & stf::MyOFStream::operator<<(const strString &_s)
{
	intTypeOut = _s;
	return *this;
}

stf::MyOFStream & stf::MyOFStream::setf(strString _s)
{
	intTypeOut = _s;
	return *this;
}

stf::MyOFStream & stf::MyOFStream::unsetf()
{
	intTypeOut = stf::dec;

	return *this;
}

std::string & stf::rw(std::string & _s)
{
	_s = "w";
	return _s;
}

std::string & stf::add(std::string & _s)
{
	_s = "a";
	return _s;
}

stf::MyOFStream &stf::endl(MyOFStream &_s)
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