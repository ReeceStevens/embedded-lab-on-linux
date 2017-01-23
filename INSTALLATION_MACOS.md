# Installation
## Install brew, Package manager for MacOS
[Homebrew][brew]

```bash
xcode-select --install
/usr/bin/ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)"
```

## Install arm cross compiler
[homebrew-arm][arm-cross]

```bash
brew tap osx-cross/arm
brew install arm-gcc-bin
```

## Installing lm4tools
[lm4tools][lm4tools-link]

```bash
cd lm4tools
brew install libusb

# In a directory of your choice
git clone https://github.com/utzig/lm4tools.git
cd lm4tools/lm4flash
make

# Update your path
echo 'PATH=$PATH:'$PWD >> ~/.bashrc
```

> NOTE: If you use ZSH, then update the append to the ~/.zshrc file instead of ~/.bashrc

## Installing OpenOCD
[OpenOCD][opencd-link]

```bash
brew install openocd
```

## Installing Python 3
[Python][python]

```bash
brew install python3
pip3 install -r requirements.txt
```

## Install ValvanoWare
Finally, you'll need to download [ValvanoWare][valvoware] and
[TivaWare][tivaware]. Place the downloads in the parent directory to this folder, and call them `ValvanoWare` and `TivaWare` respectively.

> NOTE: Download the `SW-TM4C: TivaWare for C Series Software (Complete)` exe by clicking *Get Software* and by filling out the form. Then open the .exe file and extract (I used the Unarchiver app) the `SW-TM4C-*` folder.

# Testing
```bash
make clean && make
make flash
```

[arm-cross]: https://github.com/osx-cross/homebrew-arm
[brew]: http://brew.sh
[lm4tools-link]: https://github.com/utzig/lm4tools
[openocd-link]: http://openocd.org/
[python]: https://www.python.org
[valvoware]: http://edx-org-utaustinx.s3.amazonaws.com/UT601x/ValvanoWareTM4C123.zip
[tivaware]: http://www.ti.com/tool/sw-tm4c
