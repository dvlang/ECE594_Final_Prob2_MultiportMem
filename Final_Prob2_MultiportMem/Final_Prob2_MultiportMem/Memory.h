#include <systemc.h>
#include <iostream>

#define WORD_LENGTH 8 
#define ADDRESS 10 
#define ADDR_SPACE 1024
 
SC_MODULE (Memory) {

	sc_in_rv <ADDRESS> addr1;
	sc_in_rv <WORD_LENGTH> datain1;
	sc_out_rv <WORD_LENGTH> dataout1;
	sc_in_rv <ADDRESS> addr2;
	sc_in_rv <WORD_LENGTH> datain2;
	sc_out_rv <WORD_LENGTH> dataout2;
	sc_in_rv <ADDRESS> addr3;
	sc_in_rv <WORD_LENGTH> datain3;
	sc_out_rv <WORD_LENGTH> dataout3;
	sc_in_rv <ADDRESS> addr4;
	sc_in_rv <WORD_LENGTH> datain4;
	sc_out_rv <WORD_LENGTH> dataout4;


	sc_in_resolved cs1, cs2, cs3, cs4, rwbar1, rwbar2, rwbar3, rwbar4;

	sc_uint <WORD_LENGTH> mem [ADDR_SPACE];

	void meminit ();
	void memread ();
	void memwrite ();
	void memdump ();

	SC_CTOR(Memory) {
		SC_THREAD (meminit);
		SC_METHOD (memread);

			sensitive << addr1 << addr2 << addr3 << addr4 << cs1<< cs2<< cs3<< cs4 << rwbar1 << rwbar2 << rwbar3 << rwbar4;

		SC_METHOD (memwrite);

			sensitive << addr1 << addr2 << addr3 << addr4 << cs1 << cs2 << cs3 << cs4 << rwbar1 << rwbar2 << rwbar3 << rwbar4;
		SC_THREAD (memdump);
	}
};
