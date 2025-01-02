#include <iostream>
#include <queue>
#include <time.h>
#include <array>

class Task {
private:
	std::string m_name;
	int m_duration;
	int m_priority;

public:
	Task(std::string name, int duration, int priority)
		: m_name(name),m_duration(duration),m_priority(priority) {}

	void printTask() {
		std::cout << "Name: " << m_name << "\n";
		std::cout << "Duration: " << m_duration << "\n";
		std::cout << "Priority: " << m_priority << "\n";
	}

	bool operator < (const Task& t) const {
		if (m_priority == t.m_priority)
			return m_duration < t.m_duration;
		return m_priority < t.m_priority;
	}

	int getDuration() {
		return m_duration;
	}

	int getPriority() {
		return m_priority;
	}

	std::string getName() {
		return m_name;
	}
};

Task generateRandTasks() {
	// Durata : [0,20]
	// Prioritate : [0,5]
	// Nume :


	std::array<std::string, 5> commands = { "comanda noua", "rezolva corespondenta", "livreaza intern", "livreaza extern", "calculeaza plati" };
	std::string name = commands[rand() % commands.size()];

	int duration = rand() % 21;
	int priority = rand() % 6;

	Task newTask = Task(name, duration, priority);
	return newTask;
}

int main() {
	srand(time(NULL));
	std::priority_queue<Task> priorityQueue;
	for (int i = 0; i < 4; i++) {
		Task randomTask = generateRandTasks();
		priorityQueue.push(randomTask);
	}

	while (!priorityQueue.empty()) {
		Task task = priorityQueue.top();
		task.printTask();
		priorityQueue.pop();
	}
	return 0;
}