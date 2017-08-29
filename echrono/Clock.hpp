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
	class Steady;
	/**
	 * @brief Clock is a compleate virtual clock that is used to virtualize the urrent clock used (can be non real-time, ex:for simulation)
	 */
	class Clock {
		private:
			int64_t m_data;
		public:
			Clock();
			//Clock(const echrono::Duration& _val) {}; //value in second
			Clock(int64_t _valNano);
			Clock(int64_t _valSec, int32_t _valNano);
			Clock(const echrono::Clock& _val);
			Clock(const echrono::Steady& _val);
			~Clock() {};
			int64_t get() const {
				return m_data;
			}
			/**
			 * @brief return the number of us since start of clock (can be <0)
			 * @return a number un us since start of clock
			 */
			static Clock now();
			const Clock& operator= (const echrono::Clock& _obj );
			bool operator== (const echrono::Clock& _obj) const;
			bool operator!= (const echrono::Clock& _obj) const;
			bool operator< (const echrono::Clock& _obj) const;
			bool operator<= (const echrono::Clock& _obj) const;
			bool operator> (const echrono::Clock& _obj) const;
			bool operator>= (const echrono::Clock& _obj) const;
			const Clock& operator+= (const echrono::Duration& _obj);
			Clock operator+ (const echrono::Duration& _obj) const;
			const Clock& operator-= (const echrono::Duration& _obj);
			Clock operator- (const echrono::Duration& _obj) const;
			Duration operator- (const echrono::Clock& _obj) const;
			void reset();
	};
	etk::Stream& operator <<(etk::Stream& _os, const echrono::Clock& _obj);
}


#include <echrono/Duration.hpp>
