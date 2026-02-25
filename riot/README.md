
# RIOT - the friendly Operating System for the Internet of Things

see <https://www.riot-os.org/>.

## Introduction

RIOT supports many boards, CPU & microcontroller architectures + a native port.

RIOT includes a build system based on Makefile,
and comes with a lot third party packages (file systems, networking, ...).

In RIOT, the RTOS kernel is optional.

In RIOT, hardware is abstracted by vendor-agnostic driver APIs.

> Write once, run anywhere.

> Promises only bind those who believe in them.

## Usage on native port

see [instructions](https://guide.riot-os.org/getting-started/installing/).

```
$ make all
$ bin/native64/tbforth.elf
RIOT native interrupts/signals initialized.
TZ not set, setting UTC
RIOT native64 board initialized.
RIOT native hardware initialization complete.

main(): This is RIOT! (Version: 2026.01)

	Dict: 3644 cells (7288 bytes) used out of 32767 cells. (11 % used).
	Total RAM : 4096 cells (16384 bytes)
	Data Stack: 50 cells. Return Stack: 50 cells.
	User RAM: 260 cells (1040 bytes) used out of 3908 cells

 ok
3 4 + .
3 4 + .

7  ok

```

## Usage on Raspberry Pi Pico

see [instructions](https://guide.riot-os.org/getting-started/installing/#architecture-arm7-and-arm-cortex-m).

```
$ make BOARD=rpi-pico all flash
```

```
main(): This is RIOT! (Version: 2026.01)

	Dict: 3644 cells (7288 bytes) used out of 32767 cells. (11 % used).
	Total RAM : 4096 cells (16384 bytes)
	Data Stack: 50 cells. Return Stack: 50 cells.
	User RAM: 260 cells (1040 bytes) used out of 3908 cells

 ok
: led0 25 gpio-write ;
 ok
1 led0
 ok
0 led0
 ok

```

## Usage on Arduino Nano ESP32

see [instructions](https://guide.riot-os.org/getting-started/installing/#architecture-xtensa).

```
$ make BOARD=arduino-nano-esp32 all flash
```
