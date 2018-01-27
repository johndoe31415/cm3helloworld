# cm3helloworld
A "Hello World" blinky example that activates that shows startup code and sets
up the clock to multiply the external HSE clock from 8 MHz to a 36 MHz system
clock using the PLL. Blinking frequency is around 1 Hz.

# Prerequisites
This has been compiled with gcc-7.3.0 and a minimal newlib configuration (not
necessary for the example, however). The STM32 standard peripheral library is
used for setting up GPIOs and needs to be downloaded externally from
STmicroelectronics: [STM32F1 Standard Peripheral
Library](http://www.st.com/en/embedded-software/stm32-standard-peripheral-libraries.html?querycriteria=productId=LN1939)

# License
GNU GPL-3.
