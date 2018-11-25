// 不可拷贝类基类


#ifndef _X_NONCOPYABLE_H_
#define _X_NONCOPYABLE_H_

namespace xbase {

////////////////////////////////////////////////////////////////////////////////
// XNonCopyable
////////////////////////////////////////////////////////////////////////////////
class XNonCopyable
{
protected:
	XNonCopyable() {}
	~XNonCopyable() {}

private:
	XNonCopyable(const XNonCopyable&);
	XNonCopyable& operator=(const XNonCopyable&);
};

}//namespace xbase;

using namespace xbase;

#endif//_X_NONCOPYABLE_H_
