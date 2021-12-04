#include<iostream>
#include<queue>
#include<vector>
#include<fstream>
#include<cmath>
#include"Process.h"
using namespace std;

vector<Process> FCFS(vector<Process>& process, int numProcess, double& total, int switching, double& totalSwitching) {
	int startTime = 0;
	int finishingTime = 0;
	vector<Process>cpu;
	for (int i = 0; i < process.size(); i++) {
		finishingTime = startTime + process[i].getCpuTime();
		process[i].setStartTime(startTime);
		process[i].setFinishingTime(finishingTime);
		process[i].calculateTurnaroundTime();
		process[i].calculateWaitingTime();
		cpu.push_back(process[i]);
		startTime = finishingTime + switching;
		totalSwitching += switching;
	}
	total = finishingTime;
	return cpu;
}

vector<Process> RoundRobin(vector<Process>& process, queue<Process> ready, int numProcess, double& total, int switching, double& totalSwitching, int timeInterval) {
	int startTime = 0;
	int finishingTime = 0;
	total = 0;
	totalSwitching = 0;
	int remaining = 0;
	vector<Process> cpu;
	for (int i = 0; i < process.size(); i++) {
		ready.push(process[i]);
	}
	while (!ready.empty()) {
		Process singleProcess = ready.front();
		ready.pop();
		if (singleProcess.getRemainingTime() >= timeInterval) {
			finishingTime = startTime + timeInterval;
			remaining = singleProcess.getRemainingTime() - timeInterval;
		}
		else if (singleProcess.getRemainingTime() < timeInterval && singleProcess.getRemainingTime() != 0) {
			finishingTime = startTime + singleProcess.getRemainingTime();
			remaining = 0;
		}
		else if (singleProcess.getCpuTime() >= timeInterval) {
			finishingTime = startTime + timeInterval;
			remaining = singleProcess.getCpuTime() - timeInterval;
		}
		else if (singleProcess.getCpuTime() < timeInterval) {
			finishingTime = startTime + singleProcess.getCpuTime();
			remaining = 0;
		}
		singleProcess.setStartTime(startTime);
		singleProcess.setFinishingTime(finishingTime);
		singleProcess.setRemainingTime(remaining);
		if (singleProcess.getRemainingTime() == 0) {
			singleProcess.calculateTurnaroundTime();
			singleProcess.calculateWaitingTime();
			cpu.push_back(singleProcess);
			startTime = finishingTime + switching;
			totalSwitching += switching;
			for (int j = 0; j < process.size(); j++) {
				if (singleProcess.getProcessNum() == process[j].getProcessNum()) {
					process[j] = singleProcess;
					break;
				}
			}
		}
		else {
			cpu.push_back(singleProcess);
			startTime = finishingTime + switching;
			totalSwitching += switching;
			ready.push(singleProcess);
		}
	}
	total = finishingTime;
	return cpu;
}

int main() {
	ifstream inData;
	queue<Process> readyQueue;
	int number_of_process, process_number, arrival_time, cpu_time;
	int efficiency, totalWaitingTime = 0, averageWaitingTime;
	vector<Process>cpu;
	vector<Process> processVector;
	int switchTime = 5;
	double totalSwitchingTime = 0.0, totalTime = 0.0;
	int timeQuantum[3] = { 10, 50, 100 };
	inData.open("InputScheduling.txt");
	if (!inData) {
		cout << "Error! The file does not exist!" << endl;
		return 1;
	}

	inData >> number_of_process;
	for (int i = 1; i <= number_of_process; i++) {
		inData >> process_number >> arrival_time >> cpu_time;
		Process process = Process(process_number, arrival_time, cpu_time);
		processVector.push_back(process);
	}

	cpu = FCFS(processVector, number_of_process, totalTime, switchTime, totalSwitchingTime);
	for (int j = 0; j < cpu.size(); j++) {
		totalWaitingTime += cpu[j].getWaitingTime();
	}

	averageWaitingTime = totalWaitingTime / number_of_process;
	efficiency = ceil((totalTime / (totalTime + totalSwitchingTime)) * 100);
	cout << "FCFS: " << endl;
	cout << "Total Time required is " << totalTime << " time units" << endl;
	cout << "Average waiting time is " << averageWaitingTime << " time units" << endl;
	cout << "CPU Efficiency is " << efficiency << "%" << endl;
	for (int k = 0; k < processVector.size(); k++) {
		processVector[k].display();
	}
	cout << endl;
	for (int i = 0; i < 3; i++) {
		cpu = RoundRobin(processVector, readyQueue, number_of_process, totalTime, switchTime, totalSwitchingTime, timeQuantum[i]);
		for (int j = 0; j < cpu.size(); j++) {
			totalWaitingTime += cpu[j].getWaitingTime();
		}
		averageWaitingTime = totalWaitingTime / number_of_process;
		efficiency = ceil((totalTime / (totalTime + totalSwitchingTime)) * 100);
		cout << "Roundrobin (RR) with time quanitum = " << timeQuantum[i] << ": " << endl;
		cout << "Total Time required is " << totalTime << " time units" << endl;
		cout << "Average waiting time is " << averageWaitingTime << " time units" << endl;
		cout << "CPU Efficiency is " << efficiency << "%" << endl;
		for (int k = 0; k < processVector.size(); k++) {
			processVector[k].display();
		}
		cout << endl;
	}

	system("pause");
	return 0;
}