/**
 * schedule.h
 *
 * Interface to the scheduler from applicat.lib.
 * Non-cosmetic changes are NOT ALLOWED.
 */
#ifndef _SCHEDULE_H_
#define _SCHEDULE_H_

class PCB;

/**
 * Thread scheduler from applicat.lib.
 */
class Scheduler {
	public:
		/**
		 * Puts a thread into the scheduler.
		 * @param pcb Thread to put
		 */
		static void put(PCB* pcb);
		/**
		 * Removes a thread from the scheduler.
		 * @returns One scheduled thread, if no thread is scheduled,
		 *          returns null
		 */
		static PCB* get();
};

#endif
