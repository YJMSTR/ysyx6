#include <am.h>
#include <npc.h>

void __am_timer_init() {
}

void __am_timer_uptime(AM_TIMER_UPTIME_T *uptime) {
  uint64_t clk = 0;
  clk = (((uint64_t)inl(RTC_ADDR + 4) /5ull) << 32ull) + inl(RTC_ADDR) / 5ull;
  uptime->us = clk;
}

void __am_timer_rtc(AM_TIMER_RTC_T *rtc) {
  rtc->second = 0;
  rtc->minute = 0;
  rtc->hour   = 0;
  rtc->day    = 0;
  rtc->month  = 0;
  rtc->year   = 1900;
}
