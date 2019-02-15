# 387Project
Project for OS with Dr. Professor. BJ Johnson
Thomas Ochsner, Kevin Peters, & Mike Justus West

## Preliminary Design

1.1 We are going to modify the mousedev and keydev modules to allow users to move the cursor using the arrow keys.

1.2 We feel that this adds some niche functionality. If a user ever finds themself without a working mouse or trackpad, this module allows them to still use their machine.

1.3 Modules that may need to be modified:
     input
     mousedev
     keydev
     usbcore
     uhci_hcd or ohci_hcd or ehci_hcd
     usbhid
1.4 Not Applicable. We only need to modify existing modules.
