# name of your application
APPLICATION = tbforth

# If no BOARD is found in the environment, use this default:
BOARD ?= native

# This has to be the absolute path to the RIOT base directory:
RIOTBASE ?= $(CURDIR)/../../RIOT

# Comment this out to disable code in RIOT that does safety checking
# which is not needed in a production environment but helps in the
# development process:
CFLAGS += -DDEVELHELP

# Change this to 0 show compiler invocation lines by default:
QUIET ?= 1

# Modules to include:
USEMODULE += stdin
USEMODULE += ztimer
USEMODULE += ztimer_sec
USEMODULE += ztimer_msec
USEMODULE += ztimer_usec

CFLAGS += -Wno-char-subscripts
CFLAGS += -Wno-int-to-pointer-cast
CFLAGS += -Wno-type-limits
CFLAGS += -Wno-unused-parameter
CFLAGS += -Wno-unused-value

include $(RIOTBASE)/Makefile.include
