SIM = icarus
TOPLEVEL_LANG = verilog
VERILOG_SOURCES = $(PWD)/../hdl/mac_correct.v
TOPLEVEL = mac
MODULE = test_mac

# VCD tracing for verilator backend (sets both compile-time and runtime --trace flags)
ifeq ($(SIM),verilator)
VERILATOR_TRACE = 1
endif

include $(shell cocotb-config --makefiles)/Makefile.sim
