#include "exchanger.h"
#include <time.h>

void exchanger::exchanging() {
	int i, dval, startaddr, numreadbytes;
	bool readwrite = false;

	srand(device*(unsigned)time(NULL));

	while(true) {
		cout << "Device: "<< device <<" at " << sc_time_stamp() <<" is idle ...\n";

		wait(delay*30,SC_NS);
		
		//randomize the reads and writes so they don't just stack up on each other
		if ((rand() % 50) >= 25) {
			readwrite = true;
		}
		else {
			readwrite = false;
		}

		if (readwrite) {
			//********WRITING************

			cout << "Device: " << device << " at " << sc_time_stamp() << " has requested to write...\n";

			permit->lock();

			cout << "Device: " << device << " at " << sc_time_stamp() << " is granted the use of memory ...\n";

			//startaddr = rand() % ADDR_SPACE;
			startaddr = device*100;
			numreadbytes = rand() % 63;	//randomize the number of bytes to read

			//for (i = 0; i <= 63; i++) {
			for (i = 0; i <= numreadbytes; i++) {
			
				dval = rand() % WORD_LENGTH;
				datain = (sc_lv<WORD_LENGTH>)dval;
				addr = (sc_lv<ADDRESS>)(startaddr + i);
				cs = (sc_logic)'1';
				rwbar = (sc_logic)'0';
				wait(1, SC_NS);	//delay 1 sec to let var propagate
				cout << "Device: " << device << " at " << sc_time_stamp() << " WRITE to memory ADDR:  " << addr << " DATA: " << datain << endl;
				wait(delay, SC_NS);	//each device will have its own delay
			}

			cs = (sc_logic)'Z';
			rwbar = (sc_logic)'Z';
			datain = (sc_lv<WORD_LENGTH>)"ZZZZZZZZ";
			addr = (sc_lv<ADDRESS>)"ZZZZZZZZZZ";

			cout << "Device: " << device << " wrote in the memory starting at: " << startaddr << "\n";
			cout << "Device: " << device << " at " << sc_time_stamp() << " completes its exchange.\n";
			cout << "Device: " << device << " is done.\n";

			permit->unlock();

		}
		else {
			wait(delay, SC_NS);	//each device will have its own delay
			//********READING************
			cout << "Device: " << device << " at " << sc_time_stamp() << " has requested to read...\n";
			readpermit->wait();

			cout << "Device: " << device << " at " << sc_time_stamp() << " Got a read semaphore " << "\n";
			//startaddr = rand() % ADDR_SPACE;
			startaddr = device * 100;
			
			numreadbytes = rand() % 63;
			for (i = 0; i < numreadbytes; i++) {
				addr = (sc_lv<ADDRESS>)(startaddr + i);
				cs = (sc_logic)'1';
				rwbar = (sc_logic)'1';
				wait(1, SC_NS);	//delay 1 sec to let var propagate
				cout << "Device: " << device << " at " << sc_time_stamp() << " READ from memory ADDR:  "<< addr<< " DATA: " << dataout << endl;

				wait(delay, SC_NS);
			}

			cs = (sc_logic)'Z';
			rwbar = (sc_logic)'Z';

			readpermit->post();
		}

	}
}
