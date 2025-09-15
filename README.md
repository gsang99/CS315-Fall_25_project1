//Gemma Sangervasi, 007993564, https://github.com/gsang99/CS315-Fall_25_project1.git

//Collaboration and sources
My two biggest helps were geeks4geeks and chatgpt, geeks4geeks helped me to create a majority of my work when it came to the backtracking as well as using how they made the directions work from. It also helped me
with learning what arguments are used for the command line and how to implement them. I also got help from chatgpt, I would throw in my code to check what exactly it was doing and the functions were working the way
I wanted. It also helped me to fix segmentation faults in my code, (i accidentally initialized a private variable to early and my code flipped. this happened twice). I also looked at stack overflow when it came to 
how to make a 2D vector and what can be stored in matrixs. I also went to Regina for help when my code wasn't running properly on blue and she also let me know that I needed to change my hard coding of input text 
files to be able to take command line. She was really helpful and gave me the articles from geeks4geeks for them. I also talked with my classmates and we helped each other figure out bugs that we were experiencing,
especially when it came to running on blue. 

//Implementation details
I made a 2D vector, made a maze class, to act as a matrix once I had been able to get my file to open properly and start filtering the code. I then started with looking for the edges of the matrix and finding where
the two entry paths were and immediately storing them once I did. I created some print functions to get the original maze and then print out the coordinates of the where I stored the entrance & target to make sure
they were actually where the open paths started and ended. I then made an isitempty function to check the vectors as well as the file that they had contents, and if not to immediately exit if anything happened.
After I began my function find path, where I used recursion and backtracking. I have two seperate variables created, one to hold the coordinates and another to push to the stack. This made it a lot easier to track 
where I was in the maze and then store the open path into the stack variable. Also made a basic constructor and destructor at the beginning, forgot to say. Made another function to check if the paths that were being
scanned were able to be used and was passing that in the find path function as well. And then made a secondary print function with the solved maze and had to make a getter function to pass the coordinates back to main
in order to print it. 

//Testing status
It is fully functional on blue and accepts new text files through ./a.out command line. On clion it throws an error but that is due to the command line function I believe and it not being given the text file
immediately from the user. 
