# ECE 410/510 Spring 2026
### Jose Ramirez

## Project: Basic Kalman Filter Update HW Accelerator  

## Module Description

Updates the prediction accroding to the actual value of measurement.  

## Interface Choice

I be using the PCIe interface used by the Intel i7 11800H core since the update Kernal's low arithmetic intensity of 0.4637 FLOP/Byte making it memory-bound. This means that the maximum performance is 23.74 GFLOPs as the maximum bandwidth is 

## Precision Justification

I'll be sticking to the FP64 for now since the purpose of the Kalman filter is to precise results.
