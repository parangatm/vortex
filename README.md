# Vortex GPGPU

Vortex is a full-stack open-source RISC-V GPGPU. Vortex supports multiple **backend drivers**, including our C++ simulator (simx), an RTL simulator, and physical Xilinx and Altera FPGAs-- all controlled by a single driver script. The chosen driver determines the corresponding code invoked to run Vortex. Generally, developers will prototype their intended design in simx, before completing going forward with an RTL implementation. Alternatively, you can get up and running by selecting a driver of your choice and running a demo program.

Vortex README continued here: [README.md](./Vortex_README.md)

---

This repository contains my implementation of the lab assignments from CS 259 GPU Microarchitecture course at UCLA taught by Prof. Tine in Fall 2024.

## Lab 1

 **Objective**: Introduction to the basics of parallel programming, execution, and evaluation on a GPU.

 **Description**: [Lab1](./labs/lab1/cs259_lab1.pdf)

 **Deliverables**:
 - [source.diff](./labs/lab1/source.diff) : diff file showing the changes made to the source code
 - [report.pdf](./labs/lab1/gpu_lab1_report.pdf) :  written report detailing the evaluation results

 > See the exact changes for lab 1 via the 'lab1' branch

## Lab 2

 **Objective**:  Extending GPU microarchitecture by implementing a new software prefetch instruction to reduce global memory latency

 **Description**: [Lab2](./labs/lab1/cs259_lab2.pdf)

 **Deliverables**:
 - [source.diff](./labs/lab2/source.diff) : diff file showing the changes made to the source code
 - [report.pdf](./labs/lab2/gpu_lab2_report.pdf) :  written report detailing the evaluation results

 > See the exact changes for lab 2 via the 'lab2' branch

 ## Lab 3

 **Objective**:   extending GPU microarchitecture to accelerate a kernel in hardware

 **Description**: [Lab3](./labs/lab3/cs259_lab3.pdf)

 **Deliverables**:
 - [source.diff](./labs/lab3/source.diff) : diff file showing the changes made to the source code
 - [report.pdf](./labs/lab3/gpu_lab3_report.pdf) :  written report detailing the evaluation results

 > See the exact changes for lab 3 via the 'lab3' branch

 ---