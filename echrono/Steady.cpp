/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <echrono/Steady.hpp>
#include <echrono/Duration.hpp>
#include <echrono/debug.hpp>
#include <etk/UString.hpp>
#include <time.h>

static int64_t getTime() {
	#if defined(__TARGET_OS__Android)
		struct timevalnow;
		gettimeofday(&now, nullptr);
		return int64_t(now.tv_sec)*1000000LL + int64_t(now.tv_usec);
	#elif    defined(__TARGET_OS__Web) \
	      || defined(__TARGET_OS__Linux) \
	      || defined(__TARGET_OS__buildroot)
		struct timespec now;
		int ret = clock_gettime(CLOCK_UPTIME_RAW, &now);
		if (ret != 0) {
			// Error to get the time ...
			now.tv_sec = time(nullptr);
			now.tv_nsec = 0;
		}
		m_data = int64_t(now.tv_sec)*1000000LL + int64_t(now.tv_nsec)/1000LL;
	#elif    defined(__TARGET_OS__MacOs) \
	      || defined(__TARGET_OS__IOs)
		struct timespec now;
		clock_serv_t cclock;
		mach_timespec_t mts;
		host_get_clock_service(mach_host_self(), REALTIME_CLOCK, &cclock);
		clock_get_time(cclock, &mts);
		mach_port_deallocate(mach_task_self(), cclock);
		now.tv_sec = mts.tv_sec;
		now.tv_nsec = mts.tv_nsec;
		return int64_t(now.tv_sec)*1000000LL + int64_t(now.tv_nsec)/1000LL;
	#else
		#error must be implemented ...
	#endif
	return 0;
}

echrono::Steady::Steady() :
  m_data(0) {
	
}

echrono::Steady::Steady(int64_t _valNano) {
	m_data = std::chrono::steady_clock::time_point(std::chrono::nanoseconds(_valNano));
}

echrono::Steady::Steady(int64_t _valSec, int64_t _valNano) :
  m_data(_valSec*1000000000LL +_valNano) {
	
}

echrono::Steady::Steady(const std::chrono::steady_clock::time_point& _val) {
	m_data = _val;
}

echrono::Steady echrono::Steady::now() {
	return echrono::Steady(std::chrono::steady_clock::now());
}

const echrono::Steady& echrono::Steady::operator= (const echrono::Steady& _obj) {
	m_data = _obj.m_data;
	return *this;
}

bool echrono::Steady::operator== (const echrono::Steady& _obj) const {
	return m_data == _obj.m_data;
}

bool echrono::Steady::operator!= (const echrono::Steady& _obj) const {
	return m_data != _obj.m_data;
}

bool echrono::Steady::operator< (const echrono::Steady& _obj) const {
	return m_data < _obj.m_data;
}

bool echrono::Steady::operator<= (const echrono::Steady& _obj) const {
	return m_data <= _obj.m_data;
}

bool echrono::Steady::operator> (const echrono::Steady& _obj) const {
	return m_data > _obj.m_data;
}

bool echrono::Steady::operator>= (const echrono::Steady& _obj) const {
	return m_data >= _obj.m_data;
}

const echrono::Steady& echrono::Steady::operator+= (const echrono::Duration& _obj) {
	m_data += _obj.get();
	return *this;
}

echrono::Steady echrono::Steady::operator+ (const echrono::Duration& _obj) const {
	echrono::Steady tmp(m_data);
	tmp += _obj;
	return tmp;
}

const echrono::Steady& echrono::Steady::operator-= (const echrono::Duration& _obj) {
	m_data -= _obj.get();
	return *this;
}

echrono::Steady echrono::Steady::operator- (const echrono::Duration& _obj) const {
	echrono::Steady tmp(m_data);
	tmp -= _obj;
	return tmp;
}

echrono::Duration echrono::Steady::operator- (const echrono::Steady& _obj) const {
	return m_data - _obj.m_data;
}

void echrono::Steady::reset() {
	m_data = 0;
}

etk::Stream& echrono::operator <<(etk::Stream& _os, const echrono::Steady& _obj) {
	int64_t ns = obj.get();
	int64_t totalSecond = ns/1000000000;
	int64_t millisecond = (ns%1000000000)/1000000;
	int64_t microsecond = (ns%1000000)/1000;
	int64_t nanosecond = ns%1000;
	//_os << totalSecond << "s " << millisecond << "ms " << microsecond << "�s " << nanosecond << "ns";
	int32_t second = totalSecond % 60;
	int32_t minute = (totalSecond/60)%60;
	int32_t hour = (totalSecond/3600)%24;
	int32_t day = (totalSecond/(24*3600))%365;
	int32_t year = totalSecond/(24*3600*365);
	bool start = false;
	if (year != 0) {
		start = true;
		_os << year << "y ";
	}
	if (day != 0 || start == true) {
		start = true;
		_os << day << "d ";
	}
	if (hour != 0 || start == true) {
		start = true;
		_os << hour << "h ";
	}
	if (minute != 0 || start == true) {
		start = true;
		_os << minute << ":";
	}
	if (second != 0 || start == true) {
		start = true;
		_os << second << "s ";
	}
	if (millisecond != 0 || start == true) {
		start = true;
		_os << millisecond << "ms ";
	}
	if (microsecond != 0 || start == true) {
		start = true;
		_os << microsecond << "us ";
	}
	_os << nanosecond << "ns ";
	return _os;
}

namespace etk {
	template<> etk::String toString<echrono::Steady>(const echrono::Steady& _obj) {
		return etk::toString(_obj.get());
	}
	template<> etk::UString toUString<echrono::Steady>(const echrono::Steady& _obj) {
		return etk::toUString(_obj.get());
	}
}
