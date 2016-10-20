/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <string>
#include <etk/types.hpp>
#include <chrono>

namespace echrono {
	class Duration;
	/**
	 * @brief Represent the earth clock (if computer is synchronized)
	 */
	class Time {
		private:
			std::chrono::system_clock::time_point m_data;
		public:
			Time();
			//Time(const echrono::Duration& _val) {}; //value in second
			Time(int64_t _valNano);
			Time(int64_t _valSec, int64_t _valNano);
			Time(const std::chrono::system_clock::time_point& _val);
			~Time() {};
			const std::chrono::system_clock::time_point& get() const {
				return m_data;
			}
			/**
			 * @brief return the number od us since epoch (can be <0)
			 * @return a number un µs since epoch
			 */
			int64_t count();
			/**
			 * @brief get the current time
			 */
			static Time now();
			const Time& operator= (const echrono::Time& _obj );
			bool operator== (const echrono::Time& _obj) const;
			bool operator!= (const echrono::Time& _obj) const;
			bool operator< (const echrono::Time& _obj) const;
			bool operator<= (const echrono::Time& _obj) const;
			bool operator> (const echrono::Time& _obj) const;
			bool operator>= (const echrono::Time& _obj) const;
			const Time& operator+= (const echrono::Duration& _obj);
			Time operator+ (const echrono::Duration& _obj) const;
			const Time& operator-= (const echrono::Duration& _obj);
			Time operator- (const echrono::Duration& _obj) const;
			Duration operator- (const echrono::Time& _obj) const;
			void reset();
	};
	std::ostream& operator <<(std::ostream& _os, const echrono::Time& _obj);
}

