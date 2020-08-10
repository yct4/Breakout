# Plant the Lawn
A game based on the old arcade game Breakout where the player replaces blocks of dirt with tuffs of grass.

## Development

Everything will be run and compiled using an Ubuntu Desktop Image in Virtualbox.

1. Download Virtualbox on Mac or Windows.
2. Download the Ubuntu for desktop .iso file from [source](https://ubuntu.com/download/desktop).
3. Ensure that the repo folder is shareable as per these [instructions](https://www.howtogeek.com/howto/2845/install-guest-additions-to-windows-and-linux-vms-in-virtualbox/) and then these[https://www.howtogeek.com/187703/how-to-access-folders-on-your-host-machine-from-an-ubuntu-virtual-machine-in-virtualbox/](https://www.howtogeek.com/187703/how-to-access-folders-on-your-host-machine-from-an-ubuntu-virtual-machine-in-virtualbox/)
4. Ensure that the boot from floppy is switched [off](https://askubuntu.com/questions/263421/ubuntu-in-virtualbox-wants-to-install-on-every-boot).
4. To speed up the machine check [this](https://thomas.vanhoutte.be/miniblog/guide-speed-up-ubuntu-virtualbox/).
5. Run install script in the terminal for ubuntu for desktop.
`sudo ./install.sh`

Source: [https://www.instructables.com/id/How-to-Create-an-Ubuntu-Virtual-Machine-with-Virtu/](https://www.instructables.com/id/How-to-Create-an-Ubuntu-Virtual-Machine-with-Virtu/)

### Attempt 1: Xquartz/XServer

An earlier attempt involved trying to use Xquartz/Server and running a GUI-based application
using Docker on Windows or MAC. This, however, ran into multiple errors on a Mac so was abandoned.

Source:
1. Mac, Windows, Linux: [https://cuneyt.aliustaoglu.biz/en/running-gui-applications-in-docker-on-windows-linux-mac-hosts/](https://cuneyt.aliustaoglu.biz/en/running-gui-applications-in-docker-on-windows-linux-mac-hosts/)
2. Mac: [https://sourabhbajaj.com/blog/2017/02/07/gui-applications-docker-mac/](https://sourabhbajaj.com/blog/2017/02/07/gui-applications-docker-mac/)

### Attempt 2: Using Vagrant and Virtualbox

While this mostly worked, I couldn't manage to open the desktop ubuntu using vagrant AND virtualbox,
despite numerous attempts. My Stackoverflow searches are below.

Install vagrant: `brew cask install vagrant`
Install virtualbox: `brew cask install virtualbox`.

(Note: If the installation fails with an error, follow the directs here: [https://developer.apple.com/library/archive/technotes/tn2459/_index.html](https://developer.apple.com/library/archive/technotes/tn2459/_index.html).)

Install vagrant-manager: `brew cask install vagrant-manager`

Source: [https://sourabhbajaj.com/mac-setup/Vagrant/README.html](https://sourabhbajaj.com/mac-setup/Vagrant/README.html)

Attempt to get ubuntu desktop working with vagrant:
1. [https://stackoverflow.com/questions/26909433/ubuntu-via-vagrant-with-gui](https://stackoverflow.com/questions/26909433/ubuntu-via-vagrant-with-gui)
2.[https://stackoverflow.com/questions/18878117/using-vagrant-to-run-virtual-machines-with-desktop-environment](https://stackoverflow.com/questions/18878117/using-vagrant-to-run-virtual-machines-with-desktop-environment)
3. [https://stackoverflow.com/questions/31845472/how-do-i-install-a-vagrant-linux-box-that-has-a-gui-gnome-kde](https://stackoverflow.com/questions/31845472/how-do-i-install-a-vagrant-linux-box-that-has-a-gui-gnome-kde)
4. [https://stackoverflow.com/questions/15243405/is-it-possible-for-vagrant-to-use-an-os-iso-install-image-directly-or-create-a](https://stackoverflow.com/questions/15243405/is-it-possible-for-vagrant-to-use-an-os-iso-install-image-directly-or-create-a)

## Goal
Learn the basics of C++ SDL game development (building off of Pong).

## Basic Mechanics
https://youtu.be/AMUv8KvVt08
Player moves a paddle to hit a ball. The ball will rebound and hit blocks above the player. The game ends when the player misses the ball and it hits the bottom boundary. The score updates in real-time as the player plays. the ball speed will increase with time.

## Tasks
1. Showcase the paddle at the bottom of the screen. X
2. Switch ball trajectory to up-down. X
2.1. Game ends when the ball hits the bottom boundary. X
3. Add a map with the breakout blocks. (Block class? Map class?) X
3.1. Blocks are removed from the map as the ball hits each block. X
3.1.1. Detect which side of the block was hit by the ball to determine the resulting velocity of the ball
3.2. Game polls and refreshes the map. X
3.3. Make Game class to tie stuff together. X
4. Display score at the top.
5. Add levels
5.1. Display new level screen between levels.
5.2. Map class member to store scores (e.g. current level, current score, best score)
