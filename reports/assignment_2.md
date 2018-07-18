What are 2 things that you learned from this assignment?
- Learned about the volatile keyword and its uses in multithreading applications.
*********************************************************************

What are 2 mistakes that you made in this assignment, and how did you discover and fix these mistakes?
- Multiple definition error occured. I fixed them by importing header files once only in my C files inseatd of importing the same header files in multiple files.
- I had a race condition in my polling where my array of values were destroyed as my parent process terminated sooner than my child process could access the values of the array. Fixed them by keeping the parent process alive using polling variables.
**********************************************************************

If you were restarting this assignment, what would you change about how you went about completing this assignment?
- I would make sure that I have declared all my header files only once.
***********************************************************************
