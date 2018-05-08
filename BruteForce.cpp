#include <iostream>
#include <time.h>
#include <string>
#include <cstring>
#include <random>
#include "sha256.h"

using namespace std;

class bruteforce {
	int m_min = 0, m_max = 0;
	string m_RealyPass;
public:
	void set(string RealyPass) {
		m_RealyPass = RealyPass;
		int IntRealyPass = stoi(RealyPass);
		int min, max = 0;
		if (IntRealyPass < 0) {
			//For increase the probabilities :D
			min = IntRealyPass - 1000;
			max = IntRealyPass - ((IntRealyPass * 2) * 50);
			m_min = min;
			m_max = max;
		}
		else {
			m_min = 0;
			m_max = IntRealyPass;
		}
		cout << "Max = " << m_max << " Min = " << m_min << "\n";
	}

	int returnRandom() {
		random_device rd;
		mt19937 gen(rd());
		uniform_int_distribution<> dis(m_min, m_max);
		return dis(gen);
	}

	bool CheckPass(string RealyPass, string password) {
		if (sha256(RealyPass) == sha256(password)) {
			return true;
		}
		return false;
	}

	inline int returnMax() {
		return m_max;
	}

	inline int returnMin() {
		return m_min;
	}

	inline string GetRealyPasswordHash(){
		return sha256(m_RealyPass);
	}

	inline string GetHash(string str) {
		return sha256(str);
	}
};
int main()
{
	bruteforce obj;

	string RealyPass;
	cout << "Enter Your Secret Password (i don't use your password in this program . i just use our guess !):";
	getline(cin, RealyPass);

	obj.set(RealyPass);

	cout << "Realy Password = " <<obj.GetRealyPasswordHash()<<"->"<< RealyPass << "\n";
	bool status = false;
	do {
		string rand = to_string(obj.returnRandom());
		status = obj.CheckPass(RealyPass, rand);

		cout << obj.GetHash(rand) <<"="<< rand <<"->"<< status << "\n";

		if (status) {
			cout << "Password is " << obj.GetHash(rand) <<"="<< rand << "\n";
		}
	} while (!status);
	getchar();
    return 0;
}

