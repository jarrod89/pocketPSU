# pocketPSU

## Specs

### Power outputs
Output1 / Battery input:
- efuse protected USBPD output
- 3A, 30V
- Use when paired with a PPS capable supply for charging batteries or general supply output

Output2 (optional):
- buck-boost output
- 1A 0-60V

Output3:
- LDO output for low ripple
- 1A 0-60V (limited current based on input/output delta)

### User interface

The user interface will consist of:

- One LCD screen
- One rotary encode + integrated switch. The switch could serve as a way to switch between fine and coarse setting
- One button to turn the power output on/off
- Three buttons for navigation:
  - Up
  - Down
  - Select

### Powering the PSU

The supply can be powered over USB-C or using an external battery. The battery could potentially be a power tool battery that users already have on hand.

## LCD ato code for reference:

```
component lcd_GMT020_01:
    # This is a 2" diagonal 240(H)RGB x 320(V) lcd module from alibaba with a flex-pcb solder interface 
    # (like the lcd modules from sparkfun etc, but minus the interface PCB)
    # It has a built in ST7789VW driver, with SPI interface 
    footprint = "LCD-GMT020-02"
    mpn = "GMT020-02"
    power = new Power
    spi = new LCDSPI
    # LCD flex interface
    power.gnd ~ pin 1
    signal LEDK ~ pin 2
    power.vcc ~ pin 3 # led anode
    power.vcc ~ pin 4
    power.gnd ~ pin 5
    power.gnd ~ pin 6
    spi.dc ~ pin 7
    spi.cs ~ pin 8
    spi.sck ~ pin 9
    spi.mosi ~ pin 10
    spi.reset ~ pin 11
    power.gnd ~ pin 12
    # cap bypass
    c_bp1 = new myCap
    c_bp1.value = 1uF +/- 25%
    c_bp1.p1 ~ power.vcc
    c_bp1.p2 ~ power.gnd
    # Backlight control 
    # max current = 80mA, min Vf = 2.9V
    # R = (3.3-2.9)/0.08 = 5ohm. FET is ~1ohm, so can use 4.7R
    rBL = new myRes
    rBL.value = 4.7ohm +/- 5%
    rBL.p1 ~ LEDK
    nfet = new _2N7002
    nfet.S ~ power.gnd
    nfet.D ~ rBL.p2
    nfet.G ~ spi.backlightEN

```