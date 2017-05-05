#include "multiPortMem.h"

int sc_main(int argc, char* argv[])
{
	multiPortMem EXC_TB ("EXC_Instance");

	sc_trace_file* VCDFile;
	VCDFile = sc_create_vcd_trace_file("multiportmem");
		sc_trace(VCDFile, EXC_TB.databusin1, "inb1");
		sc_trace(VCDFile, EXC_TB.databusout1, "oub1");
		sc_trace(VCDFile, EXC_TB.addrbus1, "adb1");
		sc_trace(VCDFile, EXC_TB.databusin2, "inb2");
		sc_trace(VCDFile, EXC_TB.databusout2, "oub2");
		sc_trace(VCDFile, EXC_TB.addrbus2, "adb2");
		sc_trace(VCDFile, EXC_TB.databusin3, "inb3");
		sc_trace(VCDFile, EXC_TB.databusout3, "oub3");
		sc_trace(VCDFile, EXC_TB.addrbus3, "adb3");
		sc_trace(VCDFile, EXC_TB.databusin4, "inb4");
		sc_trace(VCDFile, EXC_TB.databusout4, "oub4");
		sc_trace(VCDFile, EXC_TB.addrbus4, "adb4");
		sc_trace(VCDFile, EXC_TB.cs1, "cs1");
		sc_trace(VCDFile, EXC_TB.cs2, "cs2");
		sc_trace(VCDFile, EXC_TB.cs3, "cs3");
		sc_trace(VCDFile, EXC_TB.cs4, "cs4");
		sc_trace(VCDFile, EXC_TB.rwbar1, "rwb1");
		sc_trace(VCDFile, EXC_TB.rwbar2, "rwb2");
		sc_trace(VCDFile, EXC_TB.rwbar3, "rwb3");
		sc_trace(VCDFile, EXC_TB.rwbar4, "rwb4");
	sc_start(2500,SC_NS);
	return 0;
}


