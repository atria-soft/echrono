/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/String.hpp>
#include <etk/types.hpp>

namespace echrono {
	class Duration;
	/**
	 * @brief Steady is a Program start time clock
	 */
	class Steady {
		private:
			uint64_t m_data; //!< Monotonic clock since computer star
		public:
			Steady();
			//Steady(const echrono::Duration& _val) {}; //value in second
			Steady(int64_t _valNano);
			Steady(int64_t _valSec, int32_t _valNano);
			Steady(const echrono::Steady& _obj);
			~Steady() {};
			int64_t get() const {
				return m_data;
			}
			/**
			 * @brief return the number of us since start program (can be <0)
			 * @return a number un us since start
			 */
			int64_t count();
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
	etk::Stream& operator <<(etk::Stream& _os, const echrono::Steady& _obj);
}


#include <echrono/Duration.hpp>

