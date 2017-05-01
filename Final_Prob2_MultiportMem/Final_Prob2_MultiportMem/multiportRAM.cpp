// classes example
#include <systemc.h>
#include <iostream>
#include <time.h>
using namespace std;


/*
class Rectangle {
	int width, height;
public:
	void set_values(int, int);
	int area() { return width*height; }
};

void Rectangle::set_values(int x, int y) {
	width = x;
	height = y;
}

int main() {
	Rectangle rect;
	rect.set_values(3, 4);
	cout << "area: " << rect.area() << endl;
	return 0;
}
*/

/*
//BEGIN MY CODE.....
class multiportRAM {
	int addr, data;

	//sc_semaphore read_ports(3);
	sc_mutex write_port;

public:
	//void readmem(int addr, int& data);
	//void writemem(int addr, const int& data);
	void writemem(int addr, int data);
	void readmem();
};

void multiportRAM::writemem(int a, int d) {
	addr = a;
	data = d;
}

void multiportRAM :: readmem(void) {
	cout << "ADDR is " << addr << endl;
	cout << "DATA is " << data << endl;
}


int main() {
	multiportRAM mltram;
	mltram.writemem(3, 4);
	//cout << "area: " << mltram.area() << endl;
	mltram.readmem();
	return 0;
}
*/


//*****************SEMAPHORE*********************************
SC_MODULE(sc_semaphore_example) {
	sc_in<bool> clock;

	sc_semaphore   bus;
	int     cnt;



	void bus_semaphore() {
		const char* name = sc_core::sc_get_current_process_b()->get_parent()->basename();
		while (true) {
			srand(time(NULL));
			wait(rand() % 10, SC_NS);
			cout << "@" << sc_time_stamp() << " P_"<< name << " Check if semaphore is 0 " << endl;

			if (bus.get_value() == 0) {
				cout << "@" << sc_time_stamp() << " P_" << name << " Posting 2 to semaphore " << endl;
				bus.post();
				bus.post();
				if (cnt >= 3) {
					sc_stop(); // sc_stop triggers end of simulation
				}
				cnt++;
			}
		}
	}

	void do_read() {
		const char* name = sc_core::sc_get_current_process_b()->get_parent()->basename();
		while (true) {
			srand(time(NULL));
			wait(rand() % 10, SC_NS);
			cout << "@" << sc_time_stamp() << " P_" << name << "  Checking semaphore for intance 0" << endl;
			// Check if semaphore is available
			if (bus.trywait() != -1) {
				cout << "@" << sc_time_stamp() << " P_" << name << "  Got semaphore for intance 0" << endl;
				wait(rand() % 10, SC_NS);
			}
		}
	}

	void do_write() {
		const char* name = sc_core::sc_get_current_process_b()->get_parent()->basename();
		while (true) {
			srand(time(NULL));
			wait(rand() % 10, SC_NS);
			cout << "@" << sc_time_stamp() << " P_" << name << "  Checking semaphore for intance 1" << endl;
			// Wait till semaphore is available
			wait(rand() % 10, SC_NS);
			cout << "@" << sc_time_stamp() << " P_" << name << "  Got semaphore for intance 1" << endl;
			wait(3);
		}
	}

	SC_CTOR(sc_semaphore_example) : bus(3) {
		cnt = 0;
		SC_CTHREAD(do_read, clock.pos());
		SC_CTHREAD(do_write, clock.pos());
		SC_CTHREAD(bus_semaphore, clock.pos());
	}
};

//*********************MUTEX*********************************
SC_MODULE(sc_mutex_example) {
	sc_in<bool> clock;

	sc_mutex   bus;
	int     cnt;


	void do_bus(int who) {
		const char* name = sc_core::sc_get_current_process_b()->get_parent()->basename();
		cout << "@" << sc_time_stamp() << " P_" << name << "  Bus access by instance " << who << endl;
	}

	void do_test1() {
		while (true) {
			const char* name = sc_core::sc_get_current_process_b()->get_parent()->basename();
			srand(time(NULL));
			srand(time(NULL));
			wait(rand()%10, SC_NS);
			//wait();
			cout << "@" << sc_time_stamp() << " P_" << name << "  Checking mutex intance 0" << endl;
			// Check if mutex is available
			if (bus.trylock() != -1) {
				cout << "@" << sc_time_stamp() << " P_" << name << "  Got mutex for intance 0" << endl;
				cnt++;
				do_bus(0);
				srand(time(NULL));
				wait(rand() % 10, SC_NS);
				// Unlock the mutex
				bus.unlock();
			}
			if (cnt >= 3) {
				cout << "done due to semaphore" << endl;
				sc_stop(); // sc_stop triggers end of simulation
			}
		}
	}

	void do_test2() {
		const char* name = sc_core::sc_get_current_process_b()->get_parent()->basename();
		while (true) {
			srand(time(NULL));
			wait(rand() % 10, SC_NS);
			cout << "@" << sc_time_stamp() << " P_" << name << "  Checking mutex intance 1" << endl;
			// Wait till mutex is available
			bus.lock();
			cout << "@" << sc_time_stamp() << " P_" << name << "  Got mutex for intance 1" << endl;
			do_bus(1);
			srand(time(NULL));
			wait(rand() % 10, SC_NS);
			// Unlock the mutex
			bus.unlock();
		}
	}

	SC_CTOR(sc_mutex_example) {
		cnt = 0;
		SC_CTHREAD(do_test1, clock.pos());
		SC_CTHREAD(do_test2, clock.pos());
	}
};


//*********************MAIN***********************************

int sc_main(int argc, char* argv[]) {
	sc_clock clock("my_clock", 1, 0.5);

	//wait(rand() % 10, SC_NS);
	sc_semaphore_example  object1("semaphore1");
	object1.clock(clock);
	sc_semaphore_example  object3("semaphore2");
	object3.clock(clock);

	sc_semaphore_example  object4("semaphore3");
	object4.clock(clock);
	sc_semaphore_example  object5("semaphore4");
	object5.clock(clock);

	//wait(rand() % 10, SC_NS);
	sc_mutex_example  object2("mutex");
	object2.clock(clock);

	sc_start(); // First time called will init schedular
	sc_start();  // Run the simulation till sc_stop is encountered
	return 0;// Terminate simulation
}