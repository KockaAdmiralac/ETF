/**
 * USER1.CPP
 *
 * Public test code.
 * Command-line arguments:
 * 1. Buffer size
 * 2. Thread number
 * 3. Producer time slice
 * @see http://os.etf.bg.ac.rs/OS1/projekat/javni_test_2021.zip
 */
#include <assert.h>
#include <dos.h>
#include <event.h>
#include <iostream.h>
#include <semaphor.h>
#include <stdlib.h>
#include <thread.h>

/**
 * Default test parameters.
 */
Time TIME_SLICE = 2;
// 1 <= N <= 19
int N = 19;

// End flag for the producer.
volatile int theEnd = 0;

/**
 * intLock
 */
#define intLock mutex_glb_wait();
#define intUnlock mutex_glb = 1;

int mutex_glb = 1;

void mutex_glb_wait() {
	sloop:asm{
		mov ax, 0
		xchg ax, mutex_glb 	
	}
	if (_AX == 0) {
		dispatch();
		asm jmp sloop;
	}
}

/**
 * Representation of a bounded buffer.
 */
class BoundedBuffer {
	public:
		BoundedBuffer(unsigned size);
		virtual ~BoundedBuffer();
		int append(char);
		char take();
		/**
		 * Used by consumer.
		 */
		int fullCount() {
			return itemAvailable.val();
		}
	private:
		unsigned size;
		Semaphore mutexa, mutext;
		Semaphore spaceAvailable, itemAvailable;
		char* buffer;
		int head, tail;
};

/**
 * Constructs a bounded buffer of a specified size.
 * @param size Size of the bounded buffer
 */
BoundedBuffer::BoundedBuffer(unsigned size) : size(size), mutexa(1), mutext(1),
	spaceAvailable(size), itemAvailable(0), head(0), tail(0) {
	buffer = new char[size];
	if (!buffer) {
		exit(1);
	}
}

/**
 * Frees resources used by the buffer.
 */
BoundedBuffer::~BoundedBuffer() {
	intLock
	delete[] buffer;
	intUnlock
}

/**
 * Appends a character to the buffer.
 * @param d Character to append
 * @returns Zero on success
 */
int BoundedBuffer::append(char d) {
	spaceAvailable.wait(0);
	mutexa.wait(0);
	buffer[tail] = d;
	tail = (tail + 1) % size;
	mutexa.signal();
	itemAvailable.signal();
	return 0;
}

/**
 * Takes a character from the buffer.
 * @returns The character that was taken.
 */
char BoundedBuffer::take() {
	itemAvailable.wait(0);
	mutext.wait(0);
	char d = buffer[head];
	head = (head+1) % size;
	mutext.signal();
	spaceAvailable.signal();
	return d;
}

/**
 * Class representing a character producer.
 */
class Producer : public Thread {
	public:
		Producer(BoundedBuffer* bb, char y, Time timeSlice);
		virtual ~Producer() {
			waitToComplete();
		}
		Thread* clone() const {
			return new Producer(myBuffer, x, timeSliceClone);
		}
	protected:
		virtual void run ();
		char produce() {
			return x;
		}
	private:
		Time timeSliceClone;
		BoundedBuffer* myBuffer;
		char x;
		Semaphore sleep;
};

/**
 * Class representing a character consumer.
 */
class Consumer : public Thread {
	public:
		Consumer(BoundedBuffer* bb) : Thread(defaultStackSize, 0),
			myBuffer(bb), sleep(0) {}
		virtual ~Consumer() {
			waitToComplete();
		}
		Thread* clone() const {
			return new Consumer(myBuffer);
		}
	protected:
		virtual void run();
		void consume(char p);
	private:
		BoundedBuffer* myBuffer;
		Semaphore sleep;
};

Producer::Producer (BoundedBuffer* bb, char y, Time timeSlice)  :
	Thread(defaultStackSize, timeSlice), myBuffer(bb), x(y), sleep(0),
	timeSliceClone(timeSlice) {}

void Producer::run () {
	while (!theEnd) {
		char d = produce();
		myBuffer->append(d);
		assert(1 != sleep.wait(10));
	}
}

void Consumer::consume(char p) {
	intLock
	cout << p << " ";
	intUnlock
}

void Consumer::run () {
	int i = 0;
	while (!theEnd) {
		char d = myBuffer->take();
		consume(d);
		if (i++ == 40) {
			assert(1 != sleep.wait(5));
			i = 0;
		} else {
			for (int j = 0; j < 200; j++);
		}
	}
	intLock
	cout << endl << "ESC pressed - empty the buffer!" << endl;
	intUnlock
	while (myBuffer->fullCount()) {
		char d = myBuffer->take();
		consume(d);
		dispatch();
	}
	intLock
	cout << endl << "Happy End" << endl;
	intUnlock
}

