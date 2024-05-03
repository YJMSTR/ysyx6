#include <device/map.h>

static uint8_t *flash_base = NULL;

void init_flash() {
  flash_base = new_space(CONFIG_FLASH_SIZE);
  add_mmio_map("flash", CONFIG_FLASH_BASE, flash_base, CONFIG_FLASH_SIZE, NULL);
}