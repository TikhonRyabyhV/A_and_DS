#pragma once
#include <stdio.h>

#define void_func_breaker(condition)			\
	if( !( condition ) ) {				\
		printf( "Error in /%s/" 		\
		"  ( %s in %s in %d line ).\n",		\
		#condition, __FILE__,			\
		__func__, __LINE__ );			\
		return;					\
	}

#define func_breaker(condition)			\
	if( !( condition ) ) {			\
		printf( "Error in /%s/" 	\
		"  ( %s in %s in %d line ).\n",	\
		#condition, __FILE__,		\
		__func__, __LINE__ );		\
		return 1;			\
	}

#define program_breaker(condition)			\
	if( !( condition ) ) {				\
		printf( "Error in /%s/" 		\
		"  ( %s in %s in %d line ).\n",		\
		#condition, __FILE__, 			\
		__func__, __LINE__ );			\
		abort();				\
	}
