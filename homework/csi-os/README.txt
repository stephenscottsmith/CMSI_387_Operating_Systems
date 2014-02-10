Mac OS X (10.8)

Websites I found useful:
https://developer.apple.com/library/mac/documentation/Darwin/Conceptual/KernelProgramming/Architecture/Architecture.html#//apple_ref/doc/uid/TP30000905-CH1g-TPXREF108

http://en.wikipedia.org/wiki/Mach_(kernel)

1) Pre-OS Software
File: mac_bootloader
Description: highlighted is the "boot.efi" Mac bootloader. This is
the first program when Mac computer starts up. It helps load the kernel and 
carries out a number of system checks.

2) Kernel file(s)
File: mac_kernal
Description: the "mach_kernel" is the kernel that Apple developed
from its original beginnings at Carnegie Melon.

3) Startup scripts and/or configuration files
File: mac_startup_scripts
Description: the highlighted "rc.common" file is where the mac
goes for its startup scripts. 

4) The "first process"
File: mac_first_process
Description: highlighted is the "kernel_task" with a process id number of 0

5) Network Settings
File: mac_network_settings
Description: my Macbook Pro's network settings

-----------------------------------------------

Ubuntu 12.04

1) Pre-OS Software
File: linux_grub_bootloader
Description: highlighted is the grub bootloader used by many linux
implementations. This is the first program when Mac computer starts up. 
It helps load the kernel and carries out a number of system checks. 
There is also the LILO bootloader as well (not documented in picture) that
is used by many linux implementations.

2) Kernel file(s)
File: linux_kernel
Description: the highlighted "vmlinux-3.8.0-35-generic" Ubuntu kernel. 
There was also a link for it in the root directory.

3) Startup scripts and/or configuration files
File: linux_startup_scripts
Description: highlighted the "init" and "init.d" scripts folders.
"init" is where the startup conifgs live and "init.d" is where the system 
scripts are placed.

4) The "first process"
File: linux_first_process
Description: highlighted "init" process in the System Monitor

5) Network Settings
File: linux_network_settings
Description: screen capture of the Network Settings within
the Ubuntu System Settings 

------------------------------------------------

Windows 8 (ew)

Websites I found useful:
http://en.wikipedia.org/wiki/History_of_Microsoft_Windows

http://www.dummies.com/how-to/content/how-to-enable-boot-logging-in-windows.navId-397923.html

http://en.wikipedia.org/wiki/Windows_Startup_Process

1) Pre-OS Software
File: windows_boot_loader
Description: highlighted is the Window boot loader, which is a portion of the Windows
OS that finds the Windows kernel and starts it up.

2) Kernel file(s)
File: windows_kernel
Description: this is the Windows kernel, ntoskrnl.exe

3) Startup scripts and/or configuration files
File: windows_system_config
Description: the “system.ini” file is one of the many configuration files that windows stores its system settings in. “win.ini” is another.

4) The "first process"
File: windows_boot_log	
Description: I was unsure as to which one was the first process because it did not have any time information. From what I found online, the boot loader, bootmgr.efi, is the first process that is run in startup; however, I figured I would include the boot log. In Windows 8 it is a setting to log the startup of the OS. (lame)

5) Network Settings
File: windows_network_settings
Description: I could not find the Windows equivalent that listed a number of network settings, so I used ipconfig on the command line.

