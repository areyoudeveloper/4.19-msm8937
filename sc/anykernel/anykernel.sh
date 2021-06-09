# AnyKernel3 Ramdisk Mod Script
# osm0sis @ xda-developers
properties() { '
kernel.string=GoGreen4.9
do.devicecheck=0
do.modules=0
do.systemless=0
do.cleanup=1
do.cleanuponabort=0
device.name1=generic
device.name2=
device.name3=
device.name4=
device.name5=
supported.versions=
'; }

block=/dev/block/bootdevice/by-name/boot;
is_slot_device=0;
ramdisk_compression=auto;

. tools/ak3-core.sh;

chmod -R 750 $ramdisk/*;
chown -R root:root $ramdisk/*;

dump_boot;

ui_print "*******************************************"
ui_print "Updating Kernel and Patching cmdline..."
ui_print "*******************************************"

write_boot;
