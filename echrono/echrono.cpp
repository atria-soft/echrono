/** @file
 * @author Edouard DUPIN
 * @copyright 2016, Edouard DUPIN, all right reserved
 * @license MPL v2.0 (see license file)
 */

#include <echrono/debug.hpp>
#include <echrono/echrono.hpp>
#include <etk/stdTools.hpp>

static int32_t g_isInit = 0;

void echrono::init(int _argc, const char** _argv) {
	if (g_isInit > 0) {
		g_isInit++;
		return;
	}
	ECHRONO_INFO("E-chrono system init");
	for (int32_t iii=0; iii<_argc ; ++iii) {
		std::string data = _argv[iii];
		if (    data == "-h"
		     || data == "--help") {
			ECHRONO_PRINT("e-chrono - help : ");
			ECHRONO_PRINT("        -h/--help:               Dispplay this help");
		} else if (etk::start_with(data, "--echrono") == true) {
			ECHRONO_ERROR("Can not parse the argument : '" << data << "'");
		}
	}
	g_isInit++;
}

void echrono::unInit() {
	if (g_isInit >= 1) {
		g_isInit--;
		return;
	}
	if (g_isInit == 1) {
		ECHRONO_INFO("E-chrono system un-init");
		g_isInit--;
		return;
	}
	ECHRONO_ERROR("E-chrono system un-init (already done before)");
}
