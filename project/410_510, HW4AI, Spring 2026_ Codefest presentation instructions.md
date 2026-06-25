# Codefest presentation instructions

ECE 410/510, Spring 2026  
Last update: Mar 29, 2026

### Goals

* Share your idea  
* Share your progress  
* Hone your presentation skills

Schedule

* Presentation duration: **1 minute** (strict). Anybody talking for more than 1min is disqualified from extra tokens.  
* [https://docs.google.com/spreadsheets/d/12nw6twDNBKf7wRBwa3JbBLogtQKLwVh4Vk9SybJ6TJk](https://docs.google.com/spreadsheets/d/12nw6twDNBKf7wRBwa3JbBLogtQKLwVh4Vk9SybJ6TJk) 

### Instructions

1. Create a single (= 1 \= ONE) slide on which you answer the following questions:  
   1. **What are you trying to do?** I.e., what AI/ML algorithm/workload did you pick?)  
      - I'm trying to accelerate the Basic kalman filter algorithm (Give brief summary of algorithm with the Time and Measurement Update Functions).
   2. **How have others implemented and/or accelerated this algorithm?**  
      - Most common implementations use libaries such as FilterPy or NumPy in Python and Eigen Library or Hard-Coded Scalar C for C/C++.
   3. **What are you doing differently/better/etc.?**  
      - Created ASIC for Measurement Correction Kernal that can be added to a AXI-lite bus used in RISC-V SoCs (mention the key differences between this and the other implementations)
   4. **What have you accomplished so far?**  
      - Successful synthesis with full timing closure at AXI Bus clock frequency at __100 MHz__ with predicted preformance boast on RVfpgaEL2 enviornment to be 10x over software baseline
   5. **What will you do next and what remains to be done until you can declare success?**  
      - SoC integration and some other software/hardware optimizations if measured speedup over Software baseline. \(Summrize the best options using visualizations\)
   6. **Add Roofline Plot with Dominant kernal from Software Baseline and New Kernal from the Hardware Accelerator \(Potential or Measured\)**
2. The ideal slide would have not just text, but also some visualizations.  
3. Presentation duration: **1 minute** (strict)  
4. Save the slide in the shared Google folder at [https://drive.google.com/drive/folders/1xkjOLLmKAFy2\_0bcRC\_fw1UeiiQcG8Z4](https://drive.google.com/drive/folders/1xkjOLLmKAFy2_0bcRC_fw1UeiiQcG8Z4) 

