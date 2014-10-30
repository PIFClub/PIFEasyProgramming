/*****************************************************************************/
/* stdarg.h   v4.2.1                                                         */
/*                                                                           */
/* Copyright (c) 1996-2013 Texas Instruments Incorporated                    */
/* http://www.ti.com/                                                        */
/*                                                                           */
/*  Redistribution and  use in source  and binary forms, with  or without    */
/*  modification,  are permitted provided  that the  following conditions    */
/*  are met:                                                                 */
/*                                                                           */
/*     Redistributions  of source  code must  retain the  above copyright    */
/*     notice, this list of conditions and the following disclaimer.         */
/*                                                                           */
/*     Redistributions in binary form  must reproduce the above copyright    */
/*     notice, this  list of conditions  and the following  disclaimer in    */
/*     the  documentation  and/or   other  materials  provided  with  the    */
/*     distribution.                                                         */
/*                                                                           */
/*     Neither the  name of Texas Instruments Incorporated  nor the names    */
/*     of its  contributors may  be used to  endorse or  promote products    */
/*     derived  from   this  software  without   specific  prior  written    */
/*     permission.                                                           */
/*                                                                           */
/*  THIS SOFTWARE  IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS    */
/*  "AS IS"  AND ANY  EXPRESS OR IMPLIED  WARRANTIES, INCLUDING,  BUT NOT    */
/*  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR    */
/*  A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT    */
/*  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,    */
/*  SPECIAL,  EXEMPLARY,  OR CONSEQUENTIAL  DAMAGES  (INCLUDING, BUT  NOT    */
/*  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,    */
/*  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY    */
/*  THEORY OF  LIABILITY, WHETHER IN CONTRACT, STRICT  LIABILITY, OR TORT    */
/*  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    */
/*  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.     */
/*                                                                           */
/*****************************************************************************/

#ifndef _STDARG
#define _STDARG

#ifdef __cplusplus
#define _NS_PREFIX std::
namespace std {
#else
#define _NS_PREFIX
#endif /* __cplusplus */

typedef char *va_list;

#ifdef __cplusplus
} /* namespace std */
#endif

#define _VA_RNDUP(sz) 	(((sz) + 1) & ~1)

/*****************************************************************************/
/* On the MSP430, the stack grows down (towards 0x0), and arguments are      */
/* pushed in reverse order, so later arguments are at higher addresses.      */
/*****************************************************************************/

/*****************************************************************************/
/* VA_START(va_list ap, parmN)                                               */
/*                                                                           */
/*   Set "ap" to point to the address of the next argument past parmN.       */
/*   So add the size of parmN to the address of parmN.                       */
/*                                                                           */
/*   NOTES -must use the address of the level 1 symbol (via va_parmadr).     */
/*         -must account for "chars", which are widened to "ints".           */
/*                                                                           */
/*****************************************************************************/
#if defined(__LARGE_DATA_MODEL__)
#define va_start(ap, parmN)                                                   \
((ap) = (_NS_PREFIX va_list)((long)__va_parmadr(parmN) +                      \
			     (__va_argref(parmN) ?                            \
			      sizeof(&parmN) :                                \
			      (sizeof(parmN) < sizeof(int) ? sizeof(int) :    \
			                                     sizeof(parmN)))))
#else
#define va_start(ap, parmN)						      \
   ((ap) = (__va_argref(parmN) || (sizeof(parmN) < sizeof(int)) 	      \
              ? (_NS_PREFIX va_list)((int)__va_parmadr(parmN) + 2 )	      \
	      : (_NS_PREFIX va_list)((int)__va_parmadr(parmN) + sizeof(parmN))))
#endif
/*****************************************************************************/
/* VA_ARG(va_list, type)                                                     */
/*                                                                           */
/*   Return next argument (currently pointed to by "va_list", and set the    */
/*   argument pointer to point to the next argument after current one.       */
/*                                                                           */
/*   Notes -must handle variables passed by reference (_va_argref())         */
/*         -must round up chars.                                             */
/*                                                                           */
/*****************************************************************************/
#define va_arg(_ap, _type)                                       	      \
        (__va_argref(_type)                         		              \
	 ? ((_ap += sizeof(_type*)), (**(_type**)(_ap - sizeof(_type *))))    \
	 : ((_ap += _VA_RNDUP(sizeof(_type))),				      \
	     (*(_type*)(_ap - _VA_RNDUP(sizeof(_type))))))

#define va_end(ap) ((void)0)

#ifdef __cplusplus

#ifndef _CPP_STYLE_HEADER
using std::va_list;
#endif /* _CPP_STYLE_HEADER */

#endif /* __cplusplus */

#else

#ifdef __cplusplus

#ifndef _CPP_STYLE_HEADER
using std::va_list;
#endif /* _CPP_STYLE_HEADER */

#endif /* __cplusplus */

#endif /* _STDARG */
