sudo apt-get update
sudo apt-get install apt-transport-https ca-certificates gnupg software-properties-common wget
wget -O - https://apt.kitware.com/keys/kitware-archive-latest.asc 2>/dev/null | gpg --dearmor - | sudo tee /etc/apt/trusted.gpg.d/kitware.gpg >/dev/null
For Ubuntu Focal Fossa (20.04):

sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ focal main'
sudo apt-get update
For Ubuntu Bionic Beaver (18.04):

sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ bionic main'
sudo apt-get update
For Ubuntu Xenial Xerus (16.04):

sudo apt-add-repository 'deb https://apt.kitware.com/ubuntu/ xenial main'
sudo apt-get update

sudo apt-get install kitware-archive-keyring
sudo rm /etc/apt/trusted.gpg.d/kitware.gpg

To install gcc-6 (gcc-6.1.1), I had to do more stuff as shown below.
USE THOSE COMMANDS AT YOUR OWN RISK. I SHALL NOT BE RESPONSIBLE FOR ANYTHING.
ABSOLUTELY NO WARRANTY.

If you are still reading let's carry on with the code.

sudo apt-get update && \
sudo apt-get install build-essential software-properties-common -y && \
sudo add-apt-repository ppa:ubuntu-toolchain-r/test -y && \
sudo apt-get update && \
sudo apt-get install gcc-snapshot -y && \
sudo apt-get update && \
sudo apt-get install gcc-6 g++-6 -y && \
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-6 60 --slave /usr/bin/g++ g++ /usr/bin/g++-6 && \
sudo apt-get install gcc-4.8 g++-4.8 -y && \
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.8 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.8;

When completed, you must change to the gcc you want to work with by default. Type in your terminal:
sudo update-alternatives --config gcc

To verify if it worked. Just type in your terminal
gcc -v


sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-X g++-X
gcc-X --version

The best way to correctly install gcc-4.9 and set it as your default gcc version use:

sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get update
sudo apt-get install gcc-4.9 g++-4.9
sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-4.9 60 --slave /usr/bin/g++ g++ /usr/bin/g++-4.9

Then you can check which one that is set, and change back and forth using:

sudo update-alternatives --config gcc


wget https://dl.bintray.com/boostorg/release/1.75.0/source/boost_1_75_0.tar.bz2 --proxy-user=[user] --proxy-password=[pass] --no-check-certificate

tar --bzip2 -xf /path/to/boost_1_75_0.tar.bz2



apt-get install libboost-dev
apt-get install libboost-system-dev
