:: environment setting for dbus clients
@echo off

:: session bus address
set DBUS_SESSION_BUS_ADDRESS=tcp:host=localhost,port=54321,family=ipv4

:: system bus address
set DBUS_SYSTEM_BUS_DEFAULT_ADDRESS=unix:path=D:/developefile/GLIB-DBUS/dbus-master/out/install/x86-Release/var/run/dbus/system_bus_socket
