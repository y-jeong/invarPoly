#include "job.h"
#include "debug.h"
#include <string>

JOB::~JOB() {
}

JOB::JOB() {
	job_status = false;
}

void JOB::name_in(const std::string& name) {
	jobName.assign(name);
}

std::string JOB::name() {
	return jobName;
}
