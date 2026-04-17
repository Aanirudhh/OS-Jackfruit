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

## 3. Demo with Screenshots

The following screenshots demonstrate the functionality of the implemented container runtime and kernel monitoring system.

---

### 3.1 Multi-container execution

**Commands used:**

./engine
cmd> start
cmd> start
cmd> list

**Description:**
This demonstrates multiple containers running simultaneously and being tracked using container IDs and process IDs.

**Screenshot:**
<img width="1600" height="135" alt="WhatsApp Image 2026-04-17 at 6 23 05 AM(1)" src="https://github.com/user-attachments/assets/2c3518ba-4150-40ba-93b7-81f5155c4e1f" />


---

### 3.2 Metadata tracking

**Commands used:**

cmd> list

**Description:**
Displays metadata of active containers including their IDs and PIDs.

**Screenshot:**
<img width="566" height="134" alt="WhatsApp Image 2026-04-17 at 6 23 21 AM" src="https://github.com/user-attachments/assets/20dd279c-2da5-41b2-b164-6e3aa26dfe48" />


---

### 3.3 Logging using pipes

**Commands used:**

cmd> start

**Description:**
Shows container output captured using pipe-based logging, with each output labeled by container ID.

**Screenshot:**
<img width="944" height="639" alt="image" src="https://github.com/user-attachments/assets/5838ff86-f067-4bb5-916f-ef1804640acf" />


---

### 3.4 CLI interaction and container control

**Commands used:**

cmd> list
cmd> stop 0
cmd> exit

**Description:**
Demonstrates command-line interface interaction and control over container lifecycle.

**Screenshot:**
<img width="566" height="134" alt="WhatsApp Image 2026-04-17 at 6 23 21 AM" src="https://github.com/user-attachments/assets/bec7e249-7687-4066-80ca-d0f3d9885526" />
<img width="566" height="134" alt="WhatsApp Image 2026-04-17 at 6 23 21 AM" src="https://github.com/user-attachments/assets/5819b7c4-ddd1-4500-bbf1-96938c54596b" />


---

### 3.5 Kernel module loading

**Commands used:**

sudo insmod monitor.ko
lsmod | grep monitor

**Description:**
Verifies that the kernel module is successfully loaded into the system.

**Screenshot:**
*(Insert screenshot here)*

---

### 3.6 Kernel memory monitoring

**Commands used:**

./engine
cmd> start
cmd> exit

sudo dmesg | tail

**Description:**
Shows memory usage of a container retrieved from the kernel module using ioctl and displayed via dmesg.

**Screenshot:**
*(Insert screenshot here)*

---

### 3.7 Clean termination

**Commands used:**

cmd> stop 0
cmd> exit

ps aux | grep engine

**Description:**
Demonstrates proper cleanup of processes with no zombie processes remaining after execution.

**Screenshot:**
*(Insert screenshot here)*

---

### Note

Advanced features such as supervisor-based container management, resource limit enforcement, and scheduling experiments were not implemented in this version. The focus of this project is on core process management, logging, and kernel interaction.

---

