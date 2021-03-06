#ifndef _YON_CORE_MATH_H_
#define _YON_CORE_MATH_H_

#include "yonTypes.h"
#include <math.h>
#include <float.h> //For FLT_MAX
#include <limits.h> // For INT_MAX / UINT_MAX

namespace yon{
namespace core{

//舍入误差
const s32 ROUNDING_ERROR_S32 = 0;
const f32 ROUNDING_ERROR_f32 = 0.000001f;
const f64 ROUNDING_ERROR_f64 = 0.00000001;

//32位
#ifdef PI
#undef PI
#endif

//PI相关定义
const f32 PI=3.1415926535897932384626433832795f;
const f64 PI64= 3.1415926535897932384626433832795028841971693993751;
const f32 PI2=PI+PI;
const f32 RECIPROCAL_PI	= 1.0f/PI;
const f32 HALF_PI	= PI*0.5f;

//从角度转为弧度
const f32 DEGTORAD = PI / 180.0f;
//从弧度转为角度
const f32 RADTODEG   = 180.0f / PI;
const f64 RADTODEG64 = 180.0 / PI64;

//! returns abs of two values. Own implementation to get rid of STL (VS6 problems)
template<class T>
inline T abs_(const T& a)
{
	return a <(T)0? -a : a;
}
//! returns linear interpolation of a and b with ratio t
//! \return: a if t==0, b if t==1, and the linear interpolation else
template<class T>
inline T lerp(const T& a, const T& b, const f32 t)
{
	return (T)(a*(1.f-t)) + (b*t);
}

//! returns minimum of two values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& min_(const T& a, const T& b)
{
	return a < b ? a : b;
}

//! returns minimum of three values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& min_(const T& a, const T& b, const T& c)
{
	return a < b ? min_(a, c) : min_(b, c);
}

//! returns maximum of two values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& max_(const T& a, const T& b)
{
	return a < b ? b : a;
}

//! returns maximum of three values. Own implementation to get rid of the STL (VS6 problems)
template<class T>
inline const T& max_(const T& a, const T& b, const T& c)
{
	return a < b ? max_(b, c) : max_(a, c);
}

//! clamps a value between low and high
template <class T>
inline const T clamp(const T& value, const T& low, const T& high)
{
	return min_(max_(value,low), high);
}

inline bool equals(const f64 a, const f64 b, const f64 tolerance = ROUNDING_ERROR_f64)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

// returns if a equals b, taking possible rounding errors into account
inline bool equals(const f32 a, const f32 b, const f32 tolerance = ROUNDING_ERROR_f32)
{
	return (a + tolerance >= b) && (a - tolerance <= b);
}

inline s32 floor32(f32 x)
{
	return (s32) floorf ( x );
}

inline s32 ceil32( f32 x )
{
	//TODO优化
	return (s32) ceilf ( x );
}

inline f32 round_( f32 x )
{
	return floorf( x + 0.5f );
}

inline s32 round32(f32 x)
{
	return (s32) round_(x);
}

inline f32 reciprocal(const f32 f)
{
	//TODO优化
	return 1.f/f;
}

inline f64 reciprocal ( const f64 f )
{
	return 1.0 / f;
}

inline bool iszero(const f64 a, const f64 tolerance = ROUNDING_ERROR_f64)
{
	return fabs(a) <= tolerance;
}

inline bool iszero(const f32 a, const f32 tolerance = ROUNDING_ERROR_f32)
{
	return fabsf(a) <= tolerance;
}

inline bool iszero(const s32 a, const s32 tolerance = 0)
{
	return ( a & 0x7ffffff ) <= tolerance;
}

inline bool iszero(const u32 a, const u32 tolerance = 0)
{
	return a <= tolerance;
}

inline s32 s32_min(s32 a, s32 b)
{
	const s32 mask = (a - b) >> 31;
	return (a & mask) | (b & ~mask);
}

inline s32 s32_max(s32 a, s32 b)
{
	const s32 mask = (a - b) >> 31;
	return (b & mask) | (a & ~mask);
}

inline s32 s32_clamp (s32 value, s32 low, s32 high)
{
	return s32_min(s32_max(value,low), high);
}

template<class T>
inline const T square(const T& a)
{
	return a*a;
}

inline f32 squareroot(const f32 f)
{
	return sqrtf(f);
}

inline f64 squareroot(const f64 f)
{
	return sqrt(f);
}
inline s32 squareroot(const s32 f)
{
	return static_cast<s32>(squareroot(static_cast<f32>(f)));
}
inline f32 reciprocal_squareroot(const f32 f)
{
	return 1.f/ sqrtf(f);
}
inline s32 reciprocal_squareroot(const s32 x)
{
	return static_cast<s32>(reciprocal_squareroot(static_cast<f32>(x)));
}

//注意0不是2的N次幂
inline bool isPowerOf2(const u32 a)
{
	return a&&!(a&(a-1));
}
//获取比value大的最近2的N次幂，如果value为0，返回0
//注意0不是2的N次幂
inline u32 nearestPowerOf2(const u32 value)
{
	/* Error! */
	if (value == 0) return 0;

	u32 rval=1;
	while(rval<value) rval<<=1;
	return rval;

}
inline f32 fract(const f32 x )
{
	return x - floorf (x);
}

//获取n二进制表示中1的个数
inline u32 countBits(const u32 a)
{
	u32 s=0;
	u32 n=a;
	while(n)  
	{  
		n &= (n - 1);  
		++s;  
	}
	return s;
}

//获取a和b的最大公约数
inline s32 gcd(s32 a,s32 b){  
	s32 k=1,t;  
	while(~a&1 && ~b&1)k<<=1,a>>=1,b>>=1;  
	t=(a&1)?-b:a>>1;  
	do{  
		while(~t&1)t>>=1;  
		if(t>0)a=t;else b=-t;  
	}while(t=a-b);  
	return a*k;  
}  

}//core
}//yon

#endif