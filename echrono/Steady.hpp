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
	 * @brief Steady is a Program start time clock
	 */
	class Steady {
		private:
			std::chrono::steady_clock::time_point m_data;
		public:
			Steady();
			//Steady(const echrono::Duration& _val) {}; //value in second
			Steady(int64_t _valNano);
			Steady(int64_t _valSec, int64_t _valNano);
			Steady(const std::chrono::steady_clock::time_point& _val);
			~Steady() {};
			const std::chrono::steady_clock::time_point& get() const {
				return m_data;
			}
			static Steady now();
			const Steady& operator= (const echrono::Steady& _obj );
			bool operator== (const echrono::Steady& _obj) const;
			bool operator!= (const echrono::Steady& _obj) const;
			bool operator< (const echrono::Steady& _obj) const;
			bool operator<= (const echrono::Steady& _obj) const;
			bool operator> (const echrono::Steady& _obj) const;
			bool operator>= (const echrono::Steady& _obj) const;
			const Steady& operator+= (const echrono::Duration& _obj);
			Steady operator+ (const echrono::Duration& _obj) const;
			const Steady& operator-= (const echrono::Duration& _obj);
			Steady operator- (const echrono::Duration& _obj) const;
			Duration operator- (const echrono::Steady& _obj) const;
			void reset();
	};
	std::ostream& operator <<(std::ostream& _os, const echrono::Steady& _obj);
}

