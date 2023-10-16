# Snake

I tried to implement the classic snake game in C.

## Libraries

I used the following libraries:
- include<stdio.h>, for printing with printf();
- include<windows.h>, to be able of modifying the coordinates in the console screen;
- include<conio.h>, for using the functions kbhit() and getch(), to take the user's input;
- include<stdbool.h>, for using boolean variables;
- include<time.h>, for using the function Sleep().


## Functioning

I used two structs for defining both the Snake and the Fruit. In particular, the Snake was realized by two vectors of #SnakeLength positions, the first for the vertical positions and the second for the horizontal ones. In this way, the  i-th elements of both the vectors identifies a cell occupied by the Snake.

I then create the map, by setting the border to 1 and the center to 0, for be able to print it after. In the function printMap(), I print it in the console, positioning also the Snake and the Fruit in it.
I create also a function for randomly setting up the fruit, without putting it above the snake.

For moving the Snake, i take the user's input move on the keyboard and then I translate it into the correct move, by changing the position of the head of the Snake, and the by updating the rest of the vectors, by copying the i+1-th element in the i-th position.
Finally, i make some controls for verifying if the Snake has slammed his head against something.

The game ends with a victory if the Snake reaches his maximum length.
