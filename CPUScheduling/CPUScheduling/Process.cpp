#include "Process.h"
#include<iostream>
using namespace std;

Process::Process() {
	processNum = 0;
	arrivalTime = 0;
	cpuTime = 0;
	startTime = 0;
	finishing_time = 0;
	turnaroundTime = 0;
	waitingTime = 0;
	remainingTime = 0;
}

Process::Process(int process, int arrival, int cpu) {
	processNum = process;
	arrivalTime = arrival;
	cpuTime = cpu;
	startTime = 0;
	finishing_time = 0;
	turnaroundTime = 0;
	waitingTime = 0;
	remainingTime = 0;
}

int Process::getProcessNum() {
	return processNum;
}

int Process::getArrival() {
	return arrivalTime;
}

int Process::getCpuTime() {
	return cpuTime;
}

int Process::getFinishingTime() {
	return finishing_time;
}

int Process::getturnaroundTime() {
	return turnaroundTime;
}

int Process::getWaitingTime() {
	return waitingTime;
}

int Process::getRemainingTime() {
	return remainingTime;
}

void Process::calculateTurnaroundTime() {
	turnaroundTime = finishing_time - arrivalTime;
}

void Process::calculateWaitingTime() {
	waitingTime = turnaroundTime - cpuTime;
}

void Process::setFinishingTime(int finishing) {
	finishing_time = finishing;
}

void Process::setRemainingTime(int remaining) {
	remainingTime = remaining;
}

void Process::display() {
	cout << "Process " << processNum << ":" << endl;
	cout << "Service time = " << cpuTime << endl;
	cout << "Turnaround time = " << turnaroundTime << endl;
}

int Process::getStartTime() {
	return startTime;
}

void Process::setStartTime(int start) {
	startTime = start;
}