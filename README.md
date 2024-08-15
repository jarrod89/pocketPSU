# pocketPSU

## Specs  
Output1:  
- Efuse protected USBPD output
- 3A, 20V 
- setting resolution depends on capability of USB-C brickw. If using a PPS capable supply, 10mV CV and 50mA CC settings
- By default this output is disabled as the PD command will track output 3 for minimal power loss in LDO
- Must be lower than output2  
  
Input1:
- Output1 can be used to supply pocketPSU via a battery
- Optional battery charging capability (addon board with BMS)
  
Output2:  
- (optional) Boost output with efuse protection (no dedicated CC)
- 1A 3.3-30V
- By default this tracks output3 for minimal power loss in LDO
- Must be higher than output1 and output3

Output3:  
- LDO output for low ripple
- 1A 0-30V (limited current based on input/output delta)
- Must be lower than output1

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