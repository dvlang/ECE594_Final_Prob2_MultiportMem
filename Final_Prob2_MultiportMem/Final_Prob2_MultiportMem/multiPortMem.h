#include "Memory.h"
#include "exchanger.h"

SC_MODULE(multiPortMem)
{

	sc_signal_rv<WORD_LENGTH> databusin1, databusout1;
	sc_signal_rv<ADDRESS> addrbus1;
	sc_signal_rv<WORD_LENGTH> databusin2, databusout2;
	sc_signal_rv<ADDRESS> addrbus2;
	sc_signal_rv<WORD_LENGTH> databusin3, databusout3;
	sc_signal_rv<ADDRESS> addrbus3;
	sc_signal_rv<WORD_LENGTH> databusin4, databusout4;
	sc_signal_rv<ADDRESS> addrbus4;
	sc_signal_resolved cs1, cs2, cs3, cs4, rwbar1, rwbar2, rwbar3, rwbar4;

	sc_mutex writeBusses;
	sc_semaphore readBusses;

	exchanger* EXC1;
	exchanger* EXC2;
	exchanger* EXC3;
	exchanger* EXC4;

	Memory* MEM;
	
	void resetting();
	void clocking();
	void displaying();
	
	SC_CTOR(multiPortMem):readBusses(3)
	{
		EXC1 = new exchanger("EXC1_Instance", 1, 1); 
			EXC1->cs(cs1);
			EXC1->rwbar(rwbar1);
			EXC1->datain(databusin1);
			EXC1->dataout(databusout1);
			EXC1->addr(addrbus1);
			EXC1->permit=&writeBusses;  // Pass mutex reference
			EXC1->readpermit = &readBusses;  // Pass semaphore reference

		EXC2 = new exchanger("EXC2_Instance", 2,1);
			EXC2->cs(cs2);
			EXC2->rwbar(rwbar2);
			EXC2->datain(databusin2);
			EXC2->dataout(databusout2);
			EXC2->addr(addrbus2);
			EXC2->permit=&writeBusses;  // Pass mutex reference
			EXC2->readpermit = &readBusses;  // Pass semaphore reference

		EXC3 = new exchanger("EXC3_Instance", 3, 1);
			EXC3->cs(cs3);
			EXC3->rwbar(rwbar3);
			EXC3->datain(databusin3);
			EXC3->dataout(databusout3);
			EXC3->addr(addrbus3);
			EXC3->permit = &writeBusses;  // Pass mutex reference
			EXC3->readpermit = &readBusses;  // Pass semaphore reference

		EXC4 = new exchanger("EXC4_Instance", 4,1);
			EXC4->cs(cs4);
			EXC4->rwbar(rwbar4);
			EXC4->datain(databusin4);
			EXC4->dataout(databusout4);
			EXC4->addr(addrbus4);
			EXC4->permit = &writeBusses;  // Pass mutex reference
			EXC4->readpermit = &readBusses;  // Pass semaphore reference
			

		MEM = new Memory("MEM_Instance");

			(*MEM) (addrbus1, databusin1, databusout1, addrbus2, databusin2, databusout2, addrbus3, databusin3, databusout3, addrbus4, databusin4, databusout4, cs1, cs2, cs3, cs4, rwbar1, rwbar2, rwbar3, rwbar4);
	
	
	}


};
 