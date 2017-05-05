#include <systemc.h>

#define WORD_LENGTH 8 
#define ADDRESS 10 
#define ADDR_SPACE 1024

SC_MODULE(exchanger)
{
	sc_out_rv <ADDRESS> addr;
	sc_out_rv <WORD_LENGTH> datain;
	sc_in_rv <WORD_LENGTH> dataout;
	sc_out_resolved cs, rwbar;

	sc_mutex* permit;
	sc_semaphore* readpermit;

	SC_HAS_PROCESS(exchanger);

	exchanger::exchanger (sc_module_name NAME, int NUM, int TIM) : sc_module(NAME), device(NUM), delay(TIM)    
	{
		cout << "Device: " << device << " has started.\n";
		SC_THREAD(exchanging);
	}

	void exchanging();

	private:
		int device;
		int delay;
};
