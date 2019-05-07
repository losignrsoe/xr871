/* =======================================================================================
*  Project          Keyword Search (KWS)
*  (c) Copyright    2014-2018
*  Company          Shanghai UVoice Information Technology CO., LTD
*                   All rights reserved
*  Secrecy Level    STRICTLY CONFIDENTIAL
* --------------------------------------------------------------------------------------*/
/**
 *  @internal
 *  @file kws.h
 *
 *  Prototypes of the Keyword Search (KWS) API functions.
 *
 *  This header file contains all prototypes of the API functions of the Keyword Search (KWS) module.
 */
/*======================================================================================*/
/** @addtogroup DEF
*  @{*/
#ifndef _UVOICE_KWS_H_
#define _UVOICE_KWS_H_

#ifdef __cplusplus
extern "C"
{
#endif

/*-----------------------------------------------------*/
/*   Error codes                                       */
/*-----------------------------------------------------*/
#define KWS_CODE_ERROR_PARAMETER -4
#define KWS_CODE_ERROR_NULLPTR   -3
#define KWS_CODE_ERROR_GENER     -2
#define KWS_CODE_ERROR_UNINIT    -1
#define KWS_CODE_NORMAL           0
#define KWS_CODE_PROCESSEND       1

/*--------------------------------------------------------------------------------------*/
/*   Type definitions                                                                       */
/*--------------------------------------------------------------------------------------*/
typedef unsigned char kws_uint8_t;
typedef signed char kws_int8_t;

typedef unsigned short kws_uint16_t;
typedef signed short kws_int16_t;

typedef unsigned int kws_uint32_t;
typedef signed int kws_int32_t;

typedef float kws_float32_t;


//extern int chipid_kws[4];
//extern unsigned int uiHexArray[8];

typedef enum kws_paramterId_e {
    kws_shiftFrames,   /* kws_uint16_t  : 1 (0~10) */
    kws_smoothFrames,  /* kws_uint16_t  : 30 (0~30) */
    kws_lockFrames,    /* kws_uint16_t  : 60 (0~100) */
    kws_postMaxFrames, /* kws_uint16_t  : 100 (0~100) */
    kws_threshold,     /* kws_float32_t : 0.60f (0.0f~1.0f) */
} kws_paramterId;

/*-----------------------------------------------------------------------------*/
/*    Function prototypes                                                   */
/*-----------------------------------------------------------------------------*/
/**
*  This function get keyword name.
*
* @param
*      index      -I  : Keyword index.
*      name       -IO : Pointer pointer to keyword name (not has copy operation) or NULL.
* @return
*      Returns KWS_CODE_NORMAL if success or other error code.
*/
kws_int32_t kwsGetName(kws_uint16_t index, const char** name);

/**
*  This function get all keywords.
*
* @return
*      Returns keywords.
*/
const char* kwsGetKeywords(void);

/**
*  This function get version.
*
* @return
*      Returns version name.
*/
const char* kwsGetVersion(void);

/**
 * Allocates the memory needed by the KWS.
 *
 * @param
 *      kwsInst -IO: Pointer to the created object or NULL with error.
 *
 */
void kwsCreate(void** kwsInst,char *license_str, unsigned int license_str_len);

/**
 *  Initializes the KWS instance.
 *
 * @param
 *      kwsInst    -IO : Pointer to the KWS instance.
 * @return
 *      Returns KWS_CODE_NORMAL if success or other error code.
 */
kws_int32_t kwsInit(void* kwsInst);

/**
 *   This function enables the user to set certain parameters on-the-fly.
 *
 * @param
 *      kwsInst    -IO : Pointer to the KWS instance.
 *      parm_id    -I  : Parameter id.
*       data       -I  : Pointer to the parameter data.
 * @return
 *      Returns KWS_CODE_NORMAL if success or other error code.
 */
kws_int32_t kwsSetConfig(void* kwsInst, kws_paramterId parmId, const void* data);

/**
 *   This function enables the user to get certain parameters on-the-fly.
 *
 * @param
 *      kwsInst    -IO : Pointer to the KWS instance.
 *      parm_id    -I  : Parameter id.
*       data       -I  : Pointer to the parameter data.
 * @return
 *      Returns KWS_CODE_NORMAL if success or other error code.
 */
kws_int32_t kwsGetConfig(void* kwsInst, kws_paramterId parmId, void* data);

/**
 *  Reset the KWS instance.
 *
 * @param
 *      kwsInst    -IO : Pointer to the KWS instance.
 * @return
 *      Returns KWS_CODE_NORMAL if success or other error code.
 */
kws_int32_t kwsReset(void* kwsInst);

/**
* Search keyword on one frame of data.
*
* @param
*      kwsInst        -IO : Pointer to the KWS instance.
*      audio          -I  : In buffer containing one frame of recording signal (Number of samples must be 160).
*                           If "audio" set NULL means end of process.
*      samples        -I  : Number of samples in audio buffer, must be 160 now.
*      keyIndex       -IO : Index greater than 0 means keyword has been searched, call kwsGetName() to review the keyword name.
* @return
 *      Returns KWS_CODE_NORMAL or KWS_CODE_PROCESSEND if success or other error code
*/
kws_int32_t kwsProcess(void* kwsInst, const kws_int16_t* audio, kws_uint16_t samples, kws_uint16_t* keyIndex);

/**
 * This function releases the memory allocated by UVoiceKWS_Create().
 *
 * @param
 *     uvoiceKWS -IO: Pointer to the KWS instance.
 */
void kwsDesrtoy(void** kwsInst);

#ifdef __cplusplus
}
#endif

#endif // _UVOICE_KWS_H_
/**@}*/
