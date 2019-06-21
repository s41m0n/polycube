#! /bin/bash

# 4 pcn-bridge; square topology;
# connect extra links between bridges 1-3 2-4
# test connectivity, after convergence

source "${BASH_SOURCE%/*}/../../helpers.bash"

function cleanup {
  set +e
  del_bridges 2
  del_bridges_lb 3 4
  delete_veth 4
  delete_link 6
}
trap cleanup EXIT

set -x

#setup
create_veth 4
create_link 6

set -e

add_bridges_stp 2
add_bridges_lb 3 4

set_br_priority_lb br3 32768
set_br_priority_lb br4 36864

# create ports
bridge_add_port br1 link11
polycubectl br1 stp 1 set priority=28672
bridge_add_port br1 link42

bridge_add_port br2 link12
polycubectl br2 stp 1 set priority=24576
bridge_add_port br2 link21

bridge_add_port_lb br3 link22
bridge_add_port_lb br3 link31

bridge_add_port_lb br4 link32
bridge_add_port_lb br4 link41


bridge_add_port br1 link51
bridge_add_port_lb br3 link52
bridge_add_port br2 link61
bridge_add_port_lb br4 link62

bridge_add_port br1 veth1
bridge_add_port br2 veth2
bridge_add_port_lb br3 veth3
bridge_add_port_lb br4 veth4

#sleeping
sleep $CONVERGENCE_TIME


#testing connectivity
ping_cycle 4