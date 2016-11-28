# TI Launchpad for Embedded Systems courses on Linux/OSX/macOS

This repository is a template project for completing EE 445L assignments on
your UNIX-based operating system. This Makefile and `startup.c` file have some
extra work to make them compatible with both TivaWare code and ValvanoWare, the
custom drivers built for the EE 319K/445L course at UT Austin. If you aren't
in that class and just want to flash and debug a Tiva Launchpad, I'd advise you
check out [this other repository][tiva-project], since you won't have the code
overhead for compatibility with ValvanoWare.

## Bells and Whistles

I have been using this template as a base for all of the projects in EE 445L,
and because of that, I've added a couple of nice things to make development a
bit easier:

### YCM completer file

For `vim` users, I've added a YouCompleteMe file that will add dynamic
compile-time checking to your code. This provides fast-as-you-type
autocompletion for all the strange and esoteric names in TivaWare and
Valvanoware, which can really help you out. It also provides syntax
highlighting and all the cool code editing features you'd expect from an IDE
like Keil.

### GDB support

Debugging is crucial to embedded development. Using `openocd` and `gdb`, you
can step through your programs while running it on your launchpad, watch
variables, and set breakpoints. In addition to this, while I haven't done this
personally yet, you could also hook up `ddd`, a visual debugging program, for
even more useful debugging info.

### Serial console and limited `printf` support

When you connect a launchpad to your computer via the debug USB, it also
connects UART0 to a tty on your computer. I've added a simple serial console
implementation in python for you to attach to the serial console tty and see
printed output. This is *seriously* helpful. Note that if you intend on
overloading `printf` for other purposes, you'll need to comment out the
`printf` implementation functions in `UART.c`. You'll know you need to do this
once GCC starts yelling at you for defining `printf` functions multiple times.

### Assembly Output

The generated assembly side-by-side by the code is produced in listings for
each file in the `assembly_output` directory. This wasn't any fancy programming
on my part, just turning the right dials on GCC. However, it can be really
helpful-- it's just like the disassembly window in Keil.

## Getting Started

To compile and run the example project, run the following commands:

- `make clean && make`

- `sudo make flash` (you may not need sudo if you have user access to USB)

To debug and step through the program on the TM4C:

- `make clean && make`

- `sudo make debug`

... and after you're done debugging and have exited GDB,

- `sudo pkill openocd` to shut down the openocd program.

To run the serial console, open a separate terminal window and run

- `python3 serial_console.py /dev/ttyACM0`

The above command assumes that the tty opened for the Launchpad is named
ttyAMC0. This is true for most machines, but you should always check to be
sure.

## Dependencies

You'll need the following programs installed on your machine:

- [GNU Make][make] for running the Makefile

- [lm4tools][lm4tools-link] for flashing

- [OpenOCD][openocd-link] for creating a GDB bridge (recommend you install this via
  your package manager, the `Makefile` assumes the executable and board configs are
  in your path, which your package manager will do by default)

- [GNU ARM Cross Compiler][gnu-arm] for cross-compiling

- [GDB][GDB] to provide us with all the useful debugging tools you'd normally find
  in an IDE. I'd recommend installing this via your package manager rather than
  installing from source (i.e. `homebrew` from Mac OSX, `apt-get` for Ubuntu,
  etc.). Make sure it is the **cross-compiler version**, i.e. the executable
  has the name `arm-none-eabi-gdb`. Sometimes, this is already installed when
  you install the cross compiler (previous item).

- Python 3 for running `serial_console.py`

Finally, you'll need to download [ValvanoWare][valvoware] and
[TivaWare][tivaware]. Unzip these and place them somewhere safe in your
computer, then update the Makefile and `.ycm_extra_conf.py` with the paths to
each.

I'd recommend using your local package manager for as many of these programs
as you can. In OSX/macOS, I'd recommend using `homebrew`; for Linux, use your
distribution's package manager (`yum` for Fedora, `pacman` for Arch Linux,
`apt-get` for Ubuntu, etc.).

[tiva-project]: https://github.com/ReeceStevens/tiva-project
[make]: https://www.gnu.org/software/make/
[lm4tools-link]: https://github.com/utzig/lm4tools
[openocd-link]: http://openocd.org/
[GDB]: https://www.gnu.org/software/gdb
[gnu-arm]: https://launchpad.net/gcc-arm-embedded/+download
[valvoware]: http://edx-org-utaustinx.s3.amazonaws.com/UT601x/ValvanoWareTM4C123.zip
[tivaware]: http://www.ti.com/tool/sw-tm4c
