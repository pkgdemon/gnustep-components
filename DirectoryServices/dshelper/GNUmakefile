include $(GNUSTEP_MAKEFILES)/common.make

TOOL_NAME = dshelper

dshelper_OBJC_FILES = \
	main.m \
	dshelper.m

dshelper_HEADER_FILES = \
	dshelper.h

dshelper_OBJCFLAGS = -fobjc-arc
dshelper_LDFLAGS = -ldispatch -lBlocksRuntime
# crypt(3) is in a separate libcrypt on Linux and FreeBSD, but is part of libc
# on OpenBSD (there is no libcrypt to link against).
ifneq ($(findstring openbsd,$(GNUSTEP_HOST_OS)),openbsd)
dshelper_LDFLAGS += -lcrypt
endif

# Install to /System/Library/Tools
GNUSTEP_INSTALLATION_DOMAIN = SYSTEM

include $(GNUSTEP_MAKEFILES)/tool.make

# Install service files (platform-specific)
after-install::
ifeq ($(findstring freebsd,$(GNUSTEP_HOST_OS)),freebsd)
	@# NextBSD compiles as FreeBSD (config.guess does not know it) but boots
	@# launchd, so the init system is detected here rather than from
	@# $(GNUSTEP_HOST_OS). /usr/lib/system is the marker used elsewhere.
	@if [ -d /usr/lib/system ] && command -v launchctl >/dev/null 2>&1; then \
		$(MKINSTALLDIRS) /System/Library/LaunchDaemons; \
		$(INSTALL) -m 644 org.gnustep.gdomap.plist /System/Library/LaunchDaemons/org.gnustep.gdomap.plist; \
		$(INSTALL) -m 644 io.github.gershwin-desktop.dshelper.plist /System/Library/LaunchDaemons/io.github.gershwin-desktop.dshelper.plist; \
		echo "Installed launchd daemons (gdomap + dshelper)"; \
	else \
		$(MKINSTALLDIRS) /usr/local/etc/rc.d; \
		$(INSTALL) -m 555 dshelper.rc /usr/local/etc/rc.d/dshelper; \
		echo "Installed rc.d script (dshelper)"; \
	fi
endif
ifeq ($(findstring linux,$(GNUSTEP_HOST_OS)),linux)
	@if command -v systemctl >/dev/null 2>&1; then \
		$(MKINSTALLDIRS) /etc/systemd/system; \
		$(INSTALL) -m 644 dshelper.service /etc/systemd/system/dshelper.service; \
		$(INSTALL) -m 644 gdomap.service /etc/systemd/system/gdomap.service; \
		echo "Installed systemd services (dshelper + gdomap)"; \
	elif [ -d /etc/init.d ]; then \
		$(INSTALL) -m 755 dshelper.init /etc/init.d/dshelper; \
		echo "Installed sysvinit script"; \
	else \
		echo "No supported init system detected"; \
	fi
endif
