# "Push Me" Solver

A tool developed to solve a logic puzzle called "Push Me", which you can find at
this link: <a href="http://www.newgrounds.com/portal/view/615592"
target="_blank">Push Me.</a> You may need Qt libraries to build the project. A
main project file is main/main.pro

## Installation

Download the zip-file (right side of the screen), and unpack it to a destination
folder, or if you have Git installed, clone the repository:
  git clone git://github.com/legendary-mich/push-me_solver
The easiest way to build the program is to use a <a
href="http://qt-project.org/downloads">Qt Creator.</a> Open the creator. Click
"File/Open file or project.." Select "main/main.pro". On the configuration
screen select the Release checkbox, hit the "configure project" button (whatever
it is called in your language), and you are done. Now you can build the project
by clicking on a hammer icon, or simply run it clicking on a green arrow.

## Usage:

On the left side there is an editor board which comprises of outer fields, inner
fields, a final field (the black one), a final block (the red one), and regular
blocks (the green ones). Under the board there is a NEW button. Click it. Now
you can see a final field ,and a final block. You can move the final field by
clicking on one of the outer fields. To place a regular block you need to click
on an inner field and drag a mouse to an adjacent cell. To delete it, just
click on it. To move the red block, hold SHIFT and click on one of the inner
cells.

Now you can click the big button to clone the newly created level to a solver
board. You should be able to see a copy.

Click the SOLVE button, and wait untill the FORWARD or the SOLVE button is
enabled again. If the FORWARD button has been enabled, the puzzle is solved and
you may click on the FORWARD button to see a next move. Otherwise (SOLVE button
enabled) you will need to increase a DEPTH slider, and hit the SOLVE button
again. Don't worry though. Steps which the solver has already done, will not
have been repeated. But you should take into account that cost of every
additional step increases exponentially.
