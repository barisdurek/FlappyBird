# Flappy Bird - mkeykernel Version
This project is a simple Flappy Bird game running on a custom operating system kernel called mkeykernel. It uses basic graphics and runs directly on a virtual machine (QEMU) without any operating system.
### Original GitHub repo of the kernel:
```
git clone https://github.com/arjun024/mkeykernel.git
```
### Debugging:
```
 make
```
### Running the game: 
```
qemu-system-x86_64 -kernel kernel.bin
```