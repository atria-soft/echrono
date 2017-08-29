/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */


#include <echrono/Time.hpp>
#include <echrono/Duration.hpp>
#include <echrono/debug.hpp>
#include <etk/UString.hpp>

echrono::Duration::Duration() :
  m_data(0) {
	
}

echrono::Duration::Duration(int _val) :
  m_data(_val) {
	
}

echrono::Duration::Duration(int64_t _valSec, int32_t _valNano) :
  m_data(_valSec*1000000000LL +_valNano) {
	
}

echrono::Duration::Duration(int64_t _val) :
  m_data(_val) {
	
}

echrono::Duration::Duration(double _val) {
	m_data = int64_t(_val*1000000000.0);
}

const echrono::Duration& echrono::Duration::operator= (const echrono::Duration& _obj) {
	m_data = _obj.m_data;
	return *this;
}
bool echrono::Duration::operator== (const echrono::Duration& _obj) const {
	return _obj.m_data == m_data;
}
bool echrono::Duration::operator!= (const echrono::Duration& _obj) const {
	return _obj.m_data != m_data;
}
bool echrono::Duration::operator< (const echrono::Duration& _obj) const {
	return m_data < _obj.m_data;
}
bool echrono::Duration::operator<= (const echrono::Duration& _obj) const {
	return m_data <= _obj.m_data;
}
bool echrono::Duration::operator> (const echrono::Duration& _obj) const {
	return m_data > _obj.m_data;
}
bool echrono::Duration::operator>= (const echrono::Duration& _obj) const {
	return m_data >= _obj.m_data;
}

double echrono::Duration::toSeconds() const {
	return double(m_data) * 0.000000001;
}

const echrono::Duration& echrono::Duration::operator/= (float _value) {
	m_data = int64_t(double(m_data) / _value);
	return *this;
}
echrono::Duration echrono::Duration::operator/ (float _value) const {
	return echrono::Duration(int64_t(double(m_data) / _value));
}


const echrono::Duration& echrono::Duration::operator*= (float _value) {
	m_data = int64_t(double(m_data) * _value);
	return *this;
}
echrono::Duration echrono::Duration::operator* (float _value) const {
	return echrono::Duration(int64_t(double(m_data) * _value));
}

const echrono::Duration& echrono::Duration::operator+= (const echrono::Duration& _obj) {
	m_data += _obj.m_data;
	return *this;
}
echrono::Duration echrono::Duration::operator+ (const echrono::Duration& _obj) const {
	echrono::Duration tmp(m_data);
	tmp.m_data += _obj.m_data;
	return tmp;
}

const echrono::Duration& echrono::Duration::operator-= (const echrono::Duration& _obj) {
	m_data -= _obj.m_data;
	return *this;
}
echrono::Duration echrono::Duration::operator- (const echrono::Duration& _obj) const {
	echrono::Duration tmp(m_data);
	tmp.m_data -= _obj.m_data;
	return tmp;
}

echrono::Duration& echrono::Duration::operator++() {
	m_data++;
	return *this;
}
echrono::Duration echrono::Duration::operator++(int _unused) {
	echrono::Duration tmp(m_data);
	m_data++;
	return tmp;
}
echrono::Duration& echrono::Duration::operator--() {
	m_data -= 1;
	return *this;
}
echrono::Duration echrono::Duration::operator--(int _unused) {
	echrono::Duration tmp(m_data);
	m_data--;
	return tmp;
}

void echrono::Duration::reset() {
	m_data = 0;
}

etk::Stream& echrono::operator <<(etk::Stream& _os, const echrono::Duration& _obj) {
	int64_t totalSecond = _obj.get()/1000000000;
	int64_t millisecond = (_obj.get()%1000000000)/1000000;
	int64_t microsecond = (_obj.get()%1000000)/1000;
	int64_t nanosecond = _obj.get()%1000;
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
	template<> etk::String toString<echrono::Duration>(const echrono::Duration& _obj) {
		return etk::toString(_obj.get());
	}
	template<> etk::UString toUString<echrono::Duration>(const echrono::Duration& _obj) {
		return etk::toUString(_obj.get());
	}
}