PREPAREENTRY(9, 0);

/**
 * Incomplete QWERTY keyboard mapping.
 */
char keymap[128] = {	0 , 27,'1','2','3','4','5','6','7','8','9','0','-','=', 8 , 9,
	'q','w','e','r','t','y','u','i','o','p','[',']', 13, 0 ,'a','s',
	'd','f','g','h','j','k','l',';',0,0,'`','\\','z','x','c','v','b',
	'n','m',',','.','/', 0 ,'*', 0 ,' '
};

/**
 * Listens for keyboard events and feeds them into a bounded buffer.
 */
class KeyboardEvent : public Thread{
	public:
		KeyboardEvent(BoundedBuffer*);		virtual ~KeyboardEvent() {
			waitToComplete();
		}
		Thread* clone() const {
			return new KeyboardEvent(myBuffer);
		}
	protected:
		virtual void run();
		char znak;
	private:
		BoundedBuffer* myBuffer;
};

KeyboardEvent::KeyboardEvent(BoundedBuffer* bb) : Thread(), myBuffer(bb) {
	theEnd = 0;
}

/**
 * Listens for keyboard interrupts on entry 9h.
 *
 * To understand the procedure below, it is important to understand what
 * certain IO registers are for:
 * - Port 20h: Master Programmable Interrupt Controller register for the EOI
 *   signal
 * - Port 60h: Controller data port - should be read after status0 = 1
 * - Port 61h: Keyboard controller port B: bit7 = pulse to 1 for IRQ1 reset
 * - Port 64h: Status register (when read)
 * @see https://fd.lod.bz/rbil/ports/keyboard/p0060006f.html#table-P0392
 */
void KeyboardEvent::run() {
	intLock
	Event event9(9);
	cout << "KeyboardListener started!" << endl;
	intUnlock
	char scancode, status;
	while (!theEnd) {
		event9.wait();
		do {
			status = inportb(0x64);
			if (status & 0x01) {
				scancode = inportb(0x60);
				if (scancode == -127) {
					theEnd = 1;
					myBuffer->append('!');
				} else {
					if (scancode & 0x80) {
						myBuffer->append(keymap[scancode&0x7F]);
					}
				}
			}
			asm{
				cli
				in      al, 61h         //; Send acknowledgment without
				or      al, 10000000b   //;   modifying the other bits.
				out     61h, al         //;
				and     al, 01111111b   //;
				out     61h, al         //;
				mov     al, 20h         //; Send End-of-Interrupt signal
				out     20h, al         //;
				sti
			}
		} while (!theEnd && status & 0x01);
	}
	intLock
	cout << endl << "KeyebordListener stopped!" << endl;
	intUnlock
}

void tick() {}

int userMain(int argc, char* argv[]) {
	BoundedBuffer *buff;
	Consumer *con;
	intLock
	if (argc < 2) {
		cout << "Invalid input!" << endl;
		intUnlock
		return -1;
	}
	int buffSize = atoi(argv[1]);
	N = atoi(argv[2]);
	N = N > 19 ? 19 : N;
	TIME_SLICE = atoi(argv[3]);	
	if (buffSize < N) {
		cout << "Number of Produsers is larger then Buffer size!" << endl;
		intUnlock
		return 1;
	}
	buff = new BoundedBuffer(buffSize);
	Producer **pro = new Producer*[N];
	KeyboardEvent* kev;
	int i;
	con = new Consumer(buff);
	con->start();
	for (i = 0; i < N; i++) {
		pro[i] = new Producer(buff, '0' + i, TIME_SLICE);
		pro[i]->start();
	}
	kev = new KeyboardEvent(buff);
	intUnlock
	kev->start();
	for (i = 0; i < N; i++) {
		delete pro[i];
	}
	delete[] pro;
	delete kev;
	delete con;
	delete buff;
	const int value = 5;
	int data = 0, *pData = &data;
	ID result = Thread::fork();
	if (result != -1) {
		if (result == 0) {
			intLock
			cout << "Child created!" << endl;
			intUnlock
			*pData = value;
			data = value + 1;
			intLock
			cout << "Child finished!" << endl;
			intUnlock
			Thread::exit();
		} else {
			Thread::waitForForkChildren();
			assert(value == data);
		}
	}
	assert(result > 0);
	intLock
	cout << "userMain finished!" << endl;
	intUnlock
	return 0;
}
