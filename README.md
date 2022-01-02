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
$> ./pipex infile command1 command2 outfile
```
infile and outfile are file names, command1 and command2 are shell commands with their parameters.  
Works like the shell command: < infile command1 | command2 > outfile
  
For example:
```
$> ./pipex infile cat wc outfile
```
infile provided for testing (outfile gets created automatically during execution).

#### pipex_bonus folder
Provides a pipex program that can handle:

##### 1) Multiple pipes
```
$> ./pipex infile command1 command2 command3 ... commandn outfile
```
Works like the shell command: < infile command1 | command2 | command3 | ... | commandn > outfile

##### 2) Here document (<<) and append (>>)
```
$> ./pipex here_doc LIMITER command1 command2 file
```
Works like the shell command: command1 << LIMITER | command2 >> outfile
