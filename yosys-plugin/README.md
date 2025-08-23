# 

Needs TCL8.6. You can install with Homebrew on Mac:

```sh
brew install tcl-tk@8
```

Which prints a helpful message:
```
For compilers to find tcl-tk@8 you may need to set:
  export LDFLAGS="-L/opt/homebrew/opt/tcl-tk@8/lib"
  export CPPFLAGS="-I/opt/homebrew/opt/tcl-tk@8/include"

For pkg-config to find tcl-tk@8 you may need to set:
  export PKG_CONFIG_PATH="/opt/homebrew/opt/tcl-tk@8/lib/pkgconfig"
```

Sometimes it's easiest to just link tcl8.6 using Brew:

```sh
brew link tcl-tk@8
```

You may need to `brew unlink tcl-tk` first, if you have a newer version installed. Only do this if you don't need the newer version.

