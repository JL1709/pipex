# pipex

This repo provides the pipex program that can handle the UNIX mechanisms of redirections and pipes on a very basic and static way.  
Tested on macOS Monterey.

## Installation

#### 1) Clone this repository 
```
git clone git@github.com:JL1709/pipex.git
```

#### 2) Run Makfile
```
cd pipex
make
```

#### 3)  Run program
```
$> ./pipex file1 cmd1 cmd2 file2
```
file1 and file2 are file names, cmd1 and cmd2 are shell commands with their parameters.  
Works like the shell command: < file1 cmd1 | cmd2 > file2
  
For example:
```
$> ./pipex file1 cat wc file2
```

Compile with get_next_line_bonus.c and get_next_line_utils_bonus.c and include get_next_line_bonus.h to be able to manage multiple file descriptors.  
For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can
call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors.  
demo.c and demo.txt provided for testing.
