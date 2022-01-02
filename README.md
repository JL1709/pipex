# pipex

This repo provides the pipex program that can handle the UNIX mechanisms of redirections and pipes on a very basic and static way.  
Tested on macOS Monterey.

## Installation

#### 1) Clone this repository 
```
git clone git@github.com:JL1709/pipex.git
```

#### 2)  Run program
Include header file to your code
```
#include "pathToGetNextLineFolder/get_next_line.h"
```
For example:
```ruby
#include "get_next_line.h"

int	main(void)
{
	int	i;
	char	*str;

	i = open("demo.txt", O_RDONLY);
	while ((str = get_next_line(i)))
	{
		printf("%s",str);
		free(str);
		str = NULL;
	}
	close(i);
	return (0);
}
```

Compile your code with desired buffer size
```
gcc -D BUFFER_SIZE=1 demo.c get_next_line.c get_next_line_utils.c
```

Run executable
```
./a.out
```
Compile with get_next_line_bonus.c and get_next_line_utils_bonus.c and include get_next_line_bonus.h to be able to manage multiple file descriptors.  
For example, if the file descriptors 3, 4 and 5 are accessible for reading, then you can
call get_next_line once on 3, once on 4, once again on 3 then once on 5 etc. without losing the reading thread on each of the descriptors.  
demo.c and demo.txt provided for testing.
