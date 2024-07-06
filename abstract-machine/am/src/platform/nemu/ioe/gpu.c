#include <am.h>
#include <nemu.h>

#define SYNC_ADDR (VGACTL_ADDR + 4)

void __am_gpu_init() {
}
void __am_gpu_config(AM_GPU_CONFIG_T *cfg) {
  *cfg = (AM_GPU_CONFIG_T) {
    .present = true, .has_accel = false,
    .width = 0, .height = 0,
    .vmemsz = 0
  };
  int w = inw(VGACTL_ADDR+2);
  int h = inw(VGACTL_ADDR);
  cfg->height = h;
  cfg->width = w;
  cfg->vmemsz = w * h;
}

void __am_gpu_fbdraw(AM_GPU_FBDRAW_T *ctl) {
  int w = inw(VGACTL_ADDR + 2);
  //int h = inw(VGACTL_ADDR);
  uint32_t *fb = (uint32_t *)(uintptr_t)FB_ADDR;
  uint32_t *pixels = ctl->pixels;
  if (ctl->sync) {
    outl(SYNC_ADDR, 1);
  } 
  for (int i = 0; i < ctl->h /*&& i + ctl->y < h*/; i++) {
    for (int j = 0; j < ctl->w /*&& j + ctl->x < w*/; j++) {
      int t = (i + ctl->y) * w + j + ctl->x;
      fb[t] = *(pixels + i * ctl->w + j);
    }
  }
}

void __am_gpu_status(AM_GPU_STATUS_T *status) {
  status->ready = true;
}
