This is simple plinko game, that runs in terminal.

The logic for ball falling is like this:
1. we have n layers through which the ball will fall
2. position of ball will be 'b' and starts from 0
3. Lets have simple example of where the ball will fall

   0
  1 2 
 3 4 5
6 7 8 9

We know that ball will fall either to the right or to the left of where it was. we can also rerite the pyramid like this:

0
1 2
3 4 5
6 7 8 9

From here we see that in this case ball goes either directly down or dow and 1 to the right. To go directly down we need to add 'n' to the balls position, and when it goes down and right 'b' increases by n + 1.

So we can write algorithm something like this:
int b = 0, n = 1;
while (n <= layers) {
  b += n + rand() % 2;
  n++;
}
then we can simly display it onto the screen.

