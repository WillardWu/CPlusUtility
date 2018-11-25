#ifndef _X_DEFINE_H_
#define _X_DEFINE_H_

#if defined(_WIN32) || defined(WIN32) && !defined(__WIN32__)
#define __WIN32__		1	// windows32平台标记
#ifndef _WIN32_WINNT
#define  _WIN32_WINNT 0x0501
#endif
#endif

#if defined(_WIN64) || defined(WIN64) && !defined(__WIN64__)
#define __WIN64__		1	// windows64平台标记
#endif

#if defined(WIN32) || defined(__WIN32__) || defined(__WIN64__) || defined(_WINDOWS)
#define __WINDOWS__		1	// windows平台标记
#endif

#ifndef __WINDOWS__
#ifndef __GNUC__
#define __GNUC__		1	// Unix类平台标记
#endif
#endif

#if defined(_DEBUG) || defined(DEBUG) && !defined(__DEBUG__)
#define __DEBUG__		1	// debug版本标记
#endif

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>
#include <assert.h>
#include <limits.h>
#include <stdarg.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <signal.h>

#include <vector>
#include <string>
#include <list>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

#ifdef __WINDOWS__
#include <io.h>
#include <direct.h>
#include <WinSock2.h>
#include <process.h>
#include <tchar.h>
#include <wtypes.h>
#include <sys/stat.h>
#endif//__WINDOWS__

#ifdef __GNUC__
#include <unistd.h>
#include <stdint.h>			// int64_t, uint64_t
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/statvfs.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/epoll.h>
#include <sys/wait.h>
#include <sys/file.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <pthread.h>
#include <dirent.h>

#include <semaphore.h>

#include <linux/types.h>
#endif//__GNUC__

typedef char				int8;
typedef unsigned char		uint8;
typedef short				int16;
typedef unsigned short		uint16;
typedef int					int32;
typedef unsigned int		uint32;
#ifdef __WINDOWS__
typedef __int64				int64;
typedef unsigned __int64	uint64;
typedef int					socklen_t;
#endif//__WINDOWS__
#ifdef __GNUC__
typedef int64_t				 int64;
typedef uint64_t			 uint64;
typedef int					 HANDLE;
typedef unsigned char		 BYTE;
typedef unsigned long		 DWORD;
typedef unsigned short		 WORD;
typedef int					 BOOL;
typedef int					 SOCKET;
#define TRUE				 (1)
#define FALSE				 (0)
#define INVALID_SOCKET		 (-1)
#define INVALID_HANDLE_VALUE (-1)
#define SOCKET_ERROR		 (-1)
#endif//__GNUC__

#ifdef PATH_MAX
#undef PATH_MAX
#endif//PATH_MAX
#define PATH_MAX    1024
#ifdef MAX_PATH
#undef MAX_PATH
#endif//MAX_PATH
#define MAX_PATH	1024

#ifdef __WINDOWS__
#define X_PATH_SEPARATOR_CHAR	'\\'
#define X_PATH_SEPARATOR_STRING	"\\"
#define snprintf  _snprintf
#define vsnprintf _vsnprintf
#define XAPI	__stdcall
#endif//__WINDOWS__
#ifdef __GNUC__
#define X_PATH_SEPARATOR_CHAR	'/'
#define X_PATH_SEPARATOR_STRING	"/"
#define XAPI
#endif//__GNUC__

#define __X_FUNCTION__  __FUNCTION__
#define __X_LINE__		__LINE__
#define __X_FILE__		__FILE__
#define __X_TIME__		__TIME__
#define __X_DATE__		__DATE__

#undef ASSERT
#define ASSERT(x) \
	do { \
		if (!(x)) { \
			fprintf(stderr, "assertion "#x" failed in %s:%d\n", __X_FILE__, __X_LINE__); \
			abort(); \
		} \
	} while (0)

#if defined(XBASE_EXPORTS)
  #define XBASE_API __declspec(dllexport)
#elif defined(XBASE_IMPORTS)
  #define XBASE_API __declspec(dllimport)
#else
  #define XBASE_API
#endif


#endif //_X_DEFINE_H_

