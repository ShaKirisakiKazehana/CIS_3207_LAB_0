I have written this as how normal ls command would be like
With no flags. If it starts with no inputs, it will display
Current dir, with a given dir, it will display that one.
If dir is not found it will return err. Recursion done 
by checking if the item found is a dir or not. With a given dir
It will do recursion.


I have written two functions, one only does read write between files, the other
One will creat multiple files in the new dir. which then it will call the copy
Function to copy the contents on to each one of them.
