//----------------------------------------------------------------------------------------
#ifndef aviexceptionH
#define aviexceptionH aviexceptionH
//----------------------------------------------------------------------------------------
#include <string>

//----------------------------------------------------------------------------------------
class AVIException
//----------------------------------------------------------------------------------------
{
public:
	virtual const char* what() const = 0;
};

//----------------------------------------------------------------------------------------
class AEUnsupportedCodec : public AVIException
//----------------------------------------------------------------------------------------
{
public:
	const char* what() const { return "Unsupported codec"; }
};

//----------------------------------------------------------------------------------------
class AVIWrapperException : public AVIException
//----------------------------------------------------------------------------------------
{
	std::string m_errorString;
public:
	AVIWrapperException( const char* pError ) : m_errorString(pError) {}
	const char* what() const { return m_errorString.c_str(); }
};

#endif // aviexceptionH