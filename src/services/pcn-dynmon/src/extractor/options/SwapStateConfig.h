#pragma once

#include <polycube/services/table.h>
//The suffix to be added to the original map name when swapped
#define SWAP_MAP_NAME_FORMAT "_1"
#define SWAP_MASTER_TEMPLATE "PROGRAMTYPE"
#define SWAP_MASTER_INDEX_MAP "INTERNAL_PROGRAM_INDEX"

//Dynmon master code to be injected when swap is enabled
const std::string dynmon_swap_master = R"(
BPF_ARRAY(INTERNAL_PROGRAM_INDEX, int, 1);
BPF_ARRAY(counts, u64, 1);
BPF_ARRAY(counts_1, u64, 1);
static __always_inline int handle_rx(struct CTXTYPE *ctx, struct pkt_metadata *md) {
  unsigned key = 0;
  int *index = INTERNAL_PROGRAM_INDEX.lookup(&key);
  if(!index) {
    return RX_OK;
  }
  call_PROGRAMTYPE_program(ctx, *index);
  return RX_OK;
}
)";

/**
 * Container class responsible of holding all the needed data to perform, if needed, program swap
 */
class SwapStateConfig {
 public:
  SwapStateConfig() : current_program_index(1), swap_enabled(false){};

  /**
   * Method to find out if the swap functionality is enabled
   * @return true if swap enabled, false otherwise
   */
  bool isSwapEnabled() {
    return swap_enabled;
  }

  /**
   * Method to enable the swap functionality
   */
  void enableSwap() {
    swap_enabled = true;
  }

  int triggerRead() {
    current_program_index = (current_program_index % 2) + 1;
    return current_program_index;
  }

  /**
   * Method to accordingly modify the mapName with the defined suffix
   * @param map_name the name of the map to be modified
   */
  void formatMapName(std::string &map_name) {
    if(current_program_index == 1)
      map_name =  map_name + SWAP_MAP_NAME_FORMAT;
  }

 private:
  bool swap_enabled;                        //Variable to keep track if the program needs to be swapped (at least 1 map with swap enabled)
  int current_program_index;                //Variable to keep track of the current program index
};