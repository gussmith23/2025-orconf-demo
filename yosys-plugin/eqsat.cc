#include "kernel/yosys.h"
#include "kernel/log.h"

YOSYS_NAMESPACE_BEGIN

struct EqsatPass : public Pass
{
  EqsatPass() : Pass("eqsat", "Run eqsat engine.") {}

  void execute(std::vector<std::string>, RTLIL::Design *design) override
  {
    log_push();
    log("Running eqsat...\n");

    // Use Churchroad to convert design to egglog commands.
    Pass::call(design, "churchroad");

    log_pop();
  }
} EqsatPass;

YOSYS_NAMESPACE_END