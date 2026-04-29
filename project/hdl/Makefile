SIM ?= verilator
TOPLEVEL_LANG = verilog
VERILOG_SOURCES = $(PWD)/kalman_filter.sv
TOPLEVEL = kalman_filter
MODULE = tb_kalman_filter

ifeq ($(SIM),verilator)
VERILATOR_TRACE = 1
endif

include $(shell cocotb-config --makefiles)/Makefile.sim
