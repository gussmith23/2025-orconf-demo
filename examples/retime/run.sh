SCRIPT_DIR=$(dirname "$0")

export CHURCHROAD_DIR="$SCRIPT_DIR/../../churchroad"

yosys \
  -m "$SCRIPT_DIR/../../churchroad/yosys-plugin/churchroad.so" \
  -m "$SCRIPT_DIR/../../yosys-plugin/eqsat.so" -p "
  read_verilog -sv \"$SCRIPT_DIR/needs_retiming.sv\"
  eqsat --extract-script \"$SCRIPT_DIR/extract.py\"
  write_verilog
"