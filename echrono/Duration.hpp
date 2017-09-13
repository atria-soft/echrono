/** @file
 * @author Edouard DUPIN 
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */
#pragma once

#include <etk/types.hpp>

namespace echrono {
	template<int64_t ECHRONO_FACTOR>
	class genericOffsetTime {
		private:
			int64_t m_duration;
		public:
			genericOffsetTime(int64_t _offsetSinceEpock=0) :
			  m_duration(_offsetSinceEpock*int64_t(ECHRONO_FACTOR)) {
				// nothing to do.
			}
			int64_t get() const {
				return m_duration;
			}
	};
	using nanoseconds = genericOffsetTime<1LL>;
	using microseconds = genericOffsetTime<1000LL>;
	using milliseconds = genericOffsetTime<1000000LL>;
	using seconds = genericOffsetTime<1000000000LL>;
	using minutes = genericOffsetTime<60000000000LL>;
	using hours = genericOffsetTime<3600000000000LL>;
	using days = genericOffsetTime<86400000000000LL>;
	
	class Duration {
		private:
			int64_t m_data;
		public:
			Duration();
			Duration(int _val); //value in nanosecond
			Duration(int64_t _val); //value in nanosecond
			Duration(int64_t _valSec, int32_t _valNano); //value in second and nanosecond
			Duration(double _val); //value in second
			template<int64_t ECHRONO_FACTOR>
			Duration(const genericOffsetTime<ECHRONO_FACTOR>& _val) {
				m_data = _val.get();
			}
			~Duration() { };
			int64_t get() const {
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
	etk::Stream& operator <<(etk::Stream& _os, const echrono::Duration& _obj);
}

