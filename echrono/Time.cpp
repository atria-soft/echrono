/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */


#include <echrono/Time.hpp>
#include <echrono/Duration.hpp>
#include <echrono/debug.hpp>

echrono::Time::Time() {
	m_data = std::chrono::system_clock::time_point(std::chrono::seconds(0));
}

echrono::Time::Time(int64_t _valNano) {
	#if    defined(__TARGET_OS__MacOs) \
	    or defined(__TARGET_OS__IOs) \
	    or defined(__TARGET_OS__Web)
		m_data = std::chrono::system_clock::time_point(std::chrono::milliseconds(_valNano/1000));
	#else
		m_data = std::chrono::system_clock::time_point(std::chrono::nanoseconds(_valNano));
	#endif
}

echrono::Time::Time(int64_t _valSec, int64_t _valNano) {
	m_data = std::chrono::system_clock::time_point(std::chrono::seconds(_valSec));
	#if    defined(__TARGET_OS__MacOs) \
	    or defined(__TARGET_OS__IOs) \
	    or defined(__TARGET_OS__Web)
		m_data += std::chrono::milliseconds(_valNano/1000);
	#else
		m_data += std::chrono::nanoseconds(_valNano);
	#endif
}

echrono::Time::Time(const std::chrono::system_clock::time_point& _val) {
	m_data = _val;
}

echrono::Time echrono::Time::now() {
	return echrono::Time(std::chrono::system_clock::now());
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
	#if    defined(__TARGET_OS__MacOs) \
	    || defined(__TARGET_OS__IOs) \
	    || defined(__TARGET_OS__Web)
		std::chrono::microseconds ms = std::chrono::duration_cast<std::chrono::microseconds>(_obj.get());
		m_data += ms;
	#else
		m_data += _obj.get();
	#endif
	return *this;
}

echrono::Time echrono::Time::operator+ (const echrono::Duration& _obj) const {
	echrono::Time time(m_data);
	time += _obj;
	return time;
}

const echrono::Time& echrono::Time::operator-= (const echrono::Duration& _obj) {
	#if    defined(__TARGET_OS__MacOs) \
	    || defined(__TARGET_OS__IOs) \
	    || defined(__TARGET_OS__Web)
		std::chrono::microseconds ms = std::chrono::duration_cast<std::chrono::microseconds>(_obj.get());
		m_data -= ms;
	#else
		m_data -= _obj.get();
	#endif
	return *this;
}

echrono::Time echrono::Time::operator- (const echrono::Duration& _obj) const {
	echrono::Time time(m_data);
	time -= _obj;
	return time;
}

echrono::Duration echrono::Time::operator- (const echrono::Time& _obj) const {
	std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(m_data.time_since_epoch());
	std::chrono::nanoseconds ns2 = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.m_data.time_since_epoch());
	echrono::Duration duration(ns);
	echrono::Duration duration2(ns2);
	return duration - duration2;
}

void echrono::Time::reset() {
	m_data = std::chrono::system_clock::time_point(std::chrono::seconds(0));
}

int64_t echrono::Time::count() {
	std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(m_data.time_since_epoch());
	return ns.count()/1000;
}

std::ostream& echrono::operator <<(std::ostream& _os, const echrono::Time& _obj) {
	/*
	std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.get().time_since_epoch());
	int64_t totalSecond = ns.count()/1000000000;
	int64_t millisecond = (ns.count()%1000000000)/1000000;
	int64_t microsecond = (ns.count()%1000000)/1000;
	int64_t nanosecond = ns.count()%1000;
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
	*/
	std::time_t now_c = std::chrono::system_clock::to_time_t(_obj.get());
	_os << std::put_time(std::localtime(&now_c), "%F %T");
	return _os;
}


namespace etk {
	template<> std::string to_string<echrono::Time>(const echrono::Time& _obj) {
		std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.get().time_since_epoch());
		return etk::to_string(ns.count());
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<echrono::Time>(const echrono::Time& _obj) {
			std::chrono::nanoseconds ns = std::chrono::duration_cast<std::chrono::nanoseconds>(_obj.get().time_since_epoch());
			return etk::to_u32string(ns.count());
		}
	#endif
}

