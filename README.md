# "Push Me" Solver

Tool developed to solve a logic puzzle called "Push Me", which you can find at
this link: <a href="http://www.newgrounds.com/portal/view/615592"
target="_blank">Push Me.</a> You need Qt libraries to build it. A main project
file is the main/main.pro

## Usage:

On the left side there is an editor board which comprises of outer fields, inner
fields, a final field (the black one), a final block (the red one), and regular
blocks (the green ones). Under the board there is a NEW button. Click it. Now
you can see a final field ,and a final block. You can move the final field by
clicking on one of the outer fields. To place a regular block you need to click
on an inner field, and drag a mouse to an adjacent cell. To delete it, just
click on it. To move the red block, hold SHIFT and click on one of the inner
cells.

Now you can click the big button to clone the newly created level to a solver
board. You should be able to see a copy.

Click the SOLVE button, and wait untill the FORWARD or the SOLVE button is
enabled again. If the FORWARD button has been enabled, puzzle is solved ,and
you may click on the FORWARD button to see a next move. Otherwise (SOLVE button
enabled) you will need to increase a DEPTH slider, and hit the SOLVE button
again. Don't worry though. Steps which the solver has already done, will not be
repeated. But you should take into account, that cost of every additional step
increases exponentially.
