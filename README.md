# AKernelADay
## Overview
This repository is being put together to give a step by step OS development process. Each day we will be attempting to apply a new concept or advance on an existing concept till we get to a fully functioning OS. This OS will contain as many features as I can pack in. However, we will initially be focusing on the simple concepts first: System Call wrappers, I/O (such as Ethernet or USB), etc. This project will not include any of the Standard C Libraries (we will use some of their header files to save time and energy), this means we are flying solo here. The first few weeks to months will be spent researching how an OS and kernel interact. Then a simple implementation will be made (basic concepts only, get the basics down: Hello World, Basic Drawing, Networking, etc). Then the next stage is to get a more detailed implementation down (multiple processes running, drivers, etc). Finally we will lower priviledge down to userspace and will implement individual users and user programs.

# Journal Entries
## Day ∅: Initial Commit - Project Structure
Each day that passes will be documented as to maintain a sort of "engineers journal". Today will be spent organizing my ideas and aproaches on how I want to handle/go about the project. All of my research will be documented under a folder labeled "Research" and the files (Markdown, ".md") will be seperated by concept and/or day. All source files will be placed under the folder "Source" and will be seperated out into individual sub-project folders. Common header ".h" files will be placed in a master "Include" folder (and any subfolders). Now, C was chosen because of its simplistic design and nature and C++ will most likely be integrated later in the project. C++ was not choosen for the project initialy due to some of the addon behaviors. C requires that you only implement a simple \_start function (as seen at https://en.wikipedia.org/wiki/Crt0) where as C++ requires a slightly more complex implementation (which is handled mostly by stdlib and we aren't using that). For initial OS development (at least in the init program) it should be dedicated to C to reduce complexity and possible bugs.

## Day 0: Initial Research - Who is the kernel and what do they do?

### Overview
The kernel is a an overseer that bridges the gap between software and hardware. After the bootloader (a program that has initial control over the computer) comes the kernel (Linux) or an operating system with the kernel built in (Windows). Like I stated the kernel is in charge of the hardware. This means the kernel will setup the hardware, listen for events and will finally act on those events.
In addition to this the kernel will listen to the software and will provide useful interaction with the hardware.

So far the boot process for a computer is: bootloader, kernel, operating system and finally user software. The boot process first starts by using a computers BIOS or UEFI rom (read only memory) chip. From there the BIOS or UEFI will search for bootable media. We will take a look at how these two work, starting with the BIOS.

### BIOS
The BIOS searches for a boot sector or the first sector on a disk with the byte code 0x55AA (x86). This byte code (found at the end of the boot sector) represents bootable media. Once found the boot sector is copied into memory from disk and is executed (~510 operations is all the bootloader gets initially). From there the bootloader will use the BIOS functions (essentially syscalls but done through the interupt vector table, https://en.wikipedia.org/wiki/BIOS_interrupt_call#Invoking_an_interrupt). Using this table the bootloader can load in additional object code as well as some other useful things. From here the bootloader must make its way into a 32 bit or 64 bit environment as we actually start out in a 8 bit environment for backwards compatibility. The bootloader can setup a GDT (Global Descriptor Table) and using it can jump into a 16 bit environment. 

From there additional setup such as a Virtual Memory Map Table can be setup in addition to updating the GDT for 32 bit mode and updating the CR0 register (https://en.wikipedia.org/wiki/Control_register#CR0) to enable the Protected Mode bit. Once set the register can be used to check if the bit was kept, if remained set then the processor is ready to jump to 32 bit mode using the same method that the 16 bit mode jump used. Otherwise the processor does not support 32 bit mode and cannot jump to it (usually never does because 16 bit processors are not common anymore in personal computers). 

Once in 32 bit mode the processor begins using the Virtual Memory Map (if one was setup in the prior step). From here code can check for 64 bit mode via the cpuid instruction (https://wiki.osdev.org/Setting_Up_Long_Mode), if passed the processor is ready for a final jump into 64 bit mode. Before jumping the bootloader must enable the floating point operations or FPU on the hardware (https://wiki.osdev.org/FPU#FPU_configuration) without this any float's and double's in a program cannot work and in fact will cause crashes or errors. Once enabled the jump to 64 bit land can be completed. From here the bootloader loads in the kernel, sets up the paging for the kernel, wraps up and jumps to the kernel's entry point.

### UEFI
UEFI is simple compared to its predecessor BIOS. The UEFI checks for a UEFI boot partition. If one is found then the UEFI marks the boot partition as an EFI System Partition. It acomplishes this by looking for a GUID in that partition, which identifies it as UEFI compatible. Once all partitions have been checked the standard boot sequence is used, typically UEFI prioritises all EFI System Partitions before then checking for MBR (Master Boot Record). If the MBR is searched for and found the same basic process that the BIOS uses is used here. If a EFI System Partition is used then the UEFI will execute a simply UEFI program (typically sets up the memory space and hardware before loading in the kernel). Once the kernel is loaded execution is handed over and the kernel is ready to go.

### Wrap up
Today we learned about the kernel and the bootloader. Although the kernel is what we will be mainly dealing with, it is important for us to understand that the kerenl isn't the first code to run on the computer. Code will always run before it, configuring the environment and setting things up. Once the kernel does gain control it ensures everything is ready for the operating system before stating it up.

### Implementation
So for our implementation we will be using the GRUB bootloader (which is useful because linux most often uses this). GRUB provides a series of scripts that allow us to configure it as we like. One script file allows us to define the Linux kernel file as well as an initrd file (which is a file containing a filesystem that is mounted to the computer and used during the kernel boot sequence, might not be used if kernel has it built in). We will be using a computer configured with the Ubuntu OS for our OS development. 

Take a flash drive or other kind of storage media and perfom the following:

    1. Make a ext4 partition, ensure it takes up the entire disk space as the OS can take up plenty of space. If using an HDD or SSD you can use up as much or as little space as you desire just ensure enough space for the kernel and operating system.

    2. Mount new partition, I choose to mount at /mnt/GenericOS 

    3. Remove lost+found folder, not needed but can stay if necessary. Add the folowing directories to /mnt/GenericOS: /boot /bin /sbin /etc /lib /lib64 /var /dev /proc /sys /run /tmp; Each one is necessary for the linux kernel to run.

    4. Run the following code:
        mknod -m 600 /mnt/GenericOS/dev/console c 5 1
        mknod -m 666 /mnt/GenericOS/dev/null c 1 3
       Creates the device files needed for linux.

    5. COPY over the kernel from your Ubuntu OS onto the storage media in the /mnt/GenericOS/boot directory, look for a vmlinux-{version} file, then look for a file named initrd.img-{version}; Where version matches the version of the vmlinuz file.

    6. Use the command "grub-install /dev/{MEDIA} --skip-fs-probe --boot-directory=/mnt/GenericOS/boot". This command uses your root filesystem device file representing the storage medias hardware, for example if your storage media is /dev/sdb0 then use that.

    7. GRUB should automatically install itself onto the disk, note this is the steps for a BIOS install not a UEFI install see grub-install documentation for any differences.

    8. A folder should have been created /mnt/GenericOS/boot/grub, inside this folder create a file named grub.cfg

    9. Enter the following into grub.cfg:
        set default = 0
        set timeout = 30

        menuentry "GenericOS" {
            # The next lines tells grub to load a linux kernel into memory, use version and media from prior steps. We use rw because ro ends up causing a failure in my testing.

            linux /boot/vmlinuz-{version} root=/dev/{MEDIA} rw
            initrd /boot/initrd.img-{version}
            boot
        }

    10. DONE, we now should have a fully bootable kernel. However, this kernel does not include an Operating System just yet. Upon booting the kernel we should either see an error or the kernel will crash. This is because the kernel has done its part and is now attempting to pass the baton over but no one is there to take it.

## Day 1: Research - Who takes over after the kernel and what do they do?

After the kernel the init program takes over. They reside at /sbin/init and handle the operating systems initialization. We will be building an init program capable of handling multiple runlevel's from:

    0. Turn off - The shutdown runlevel, executed when shutdown is requested.
    1. Single User Mode - The computer was booted up for a single user, typically admin.
    2. Multi User Mode - The computer was booted up for multiple users, networking is typically not setup initially.
    3. Multi User Mode w/ Networking - Same as 2 but with networking.
    4. Not Used - Implemented to keep with linux standard's.
    5. Full Mode - Same as 3 but with a display manager.
    6. Reboot - The reboot runlevel, executed when reboot is requested.

The file /etc/inittab will define our default runlevel and later a command can be provided to swap to a different runlevel. When a swap occurs any necessary services for the new runlevel will be started and any unnecessary services for the new runlevel will be stopped.

Once the runlevel has been achieved the init program will simply go dormant and wait for a runlevel change. From here we should be able to program any number of programs and have the init program handle it from there.

## Day 2: Research - Integrating C with Assembly.
A C program begins at the main function (usually defined as int main(int argc, char** argv)). However, this is not the case as it actually starts at a function named _start. This function is called prior to main to setup and execute main then finally execute the exit function using the return value from main. The _start function can be found in the ctr0.s file (s for assembly) located in the Source folder.

The _start function is called the entry point of our program, it is what the kernel expects to find to begin execution of the code. Without it the kernel will be unable to execute our code. From here we simply need to include the crt0.o file (o for object code) found in the Source folder, use "make crt0.s" for first time build.

### Why is this necessary?
Counter question, who likes PIE? Not the edible kind but the programming kind. PIE (also known as Position Independant Executeables), is a concept in computer science; In which the placement and order of object code/data is placed in random placement and order. Meaning your code is never really loaded in at the same place in memory every time. This is done to secure program's. If you were storing a password in memory somewhere and a hacker somehow began executing arbitrary code in your program wouldn't it be best if that password was loaded in a random location rather than a static one?

This concept is really useful for security purposes but causes one of two things, the need for the _start function (not the only reason but one of the major reasons) and the need for a /lib/ld-linux.so library. Once we start programming the OS we will need to copy over the existing ld-linux library from our Ubuntu install to allow for the dynamic linking of other libraries. Take some time to look through our Makefile's to see how linking and other concepts are tackled. I added in the crt0 and "Init" subproject ahead of schedule so that the initial idea could be cemented before worring about syscalls.

# Schedule/Backlog

## Day 3: Initial Coding - Implementing system calls with crt0 and main.
## Day 4: Coding - Libraries and migrating system calls.
## Day 5: Coding - Example programs (display, networking, and filesystem).
## Day 6: Refactor - Summarise what we have learned and improve code.
