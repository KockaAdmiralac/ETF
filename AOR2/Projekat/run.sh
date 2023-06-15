#!/bin/bash
cd $(dirname $(realpath "$0"))

# Colors.
white="\033[0;37m"      # White - Regular
bold="\033[1;37m"       # White - Bold
cyan="\033[1;36m"       # Cyan - Bold
green="\033[1;32m"      # Green - Bold
red="\033[1;31m"        # Red - Bold
color_reset="\033[0m"   # Reset Colors

NUM_CPUS=$(grep -c "^processor" /proc/cpuinfo)

echo -e "-> ${cyan}Compiling unoptimized processor...${color_reset}"
rm -rf build
NO_DEBUG=1 OPTIMIZED_PROCESSOR=0 make -j$NUM_CPUS > /dev/null
echo -e "-> ${cyan}Running unoptimized processor...${color_reset}"
./build/aor2 "$@" --stats

echo -e "-> ${cyan}Compiling optimized processor...${color_reset}"
rm -rf build
NO_DEBUG=1 OPTIMIZED_PROCESSOR=1 make -j$NUM_CPUS > /dev/null
echo -e "-> ${cyan}Running optimized processor...${color_reset}"
./build/aor2 "$@" --stats

echo -e "${green}Done!${color_reset}"
