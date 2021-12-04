#ifndef Process_H
#define Process_H

class Process {
public:
	Process();
	Process(int, int, int);
	int getProcessNum();
	int getArrival();
	int getCpuTime();
	int getStartTime();
	int getFinishingTime();
	int getturnaroundTime();
	int getWaitingTime();
	int getRemainingTime();
	void calculateTurnaroundTime();
	void calculateWaitingTime();
	void setRemainingTime(int);
	void setFinishingTime(int);
	void setStartTime(int);
	void display();
private:
	int startTime;
	int processNum;
	int arrivalTime;
	int cpuTime;
	int finishing_time;
	int turnaroundTime;
	int waitingTime;
	int remainingTime;
};
#endif
