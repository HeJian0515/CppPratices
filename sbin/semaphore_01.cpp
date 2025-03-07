#include <iostream>
#include <thread>
#include <chrono>
#include <semaphore>

std::binary_semaphore
	smphSignalMainToThread{0},
	smphSignalThreadToMain{0};

void ThreadProc() {
	smphSignalMainToThread.acquire();
	std::cout << "[thread] Got the signal\n"; // 2
	using namespace std::literals;
	std::this_thread::sleep_for(3s);

	std::cout << "[thread] Send the signal\n"; // 3
	smphSignalThreadToMain.release();
}


int main() {
	std::jthread thrWorker{ThreadProc};
	std::cout << "[main] Send the signal\n"; // 1

	smphSignalMainToThread.release();

	smphSignalThreadToMain.acquire();

	std::cout << "[main] Got the signal\n"; // 4
}
