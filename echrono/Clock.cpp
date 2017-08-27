/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <echrono/Clock.hpp>
#include <echrono/Steady.hpp>
#include <echrono/Duration.hpp>
#include <echrono/debug.hpp>
#include <etk/UString.hpp>

echrono::Clock::Clock() {
	m_data = std::chrono::steady_clock::time_point(std::chrono::seconds(0));
}

echrono::Clock::Clock(int64_t _valNano) {
	m_data = std::chrono::steady_clock::time_point(std::chrono::nanoseconds(_valNano));
}

echrono::Clock::Clock(int64_t _valSec, int64_t _valNano) {
	m_data = std::chrono::steady_clock::time_point(std::chrono::seconds(_valSec));
	m_data += std::chrono::nanoseconds(_valNano);
}
echrono::Clock::Clock(const std::chrono::steady_clock::time_point& _val) {
	m_data = _val;
}

echrono::Clock::Clock(const echrono::Steady& _val) {
	m_data = _val.get();
}

echrono::Clock echrono::Clock::now() {
	return echrono::Clock(std::chrono::steady_clock::now());
}

const echrono::Clock& echrono::Clock::operator= (const echrono::Clock& _obj) {
	m_data = _obj.m_data;
	return *this;
}

bool echrono::Clock::operator== (const echrono::Clock& _obj) const {
	return m_data == _obj.m_data;
}

bool echrono::Clock::operator!= (const echrono::Clock& _obj) const {
	return m_data != _obj.m_data;
}

bool echrono::Clock::operator< (const echrono::Clock& _obj) const {
	return m_data < _obj.m_data;
}

bool echrono::Clock::operator<= (const echrono::Clock& _obj) const {
	return m_data <= _obj.m_data;
}

bool echrono::Clock::operator> (const echrono::Clock& _obj) const {
	return m_data > _obj.m_data;
}

bool echrono::Clock::operator>= (const echrono::Clock& _obj) const {
	return m_data >= _obj.m_data;
}

const echrono::Clock& echrono::Clock::operator+= (const echrono::Duration& _obj) {
	#if defined(__TARGET_OS__MacOs) || defined(__TARGET_OS__IOs)
		std::chrono::microseconds ms = std::chrono::duration_cast<std::chrono::microseconds>(_obj.get());
		m_data += ms;
	#else
		m_data += _obj.get();
	#endif
	return *this;
}

echrono::Clock echrono::Clock::operator+ (const echrono::Duration& _obj) const {
	echrono::Clock time(m_data);
	time += _obj;
	return time;
}

const echrono::Clock& echrono::Clock::operator-= (const echrono::Duration& _obj) {
	#if defined(__TARGET_OS__MacOs) || defined(__TARGET_OS__IOs)
		std::chrono::microseconds ms = std::chrono::duration_cast<std::chrono::microseconds>(_obj.get());
		m_data -= ms;
	#else
		m_data -= _obj.get();
	#endif
	return *this;
}

echrono::Clock echrono::Clock::operator- (const echrono::Duration& _obj) const {
	echrono::Clock time(m_data);
	time -= _obj;
	return time;
}

echrono::Duration echrono::Clock::operator- (const echrono::Clock& _obj) const {
	std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(m_data.time_since_epoch());
	std::chrono::nanoseconds ns2 = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.m_data.time_since_epoch());
	echrono::Duration duration(ns);
	echrono::Duration duration2(ns2);
	return duration - duration2;
}

void echrono::Clock::reset() {
	m_data = std::chrono::steady_clock::time_point(std::chrono::seconds(0));
}

int64_t echrono::Clock::count() {
	std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(m_data.time_since_epoch());
	return ns.count()/1000;
}

etk::Stream& echrono::operator <<(etk::Stream& _os, const echrono::Clock& _obj) {
	std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.get().time_since_epoch());
	int64_t totalSecond = ns.count()/1000000000;
	int64_t millisecond = (ns.count()%1000000000)/1000000;
	int64_t microsecond = (ns.count()%1000000)/1000;
	int64_t nanosecond = ns.count()%1000;
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
	template<> etk::String toString<echrono::Clock>(const echrono::Clock& _obj) {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.get().time_since_epoch());
		return etk::toString(ns.count());
	}
	#if __CPP_VERSION__ >= 2011
		template<> etk::UString toUString<echrono::Clock>(const echrono::Clock& _obj) {
			std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.get().time_since_epoch());
			return etk::toUString(ns.count());
		}
	#endif
}
