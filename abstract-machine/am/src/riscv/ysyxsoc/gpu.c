#include <am.h>
#include <ysyxsoc.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
  // int i;
  // int w = inw(VGACTL_ADDR+2);
  // int h = inw(VGACTL_ADDR);
  // uint32_t *fb = (uint32_t*)(uintptr_t)FB_ADDR;
  // for (i = 0; i < w * h; i ++) fb[i] = i;
  // outl(SYNC_ADDR, 1);
}

void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  cfg->present = false;
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
}

void __am_gpu_status(AM_GPU_STATUS_T * status) {
  
}


