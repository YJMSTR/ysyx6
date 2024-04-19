#include <am.h>
#include <klib-macros.h>

void __am_timer_init();
void __am_timer_rtc(AM_TIMER_RTC_T *);
void __am_timer_uptime(AM_TIMER_UPTIME_T *);
void __am_input_keybrd(AM_INPUT_KEYBRD_T *);
void __am_gpu_config(AM_GPU_CONFIG_T *);
void __am_gpu_status(AM_GPU_STATUS_T *);
void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *);
void __am_audio_config(AM_AUDIO_CONFIG_T *);
void __am_audio_ctrl(AM_AUDIO_CTRL_T *);
void __am_audio_status(AM_AUDIO_STATUS_T *);

static void __am_timer_config(AM_TIMER_CONFIG_T *cfg) { cfg->present = true; cfg->has_rtc = true; }
static void __am_input_config(AM_INPUT_CONFIG_T *cfg) { cfg->present = true;  }

typedef void (*handler_t)(void *buf);
static volatile void *lut[128] = {
  [AM_TIMER_CONFIG] = __am_timer_config,
  [AM_TIMER_RTC   ] = __am_timer_rtc,
  [AM_TIMER_UPTIME] = __am_timer_uptime,
  [AM_INPUT_CONFIG] = __am_input_config,
  [AM_INPUT_KEYBRD] = __am_input_keybrd,
  [AM_GPU_CONFIG  ] = __am_gpu_config,
  [AM_GPU_FBDRAW  ] = __am_gpu_fbdraw,
  [AM_GPU_STATUS  ] = __am_gpu_status,
  [AM_AUDIO_CONFIG] = __am_audio_config,
  [AM_AUDIO_CTRL  ] = __am_audio_ctrl,
};

static void fail(void *buf) { 
  panic("access nonexist register");  
}

// char str[30];
bool ioe_init() {
  
  putstr("ioe init\n");
  lut[AM_TIMER_CONFIG] = __am_timer_config;
  lut[AM_TIMER_RTC]    = __am_timer_rtc;
  lut[AM_TIMER_UPTIME] = __am_timer_uptime;

  for (int i = 0; i < LENGTH(lut); i++){
    if (!lut[i]) {
      lut[i] = fail;
      // putstr("no\n");
    } else {
      putstr("yes\n");
    }
    // } else {
    //   uint64_t tmp = i;
    //   int j;
    //   for (j = 0; tmp != 0 && j < 10; j++) {
    //     str[j] = tmp % 10 + '0';
    //     tmp /= 10;
    //   }
    //   putstr("lut nonzero reg:\n")
    //   putstr(str);
    //   putstr(" == \n");
    //   tmp = (uint64_t)lut[i];
    //   for (j = 0; tmp != 0; j ++) {
    //     str[i] = (tmp % 16 >= 10) ? (tmp % 16 - 10 + 'a') : tmp + '0';
    //     tmp /= 16;
    //   }
    //   putstr(str);
    //   putstr("\n");
    // }
  }
  // __am_gpu_init();
  __am_timer_init();
  // __am_audio_init();
  return true;
}

void ioe_read (int reg, void *buf) { 
  char s[10];
  int tmp = reg;
  for (int i = 0; tmp != 0 && i < 10; i++) {
    s[i] = tmp % 10 + '0';
    tmp /= 10;
  }
  putstr("ioe read reg:=");
  putstr(s);
  putch('\n');
  ((handler_t)lut[reg])(buf); 
}
void ioe_write(int reg, void *buf) {
  char s[10];
  int tmp = reg;
  for (int i = 0; tmp != 0 && i < 10; i++) {
    s[i] = tmp % 10 + '0';
    tmp /= 10;
  }
  putstr("ioe write reg:=");
  putstr(s);
  putch('\n');
  ((handler_t)lut[reg])(buf); 
}
