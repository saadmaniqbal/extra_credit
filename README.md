# extra_credit
An attempt to synthesize texture with non parametric sampling in C++

The code written is based off the Python version of the code from:

https://github.com/rbaravalle/efros

Almost all of the code is functional except the part which writes the png file as an output. Due to the limitations of useful libraries and time constraints, i was unable to find a way to make a fully functional program. 

Other limitations in my program is the code itself, as it is very slow to run and produce the image. I have included the python version of the image to display the validity of the logic behind the code that i used from the link above. There are two functions that handle the production of the output: pixel, that renders individual pixel from an initial 3x3 sample into an entire image, and the function synthesize, that does the necessary preparations to send the relevant information to the function pixel. The main function inputs the image and sends the detail through synthesize to output the png. At this point, the program will not run, but i hope you allow partial credit for the C++ functions and what they entail. Thank you.
