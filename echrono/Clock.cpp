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

#include <etk/typeInfo.hpp>
ETK_DECLARE_TYPE(echrono::Clock);

echrono::Clock::Clock() :
  m_data(0) {
	
}

echrono::Clock::Clock(int64_t _valNano) :
  m_data(_valNano) {
	
}

echrono::Clock::Clock(int64_t _valSec, int32_t _valNano) :
  m_data(_valSec*1000000000LL +_valNano) {
	
}

echrono::Clock::Clock(const echrono::Clock& _val):
  m_data(_val.m_data) {
	
}

echrono::Clock::Clock(const echrono::Steady& _val) {
	m_data = _val.get();
}

echrono::Clock echrono::Clock::now() {
	return echrono::Clock(echrono::Steady::now());
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
	m_data += _obj.get();
	return *this;
}

echrono::Clock echrono::Clock::operator+ (const echrono::Duration& _obj) const {
	echrono::Clock tmp(m_data);
	tmp += _obj;
	return tmp;
}

const echrono::Clock& echrono::Clock::operator-= (const echrono::Duration& _obj) {
	m_data -= _obj.get();
	return *this;
}

echrono::Clock echrono::Clock::operator- (const echrono::Duration& _obj) const {
	echrono::Clock tmp(m_data);
	tmp -= _obj;
	return tmp;
}

echrono::Duration echrono::Clock::operator- (const echrono::Clock& _obj) const {
	return _obj.m_data - m_data;
}

void echrono::Clock::reset() {
	m_data = 0;
}

etk::Stream& echrono::operator <<(etk::Stream& _os, const echrono::Clock& _obj) {
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
		return etk::toString(_obj.get());
	}
	template<> etk::UString toUString<echrono::Clock>(const echrono::Clock& _obj) {
		return etk::toUString(_obj.get());
	}
}
