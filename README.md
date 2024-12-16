# frozesh
Yet another shell written in C

The supported command syntax by `frozesh` is the one below:
```
command_name arg1 arg2 arg3 [etc]
```
You can use the pipe character to pass multiple commands on one line:
```
command1_name arg1 arg2 arg3 [etc] | command2_name arg1 arg2 arg3 [etc]
```

Abstract Syntax Tree (AST) pretty print from `frozesh`:
![image](https://github.com/user-attachments/assets/6e734a41-20d0-48b9-b812-dd31bfd569be)


Feature list
- [x] Basic REPL
- [ ] Computer user shall be displayed on the left, next to the prompt
- [x] Command parser
- [x] Command lexer
- [x] Command executor
- [ ] Built-in utility functions
      - [ ] cd
      - [ ] pwd
- [ ] Command history
- [ ] Install script that makes it available to be called in bash
