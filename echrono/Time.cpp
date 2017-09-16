/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <echrono/Time.hpp>
#include <echrono/Duration.hpp>
#include <echrono/debug.hpp>
#include <etk/UString.hpp>
#include <etk/stdTools.hpp>
extern "C" {
	#include <time.h>
}
#include <etk/typeInfo.hpp>
ETK_DECLARE_TYPE(echrono::Time);

static int64_t getTime() {
	#if defined(__TARGET_OS__Android)
		struct timevalnow;
		gettimeofday(&now, nullptr);
		return int64_t(now.tv_sec)*1000000000LL + int64_t(now.tv_usec)*1000LL;
	#elif    defined(__TARGET_OS__Web) \
	      || defined(__TARGET_OS__Linux) \
	      || defined(__TARGET_OS__buildroot) \
	      || defined(__TARGET_OS__MacOs) \
	      || defined(__TARGET_OS__IOs)
		struct timespec now;
		int ret = clock_gettime(CLOCK_REALTIME, &now);
		if (ret != 0) {
			// Error to get the time ...
			now.tv_sec = time(nullptr);
			now.tv_nsec = 0;
		}
		return int64_t(now.tv_sec)*1000000000LL + int64_t(now.tv_nsec);
	#else
		#error must be implemented ...
	#endif
	return 0;
}

echrono::Time::Time() :
  m_data(0) {
	
}

echrono::Time::Time(int64_t _valNano) :
  m_data(_valNano) {
	
}

echrono::Time::Time(int64_t _valSec, int32_t _valNano) :
  m_data(_valSec*1000000000LL +_valNano) {
	
}

echrono::Time::Time(const echrono::Time& _val) {
	m_data = _val.m_data;
}

echrono::Time echrono::Time::now() {
	return echrono::Time(getTime());
}

const echrono::Time& echrono::Time::operator= (const echrono::Time& _obj) {
	m_data = _obj.m_data;
	return *this;
}

bool echrono::Time::operator== (const echrono::Time& _obj) const {
	return m_data == _obj.m_data;
}

bool echrono::Time::operator!= (const echrono::Time& _obj) const {
	return m_data != _obj.m_data;
}

bool echrono::Time::operator< (const echrono::Time& _obj) const {
	return m_data < _obj.m_data;
}

bool echrono::Time::operator<= (const echrono::Time& _obj) const {
	return m_data <= _obj.m_data;
}

bool echrono::Time::operator> (const echrono::Time& _obj) const {
	return m_data > _obj.m_data;
}

bool echrono::Time::operator>= (const echrono::Time& _obj) const {
	return m_data >= _obj.m_data;
}

const echrono::Time& echrono::Time::operator+= (const echrono::Duration& _obj) {
	m_data += _obj.get();
	return *this;
}

echrono::Time echrono::Time::operator+ (const echrono::Duration& _obj) const {
	echrono::Time tmp(m_data);
	tmp += _obj.get();
	return tmp;
}

const echrono::Time& echrono::Time::operator-= (const echrono::Duration& _obj) {
	m_data -= _obj.get();
	return *this;
}

echrono::Time echrono::Time::operator- (const echrono::Duration& _obj) const {
	echrono::Time tmp(m_data);
	tmp -= _obj.get();
	return tmp;
}

echrono::Duration echrono::Time::operator- (const echrono::Time& _obj) const {
	return echrono::Duration(int64_t(m_data - _obj.m_data));
}

void echrono::Time::reset() {
	m_data = 0;
}


etk::Stream& echrono::operator <<(etk::Stream& _os, const echrono::Time& _obj) {
	int64_t ns = _obj.get();
	int64_t totalSecond = ns/1000000000;
	int64_t millisecond = (ns%1000000000)/1000000;
	int64_t microsecond = (ns%1000000)/1000;
	int64_t nanosecond = ns%1000;
	//_os << totalSecond << "s " << millisecond << "ms " << microsecond << "µs " << nanosecond << "ns";
	int32_t second = totalSecond % 60;
	int32_t minute = (totalSecond/60)%60;
	int32_t hour = (totalSecond/3600)%24;
	int32_t day = (totalSecond/(24*3600))%365;
	int32_t year = totalSecond/(24*3600*365) + 1970;
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
	template<> etk::String toString<echrono::Time>(const echrono::Time& _obj) {
		return etk::toString(_obj.get());
	}
	template<> etk::UString toUString<echrono::Time>(const echrono::Time& _obj) {
		return etk::toUString(_obj.get());
	}
}

