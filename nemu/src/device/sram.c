#include <device/map.h>

static uint8_t *sram_base = NULL;

void init_sram() {
  sram_base = new_space(CONFIG_SRAM_SIZE);
  add_mmio_map("sram", CONFIG_SRAM_BASE, sram_base, CONFIG_SRAM_SIZE, NULL);
}