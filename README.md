# Mini Container Runtime with Kernel Memory Monitor

## 1. Team Information

* Name: Anirudha Alagawadi
* SRN: PES2UG24CS067

---

## 2. Build, Load, and Run Instructions

### Step 1: Clone Repository

git clone <your-forked-repo-link>
cd OS-Jackfruit/boilerplate

---

### Step 2: Install Dependencies

sudo apt update
sudo apt install build-essential linux-headers-$(uname -r)

---

### Step 3: Build the Project

make

This compiles:

* engine (user-space runtime)
* monitor.ko (kernel module)

---

### Step 4: Load Kernel Module

sudo insmod monitor.ko

Verify module is loaded:

lsmod | grep monitor

---

### Step 5: Start the Container Runtime

./engine

---

### Step 6: Using the CLI

Available commands:

cmd> start      # Start a new container
cmd> list       # List active containers
cmd> stop <id>  # Stop a container
cmd> exit       # Exit the runtime

---

### Step 7: Example Run Sequence

cmd> start
cmd> start
cmd> list
cmd> stop 0
cmd> list
cmd> exit

---

### Step 8: Run Workloads

By default, containers execute programs using exec().
You can modify engine.c to run:

* ./cpu_hog
* ./memory_hog
* ./io_pulse

---

### Step 9: View Memory Usage (Kernel Output)

sudo dmesg | tail

Example output:

PID 4168 memory: 159744 bytes

---

### Step 10: Unload Kernel Module

sudo rmmod monitor

---

### Step 11: Clean Build Files

make clean

---

## Notes

* The project was tested on Ubuntu 22.04/24.04
* Ensure kernel headers are installed before building
* Use sudo for kernel-related commands
* The system demonstrates:

  * Process creation using fork() and exec()
  * Container management using IDs and PIDs
  * Inter-process communication using pipes
  * Signal handling to prevent zombie processes
  * Kernel module interaction using ioctl

---

## Project Structure

* engine.c → User-space container runtime
* monitor.c → Kernel module for memory monitoring
* Makefile → Build system

---

## Output Summary

The system successfully demonstrates:

* Creation and execution of containers
* Management of multiple containers
* CLI-based interaction
* Logging of container outputs
* Kernel module loading and unloading
* Memory monitoring using dmesg

---
