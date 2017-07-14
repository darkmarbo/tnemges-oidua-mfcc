

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 7.00.0555 */
/* at Fri Jul 14 13:30:25 2017
 */
/* Compiler settings for AudioSegment.idl:
    Oicf, W1, Zp8, env=Win32 (32b run), target_arch=X86 7.00.0555 
    protocol : dce , ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
/* @@MIDL_FILE_HEADING(  ) */

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 440
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __AudioSegment_h_h__
#define __AudioSegment_h_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef __IAudioSegment_FWD_DEFINED__
#define __IAudioSegment_FWD_DEFINED__
typedef interface IAudioSegment IAudioSegment;
#endif 	/* __IAudioSegment_FWD_DEFINED__ */


#ifndef __AudioSegment_FWD_DEFINED__
#define __AudioSegment_FWD_DEFINED__

#ifdef __cplusplus
typedef class AudioSegment AudioSegment;
#else
typedef struct AudioSegment AudioSegment;
#endif /* __cplusplus */

#endif 	/* __AudioSegment_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 



#ifndef __AudioSegment_LIBRARY_DEFINED__
#define __AudioSegment_LIBRARY_DEFINED__

/* library AudioSegment */
/* [version][uuid] */ 


EXTERN_C const IID LIBID_AudioSegment;

#ifndef __IAudioSegment_DISPINTERFACE_DEFINED__
#define __IAudioSegment_DISPINTERFACE_DEFINED__

/* dispinterface IAudioSegment */
/* [uuid] */ 


EXTERN_C const IID DIID_IAudioSegment;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("2A88D239-A4A3-4295-B9BF-DDE43FA8E81E")
    IAudioSegment : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct IAudioSegmentVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            IAudioSegment * This,
            /* [in] */ REFIID riid,
            /* [annotation][iid_is][out] */ 
            __RPC__deref_out  void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            IAudioSegment * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            IAudioSegment * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            IAudioSegment * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            IAudioSegment * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            IAudioSegment * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [range][in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            IAudioSegment * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } IAudioSegmentVtbl;

    interface IAudioSegment
    {
        CONST_VTBL struct IAudioSegmentVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define IAudioSegment_QueryInterface(This,riid,ppvObject)	\
    ( (This)->lpVtbl -> QueryInterface(This,riid,ppvObject) ) 

#define IAudioSegment_AddRef(This)	\
    ( (This)->lpVtbl -> AddRef(This) ) 

#define IAudioSegment_Release(This)	\
    ( (This)->lpVtbl -> Release(This) ) 


#define IAudioSegment_GetTypeInfoCount(This,pctinfo)	\
    ( (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo) ) 

#define IAudioSegment_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    ( (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo) ) 

#define IAudioSegment_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    ( (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId) ) 

#define IAudioSegment_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    ( (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr) ) 

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* __IAudioSegment_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_AudioSegment;

#ifdef __cplusplus

class DECLSPEC_UUID("7511E10C-432A-47A8-8047-6E893780C0F1")
AudioSegment;
#endif
#endif /* __AudioSegment_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


