install plctool
git clone https://github.com/qca/open-plc-utils.git
open folder:
  - make
  - sudo make install
  - add: dtoverlay=qca7000
  - plctool -i eth1 -p pev.pib local
  - ./pev.sh pev.pib
  - modpib -N <NMK> -v pev.pib (<NMK> B59319D7E8157BA001B018669CCEE30D: network membership key cua tram xoac)
  - plctool -i eth1 -P pev.pib (load fw to qca)
  - update network membership key, network identifier trong slac/pev.ini giong nhu tram xoac
  - pev -i eth1 -p ~/Desktop/open-plc-utils/slac/pev.ini (check connection)
  - copy pev.ini to home folder

sudo systemctl enable pigpiod
sudo systemctl stop pigpiod.service
sudo vim /lib/systemd/system/pigpiod.service
pigpiod -x -1
sudo systemctl daemon-reload
sudo systemctl restart pigpiod.service

REWRITE LOGGING INFO
ADD DUMP MSG
FIX SLAC VERIFY
RECHECK OPERATION OF Testcase/TestBehavior
ADD implementation for Plug&Charge msg

A: It’s usually the task of a boot loader and board support package code to bridge between the persistent MAC
address storage (e.g. some OTP bits) and the Device Tree/platform data to tell the driver which MAC address to
use. In the case of the RPi there simply does not exist such a static assignment, so the driver has no chance but
to use a random MAC address. However, you can workaround this by specifying an MAC address in Raspbian
network configuration. For this create a file /etc/network/interfaces.d/eth1 with the following content:
auto eth1
iface eth1 inet dhcp
hwaddress ether 00:01:87:ff:ff:fe