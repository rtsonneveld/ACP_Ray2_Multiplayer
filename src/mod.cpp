#include "mod.h"
#include "util/logging.h"

void MOD_EngineTick() {
	LOG_PollConsole();
	GAM_fn_vEngine();
}