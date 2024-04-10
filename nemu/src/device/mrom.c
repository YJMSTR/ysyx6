#include <device/map.h>

static uint8_t *mrom_base = NULL;

void init_mrom() {
  mrom_base = new_space(CONFIG_MROM_SIZE);
  add_mmio_map("mrom", CONFIG_MROM_BASE, mrom_base, CONFIG_MROM_SIZE, NULL);
}