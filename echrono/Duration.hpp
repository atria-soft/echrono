/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>
#include <chrono>

namespace echrono {
	using nanoseconds = std::chrono::nanoseconds;
	using microseconds = std::chrono::microseconds;
	using milliseconds = std::chrono::milliseconds;
	using seconds = std::chrono::seconds;
	
	class Duration {
		private:
			echrono::nanoseconds m_data;
		public:
			Duration();
			Duration(int _val); //value in nanosecond
			Duration(int64_t _val); //value in nanosecond
			Duration(int64_t _valSec, int64_t _valNano); //value in second and nanosecond
			Duration(double _val); //value in second
			Duration(echrono::nanoseconds _val);
			Duration(echrono::microseconds _val);
			Duration(echrono::milliseconds _val);
			Duration(echrono::seconds _val);
			~Duration() { };
			int64_t count() const;
			const echrono::nanoseconds& get() const {
				return m_data;
			}
			const Duration& operator= (const Duration& _obj);
			bool operator== (const Duration& _obj) const;
			bool operator!= (const Duration& _obj) const;
			bool operator< (const echrono::Duration& _obj) const;
			bool operator<= (const echrono::Duration& _obj) const;
			bool operator> (const echrono::Duration& _obj) const;
			bool operator>= (const echrono::Duration& _obj) const;
			Duration operator/ (float _value) const;
			const Duration& operator/= (float _value);
			Duration operator* (float _value) const;
			const Duration& operator*= (float _value);
			const Duration& operator+= (const Duration& _obj);
			Duration operator+ (const Duration& _obj) const;
			const Duration& operator-= (const Duration& _obj);
			Duration operator- (const Duration& _obj) const;
			Duration& operator++();
			Duration operator++(int _unused);
			Duration& operator--();
			Duration operator--(int _unused);
			double toSeconds() const;
			void reset();
	};
	std::ostream& operator <<(std::ostream& _os, const echrono::Duration& _obj);
}

