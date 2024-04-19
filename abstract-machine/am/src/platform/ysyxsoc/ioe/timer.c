#include <am.h>
#include <ysyxsoc.h>
#include <klib-macros.h>

void __am_timer_init() {
  putstr("am_timer_init\n");
}
char s[24];
void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  putstr("am_timer_uptime\n");
  volatile uint64_t uptime_addr = (uint64_t)uptime;
  
  for (int i = 0; uptime_addr != 0; i++) {
    s[i] = (uptime_addr % 16 >= 10) ? (uptime_addr % 16 - 10 + 'a') : uptime_addr + '0';
    uptime_addr /= 16;
  }
  putstr("uptime_addr=");
  putstr(s);
  putstr("\n");
  uint64_t clk = 0;
  clk = (((uint64_t)inl(RTC_ADDR + 4) /5ull) << 32ull) + inl(RTC_ADDR) / 5ull;
  uptime->us = clk;
  putstr("uptime down\n");
}

volatile void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  putstr("am_timer_rtc\n");
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}