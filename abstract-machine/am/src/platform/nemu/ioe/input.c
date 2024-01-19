#include <am.h>
#include <nemu.h>

#define KEYDOWN_MASK 0x8000

void __am_input_keybrd(AM_INPUT_KEYBRD_T *kbd) {
  int t = inl(KBD_ADDR);
  kbd->keycode = t & 0xff;
  kbd->keydown = 0;
  if (kbd->keycode != AM_KEY_NONE) {
    //printf("keycode = %d\n", kbd->keycode);
    if (t & KEYDOWN_MASK)
      kbd->keydown = 1;
  }
}
