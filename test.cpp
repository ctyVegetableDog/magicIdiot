#include <thread>
#include <string>
#include <iostream>
#include <mutex>
#include <list>

class MyTest{
	public:
		MyTest () {}
		void sendMsg() {
			for (int i = 0; i < 10000; ++i) {
				myList.push_back("newMsg");
				myMutex.lock();
				std::cout<<i<<std::endl;
				myMutex.unlock();
			}
		}
		void recvMsg() {
			for (int i = 0 ; i < 10000; ++i) {
				myMutex.lock();
				if (myList.empty()) {
					std::cout << "Queue is empty" << std::endl;
				}
				else {
					std::cout << myList.front() <<std::endl;
					myList.pop_front();
				}
				myMutex.unlock();
			}
		}

	private:
		std::list<std::string> myList;
		std::mutex myMutex;
};

int main()
{
	MyTest testObj;
	std::thread sendThread(&MyTest::sendMsg, std::ref(testObj)), recvThread(&MyTest::recvMsg, std::ref(testObj));
	
	sendThread.join();
	recvThread.join();
	return 0;
}
