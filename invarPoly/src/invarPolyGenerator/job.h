#include <string>

class JOB {
	private:
		std::string jobName;
		bool job_status; // 0: not done, 1: done
	public:
		~JOB();
		JOB();
		void name_in(const std::string&);
		std::string name();
};
