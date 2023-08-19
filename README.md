# sample_rm_pico_app

This repo is a template repo to set up develpment for [pi pico](https://www.raspberrypi.com/documentation/microcontrollers/raspberry-pi-pico.html) to work in the [robomasters](https://www.robomaster.com/en-US) competition.

It uses the [rm_pico_dev](https://github.com/agmui/rm_pico_dev) library

# Setup Guide

## Linux(ubuntu)

```
git clone https://github.com/agmui/sample_rm_pico_app.git
cd sample_rm_pico_app
bash linux_init.sh
```

Next install vscode and go on to the [vscode section](#vscode-extensions)

## Windows

dependency:
[libusb download](https://github.com/libusb/libusb/releases/latest)

Next install [vscode](https://code.visualstudio.com/Download) and go on to the [vscode section](#vscode-extensions)

## Mac

<details>
<summary>might not work lol</summary>

`brew install libusb pkg-config`

</details>

## vscode extensions

Have vscode open this folder (`sample_rm_pico_app`)  
When first opining vscode should ask you to install the plugins  
![install plugins](pics/install_plugins.png)

If not just type `@recommened` here  
![recommened](pics/recommened.png)

These are recomened extensions to install.

## Uploading

Make sure the pico is pluged in

#### Method 1

> Note: This method assumes you installed all the recomned plugins from the [vscode section](#vscode-extensions)

Step1:  
select kit
![no kit selected button](pics/noKitBtn.png)
![seleting arm kit](pics/armKit.png)

Step2:  
press `ctrl + shift + B`  

### BIG NOTE: If the pico bricks you cant just use `ctrl+shift+B` you have to reset it or do Method 2

#### Method 2

```bash
mkdir build
cd build
cmake ..
make -j4
picotool load -f pico_app.uf2
```

#### If all else fails

<details>
<summary>Method 3</summary>

```bash
mkdir build
cd build
cmake ..
make -j4
```

unplug the pico  
Hold the bootsel button on the pico  
![bootsel](pics/bootsel.png)  
while still holding the button plug the pico back in

A usb stick should pop up in your file exploer  
TODO: add pic

drag and drop the `pico_app.u2f` file in the build folder

</details>

## Debugging

![picoprobe wiring](pic/../pics/picoprobe_wiring.png)
> sidenote: the debugger I use for those who care [pico_debug](https://github.com/essele/pico_debug/tree/v0.3)

## Running in Wokwi 👀

No pico no problem!

press `ctrl+shift+p` and type `Wokwi: Request a new License`
![wokwi license](pics/wokwi_license.png)

its going to ask to open a webpage  
![wokwi trust open webpage](pics/wokwi_license_open.png)

click get you license and make an account  
![wokwi get license](pics/wokwi_get_license.png)

this should pop up when it works  
![wokwi got license](pics/license_worked.png)

do `ctrl+shift+p` again  
type `Wokwi: Start Simulator and Wait for Debugger`
![wokwi debugging](pics/wokwi_debug_prompt.png)  

<details>
<summary>Select a Kit?</summary>

if it asks to select kit  
choose arm as kit  
![selecting kit for wokwi debug](pics/wokwi_select_kit.png)

</details>  

Next select the right debugger and run
![debug setup](pics/wokwi_debug_setup.png)

then open up `main.cpp` to add breakpoints

## Building

Method 1:  
Just press `f7` if you installed all plugins

Method 2:

```
mkdir build
cd build
cmake ..
make -j4
```
