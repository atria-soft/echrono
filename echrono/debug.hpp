/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license APACHE v2.0 (see license file)
 */
#pragma once

#include <elog/log.hpp>

namespace echrono {
	int32_t getLogId();
};
#define ECHRONO_BASE(info,data) ELOG_BASE(echrono::getLogId(),info,data)

#define ECHRONO_PRINT(data)         ECHRONO_BASE(-1, data)
#define ECHRONO_CRITICAL(data)      ECHRONO_BASE(1, data)
#define ECHRONO_ERROR(data)         ECHRONO_BASE(2, data)
#define ECHRONO_WARNING(data)       ECHRONO_BASE(3, data)
#ifdef DEBUG
	#define ECHRONO_INFO(data)          ECHRONO_BASE(4, data)
	#define ECHRONO_DEBUG(data)         ECHRONO_BASE(5, data)
	#define ECHRONO_VERBOSE(data)       ECHRONO_BASE(6, data)
	#define ECHRONO_TODO(data)          ECHRONO_BASE(4, "TODO : " << data)
#else
	#define ECHRONO_INFO(data)          do { } while(false)
	#define ECHRONO_DEBUG(data)         do { } while(false)
	#define ECHRONO_VERBOSE(data)       do { } while(false)
	#define ECHRONO_TODO(data)          do { } while(false)
#endif

#define ECHRONO_ASSERT(cond,data) \
	do { \
		if (!(cond)) { \
			ECHRONO_CRITICAL(data); \
			assert(!#cond); \
		} \
	} while (0)

