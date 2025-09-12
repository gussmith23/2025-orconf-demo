SCRIPT_DIR=$(dirname "$0")

export CHURCHROAD_DIR="$SCRIPT_DIR/../../churchroad"

yosys \
  -m "$SCRIPT_DIR/../../churchroad/yosys-plugin/churchroad.so" \
  -m "$SCRIPT_DIR/../../yosys-plugin/eqsat.so" -p "
  read_verilog -sv \"$SCRIPT_DIR/simple.sv\"
  hierarchy -check -top simple
  proc

  eqsat --egglog-script \"$SCRIPT_DIR/rewrites.egglog\"

  hierarchy -check -top simple
  opt
  write_verilog
"