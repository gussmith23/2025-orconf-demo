#include "kernel/yosys.h"
#include "kernel/log.h"
#include <format>

YOSYS_NAMESPACE_BEGIN

struct EqsatPass : public Pass
{
  EqsatPass() : Pass("eqsat", "Run eqsat engine.") {}

  void execute(std::vector<std::string>, RTLIL::Design *design) override
  {
    log_header(design, "Running eqsat.\n");
    log_push();

    // Use Churchroad to convert design to egglog commands.
    auto filename = "tmp.egglog";
    std::ofstream file_stream;
    file_stream.open(filename);
    Backend::backend_call(design, &file_stream, "tmp.egglog", "churchroad -salt eqsat_salt -letbindings");
    file_stream.close();

    // Check that CHURCHROAD_DIR environment variable is set.
    auto churchroad_dir = std::getenv("CHURCHROAD_DIR");
    if (churchroad_dir == nullptr)
    {
      log_cmd_error("CHURCHROAD_DIR environment variable is not set.\n");
    }

    // Run egglog on the file.
    auto output_module_name = "orconf_demo_top";
    auto tmp_output_filename = "tmp_output.sv";
    auto command = "bash -c \"cargo run --manifest-path " + std::string(churchroad_dir) + "/Cargo.toml -- orconf-demo-2025 --egglog-script " + std::string(filename) + " --output-module-name " + std::string(output_module_name) + "\" > " + std::string(tmp_output_filename);

    log("Running command: %s\n", command.c_str());
    auto result = system(command.c_str());

    if (result != 0)
    {
      log_cmd_error("Error running egglog command.\n");
    }

    // Read the output file and replace the design.
    std::ifstream output_file_stream;
    output_file_stream.open(tmp_output_filename);
    if (!output_file_stream.is_open())
    {
      log_cmd_error("Error opening output file from egglog command.\n");
    }
    std::ostringstream stringStream;
    stringStream << "read_verilog -sv " << tmp_output_filename;
    run_pass(stringStream.str());
    output_file_stream.close();

    auto top_module_name = design->top_module()->name.str();
    log("Replacing module %s with the output of eqsat\n", top_module_name.c_str());
    design->remove(design->top_module());
    auto new_module = design->module(RTLIL::escape_id(output_module_name));
    if (new_module == nullptr)
      log_error("eqsat returned OK, but no module named %s found.\n", top_module_name.c_str());
    design->rename(new_module, RTLIL::escape_id(top_module_name));

    // Design is really messy at this point. Run some cleanup passes.
    run_pass("proc");
    run_pass("opt");
    run_pass("clean");

    log_pop();
  }
} EqsatPass;

YOSYS_NAMESPACE_END