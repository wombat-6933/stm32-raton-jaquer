# Description
"El raton jaquer" is a solution to keep yourself always aviable in Teams and all that unhealthy corporative stuff. 
Raton jaquer presents to your PC as a regular mouse and sends moving actions automatically.
The name comes from a prank that we used to make our partners in school, connecting a stealth mouse or keyboard to the victim PC and moving it causing confusion.

# Instructions
 1. git clone --recurse-submodules https://github.com/wombat-6933/stm32-raton-jaquer.git
 2. cd stm32f103-raton-jaquer
 3. make -C libopencm3
 4. cd src/
 5. make
 6. make flash

# Hardware needed
 1. Supported STM32 board (check makefiles). By default stm32f103c8t6 is used
 2. Programmer for STM32. By default ST-Link V2 is used.
