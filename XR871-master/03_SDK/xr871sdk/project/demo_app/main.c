#include "common/framework/platform_init.h"
#include "fs/fatfs/ff.h"
#include "common/framework/fs_ctrl.h"
#include "kernel/os/os_thread.h"
#include "audio/pcm/audio_pcm.h"
#include "audio/manager/audio_manager.h"
#include "driver/chip/hal_gpio.h"
#include "kernel/os/os.h"

#include <string.h>
#include <stdio.h>
#include "uvoicetech.h"
#include "kws.h"
#define SOUND_CARD_ID 0
#define MBEDTLS_FS_IO
#define PCM_BUF_SIZE 640

#define SAMPLES_10MS 160


	int pcm_2ch_aec_demo(void)
	{
		int ret = 0;
		printf("222\n");
		int kws_res = 0;
		int ret_res = 0;
		void * kwsInst = NULL;
		void* aec_handle = NULL;
		struct pcm_config pcm_read_cfg;
		struct pcm_config pcm_write_cfg;
		char * pcm_buf = (char *)malloc(320 * sizeof(short));
		short * pcm_in  = (short *)malloc(160 * sizeof(short));
		short * pcm_ref = (short *)malloc(160 * sizeof(short));
		short * pcm_out = (short *)malloc(160 * sizeof(short));
		kws_uint16_t shift_frames   = 5; // 1 (0~10)
		kws_uint16_t smooth_frames  = 5; // 30 (0~30)
		kws_uint16_t lock_frames    = 1; // 60 (0~100)
		kws_uint16_t post_max_frames = 13; // 100 (0~100)
		kws_float32_t threshold     = 0.40f; // 0.60f (0.0f~1.0f)


		pcm_read_cfg.channels = 2;               
		pcm_read_cfg.format = PCM_FORMAT_S16_LE; 
		pcm_read_cfg.period_count = 2;           
		pcm_read_cfg.period_size =  80 * 2;      
		pcm_read_cfg.rate = 16000;               
		pcm_read_cfg.mix_mode = 1;               

		printf("333\n");

		kwsCreate(&kwsInst,"4F1B9088DB3E5992F3436D65E4654AEE77513065686D2604DEB2A032BE75263DC2C5D568D4ABE70B30F83D5F3C02824D99CAFD0A697F3C8D995EC026B7684700",512);
		if (NULL == kwsInst) {
			printf("Error to create kwsInst.\n");
		}
		printf("444\n");
		if (KWS_CODE_NORMAL != kwsInit(kwsInst)) {
			printf("Error to init kwsInst.\n");
		}   

		if (KWS_CODE_NORMAL != kwsSetConfig(kwsInst, kws_shiftFrames, &shift_frames)) {
			printf("kwsSetConfig kws_shiftFrames error.\n");
		}
		if (KWS_CODE_NORMAL != kwsSetConfig(kwsInst, kws_smoothFrames, &smooth_frames)) {
			printf("kwsSetConfig kws_smoothFrames error.\n");
		}
		if (KWS_CODE_NORMAL != kwsSetConfig(kwsInst, kws_lockFrames, &lock_frames)) {
			printf("kwsSetConfig kws_lockFrames error.\n");
		}

		if (KWS_CODE_NORMAL != kwsSetConfig(kwsInst, kws_postMaxFrames, &post_max_frames)) {
			printf("kwsSetConfig kws_postMaxFrames error.\n");
		}

		if (KWS_CODE_NORMAL != kwsSetConfig(kwsInst, kws_threshold, &threshold)) {
			printf("kwsSetConfig kws_threshold error.\n");
		}

    aecCreate( &aec_handle,"4F1B9088DB3E5992F3436D65E4654AEE77513065686D2604DEB2A032BE75263DC2C5D568D4ABE70B30F83D5F3C02824D99CAFD0A697F3C8D995EC026B7684700",512);
			     if(NULL == aec_handle)
				 {
					 printf("creat aec error");
					 }
				 if (0 != aecInit(aec_handle))
			          {
				              printf("init aec error \n");
			         }

 
		aud_mgr_handler(AUDIO_DEVICE_MANAGER_PATH,AUDIO_DEVICE_HEADPHONEMIC  | AUDIO_DEVICE_MAINMIC, 1);

		ret = snd_pcm_open(&pcm_read_cfg, SOUND_CARD_ID, PCM_IN);
		if (ret != 0) {
			printf("pcm open error for instream\n");
			goto out;
		}

		printf("555\n");
		printf("666\n");

		pcm_write_cfg.channels = 1;
		pcm_write_cfg.format = PCM_FORMAT_S16_LE;
		pcm_write_cfg.period_count = 2;
		pcm_write_cfg.period_size = 80 * 2;
		pcm_write_cfg.rate = 16000;
		pcm_write_cfg.mix_mode = 1;
		printf("777\n");
		ret_res = snd_pcm_open(&pcm_write_cfg, SOUND_CARD_ID, PCM_OUT);
		if (ret_res != 0) {
			printf("pcm send open error for instream\n");
			goto out;
		}


		while (1) {
			ret_res =snd_pcm_read(&pcm_read_cfg, SOUND_CARD_ID,pcm_buf, 640);
			if (ret_res == -1) {
				printf("pcm read error\n");
				goto out;
			}
			short * pcm_buffer = (short *)pcm_buf;
			for(int count = 0;count < 160;count++)
			{
				pcm_in[count]  = pcm_buffer[count*2];
				pcm_ref[count] = pcm_buffer[count*2 + 1];
			}
			aecProcess(aec_handle, (const short*)pcm_in, (const short*)pcm_ref, pcm_out, 160);
			kwsProcess(kwsInst,(const short *)pcm_out,160,&kws_res);

			if(1 == kws_res)
			{
				printf("<xiaozhi>\n");
			}
		}


out:
		snd_pcm_close(SOUND_CARD_ID, PCM_IN);
		snd_pcm_close(SOUND_CARD_ID, PCM_OUT);
		free(pcm_buf); 
		pcm_buf = NULL;
		free(pcm_in); 
		pcm_in = NULL;
		free(pcm_ref);
		pcm_ref = NULL; 
		free(pcm_out); 
		pcm_out = NULL;
		return ret;
	}


	int main(void)
	{
		platform_init();
		printf("111\n");
		pcm_2ch_aec_demo();
		return 0;
	}
