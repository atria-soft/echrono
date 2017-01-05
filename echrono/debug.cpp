/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <echrono/debug.hpp>

int32_t echrono::getLogId() {
	static int32_t g_val = elog::registerInstance("echrono");
	return g_val;
}
