#ifndef _UVOICE_TECH_H_
#define _UVOICE_TECH_H_


#ifdef __cplusplus
extern "C"
{
#endif

	/*-----------------------------------------------------*/
	/*   Error codes - success must ALWAYS equate to 0     */
	/*-----------------------------------------------------*/
#define AEC_GENER_ERROR       -1
#define AEC_UNINIT_ERROR      -2
#define AEC_NULLPTR_ERROR     -3
#define AEC_PARAMETER_ERROR   -4
#define AEC_VERIFY_ERROR      -5
#define AEC_PARAMETER_WARNING  1

	/*--------------------------------------------------------------------------------------*/
	/*      Define identification strings                                                   */
	/*--------------------------------------------------------------------------------------*/
	typedef enum aec_mode {
		aec_modeRecog = 0, /* ASR (Automatic speech recognition) or KWS (Keyword Search) */
		aec_modePhone = 1  /* Phone Call */
	} aec_mode;

typedef unsigned char aec_uint8_t;
typedef signed char aec_int8_t;

typedef unsigned short aec_uint16_t;
typedef signed short aec_int16_t;

typedef unsigned int aec_uint32_t;
typedef signed int aec_int32_t;

typedef float aec_float32_t;




	typedef enum aec_paramterId {
		aec_processMode,     /* aec_mode  : aec_modeRecog
							  * aec_modeRecog or aec_modePhone */

		aec_nonLinearLevel,  /* int       : 1 (1~12).
							  * The bigger the stronger echo cancellation,
							  * but speech recognition performance may be even worse */
		aec_filterNum,       /* int       : 12 (1~12).
							  * The bigger the stronger echo cancellation,
							  * but more time-consuming. */

		aec_suppressLevel,   /* default 0*/
		aec_doNr,            /* int        : 1 or 0. whether or not use post nr*/
		aec_doAgc,           /* int        : 1 or 0. whether or not use post agc*/
		aec_testMethod,
	} aec_paramterId;




	const char* aecGetVersion(void);


	void  * aecCreate(void ** PaecInst, char *license_str, unsigned int license_str_len);



	signed int aecInit(void* aecInst);


	signed int aceSetConfig(void* aecInst, aec_paramterId parmId, const void* data);


	signed int aceGetConfig(void* aecInst, aec_paramterId parmId, void* data);



	signed int aecProcess(void* aecInst, const short* audioInBuf, const short* refInBuf, short* aecOutBuf, short samples);


	void aecDesrtoy(void * aecInst);



#endif
