# 42sh

EPITA project : the goal is to create a fully functional shell

 -  parse the command
 -  manage builtins
 -  manage if/else, while, until, for commands
 -  manage commands such as pipeline, redirection, ...
 -  manage operators

Project realized with 2 classmates

# Building

```sh
meson setup builddir
ninja -C builddir
builddir/42sh
```

