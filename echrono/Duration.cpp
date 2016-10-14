/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */


#include <echrono/Time.hpp>
#include <echrono/Duration.hpp>
#include <echrono/debug.hpp>

echrono::Duration::Duration() {
	m_data = std::chrono::nanoseconds(0);
}

echrono::Duration::Duration(int _val) {
	m_data = std::chrono::nanoseconds(_val);
}

echrono::Duration::Duration(int64_t _valSec, int64_t _valNano) {
	m_data = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(_valSec));
	m_data += std::chrono::nanoseconds(_valNano);
}

echrono::Duration::Duration(int64_t _val) {
	m_data = std::chrono::nanoseconds(_val);
}

echrono::Duration::Duration(double _val) {
	m_data = std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::seconds(int64_t(_val)));
	m_data += std::chrono::nanoseconds(int64_t(((_val - int64_t(_val)) * 1000000000.0)));
}

echrono::Duration::Duration(echrono::nanoseconds _val) {
	m_data = std::chrono::duration_cast<std::chrono::nanoseconds>(_val);
}

echrono::Duration::Duration(echrono::microseconds _val) {
	m_data = std::chrono::duration_cast<std::chrono::nanoseconds>(_val);
}

echrono::Duration::Duration(echrono::milliseconds _val) {
	m_data = std::chrono::duration_cast<std::chrono::nanoseconds>(_val);
}

echrono::Duration::Duration(echrono::seconds _val) {
	m_data = std::chrono::duration_cast<std::chrono::nanoseconds>(_val);
}

int64_t echrono::Duration::count() const {
	return m_data.count();
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

float echrono::Duration::toSeconds() const {
	return float(double(m_data.count()) * 0.0000000001);
}

const echrono::Duration& echrono::Duration::operator/= (float _value) {
	m_data = std::chrono::nanoseconds(int64_t(double(m_data.count()) / _value));
	return *this;
}
echrono::Duration echrono::Duration::operator/ (float _value) const {
	echrono::Duration tmpp(int64_t(double(m_data.count()) / _value));
	return tmpp;
}


const echrono::Duration& echrono::Duration::operator*= (float _value) {
	m_data = std::chrono::nanoseconds(int64_t(double(m_data.count()) * _value));
	return *this;
}
echrono::Duration echrono::Duration::operator* (float _value) const {
	echrono::Duration tmpp(int64_t(double(m_data.count()) * _value));
	return tmpp;
}

const echrono::Duration& echrono::Duration::operator+= (const echrono::Duration& _obj) {
	m_data += _obj.m_data;
	return *this;
}
echrono::Duration echrono::Duration::operator+ (const echrono::Duration& _obj) const {
	echrono::Duration tmpp(m_data);
	tmpp.m_data += _obj.m_data;
	return tmpp;
}

const echrono::Duration& echrono::Duration::operator-= (const echrono::Duration& _obj) {
	m_data -= _obj.m_data;
	return *this;
}
echrono::Duration echrono::Duration::operator- (const echrono::Duration& _obj) const {
	echrono::Duration tmpp(m_data);
	tmpp.m_data -= _obj.m_data;
	return tmpp;
}

echrono::Duration& echrono::Duration::operator++() {
	m_data += std::chrono::nanoseconds(1);
	return *this;
}
echrono::Duration echrono::Duration::operator++(int _unused) {
	echrono::Duration result(m_data);
	m_data += std::chrono::nanoseconds(1);
	return result;
}
echrono::Duration& echrono::Duration::operator--() {
	m_data -= std::chrono::nanoseconds(1);
	return *this;
}
echrono::Duration echrono::Duration::operator--(int _unused) {
	m_data -= std::chrono::nanoseconds(1);
	echrono::Duration result(m_data);
	return result;
}

void echrono::Duration::reset() {
	m_data = std::chrono::nanoseconds(0);
}

std::ostream& echrono::operator <<(std::ostream& _os, const echrono::Duration& _obj) {
	int64_t totalSecond = _obj.count()/1000000000;
	int64_t millisecond = (_obj.count()%1000000000)/1000000;
	int64_t microsecond = (_obj.count()%1000000)/1000;
	int64_t nanosecond = _obj.count()%1000;
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
	template<> std::string to_string<echrono::Duration>(const echrono::Duration& _obj) {
		return etk::to_string(_obj.count());
	}
	#if __CPP_VERSION__ >= 2011
		template<> std::u32string to_u32string<echrono::Duration>(const echrono::Duration& _obj) {
			return etk::to_u32string(_obj.count());
		}
	#endif
}


