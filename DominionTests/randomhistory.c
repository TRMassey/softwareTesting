/*****************************************************************************
Author: Tara Massey
Assignment: 4, random testing
Purpose: Discuss development of random testers, improvements in coverage, and
effort to check the correctness of specification
*****************************************************************************/

/*
randomtestadventurer.c : Testing the Adventurer Card

Development of the random tester -
To begin, I start with attempting to specify what the correct domain range would
be for a random tester. As discussed in the lecture, sending completely random
test values is of little use for a function that expects a valid game state. So,
what I began with identifying a valid game state.

For starters, I idenfitied what needed to be randomized prior to initializing the
game state. For me, this was the number of players and the kingdom cards. Since we
were not testing the entire game, but merely a single card, the kingdom cards were 
of less importance for randomization than number of players. So, I randomized the
player number for each game iteration. In order to achieve boundary testing as well
as common numbers, I allowed for the minimum amount of players, two, to the maximum
allowed.

After initializing the game, I randomzed elements within the game state prior to
running the function under test. The elements that I felt were key to randomize were
the decksize, the hand size, the position of the adventurer card, and then, since I
prior to initialization I didn't force a randomization of the cards, I made a 
completely random deck from all the available cards.

Now that I had random elements which I could put in a large testing loop, I decided
to start planning for coverage. In order to cover my bases, I wanted a completely
random call within the acceptable game state, but I also wanted one that had some
level of structure. So, I made a random function as well as a random function that
guaranteed the presence of at least two treasure cards somewhere within the deck.
To keep with my random theme, I randomized which treasure cards they were as well as
their position within the deck. I felt that in doing this I was achieving solid
coverage against some game states that might occur in the purely random tester that
may not be valid.

Improvements in Coverage -
In larger terms, my previous testing scheme assumed a set number of players, set
amount of cards in hand, and an abundent deck. By nature of random testing, I'll 
be testing more scenarios than I previously covered. What happens if the deck is
very tiny? Will it shuffle often? With my random tester I can seee what occurs.
Along the same lines, I'm able to witness how this function plays with boundary
testing that I was lacking in my old coverage scheme.

I also wanted to push coverage testing by making sure the tests were focused in on 
specific questions. My last coverage was 93.75% for the function under test, but the
test cases could use specification and improvement. So, in this scheme, I decided to
not only test the amount of coin cards being picked up, by identify what the expected
amount is, what cards I was pulled, and identify the difference. Hopefully, this will 
allow me to more easily identify any error made to the coin count for the game if it
is dependent on a particular card.


Effort to Check the Corectness of the Specification -
I had a decent game plan going in for testing boundary cases as well as gather data
for random combinations, but that doesn't mean that every test is going to turn up
valid. So, to deal with this, I chose to print the data for each of the randomized 
elements prior to running the tests. This way if a test fails, as it did in test when
cards were not added to the hand because there was not enough cards in the deck, I
could see that it was, in fact, not a failure. The game handled the situation with
grace, no crashes occured, and no game state issues were detected. The test failed 
because the amount I expected was not possible. I saw this in scenarios where I
expected a number and that "expected" number, due to the formula, ended up being
negative. That is, of course, not possible and the test, despite the failed statement,
does not show a fault.

In order ot make sure my tests were correct I also ran it against the dominion.c that
was not refactored, and made sure the results were consistent. I didn't want any errors
in logic or specification to sneak in because of a fault I may have introduced in a bug.

General Coverage Comments -

Total Dominion Coverage:

File 'dominion.c'
Lines executed:23.61% of 576
Branches executed:25.66% of 417
Taken at least once:18.47% of 417
Calls executed:12.63% of 95

Previous: File 'dominion.c'
Lines executed:20.14% of 576
Branches executed:24.22% of 417
Taken at least once:16.07% of 417
Calls executed:10.53% of 95
dominion.c:creating 'dominion.c.gcov'

Function Coverage:
Function 'adventurerRef'
Lines executed:100.00% of 16
Branches executed:100.00% of 12
Taken at least once:100.00% of 12
Calls executed:100.00% of 2

Previous: Function Coverage
Lines executed:93.75% of 16
Branches executed:100.00% of 12
Taken at least once:91.67% of 12
Calls executed:50.00% of 2

Discussion of Improvements on Coverage: As you can see, the random tester definitely
got to some cases that my first card tests failed to cover. The random tester not only
made improvements with boundary cases and with additional players, but it also allowed
me to redesign my tests the lines of code I previously failed to achieve coverage on, 
namely:
       26: 1257:    while(drawntreasure<2){
       14: 1258:        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
    #####: 1259:            shuffle(currentPlayer, state);
        -: 1260:        }
The random tester not only let me test the above previously missed code, but did it
with ease and with a great deal of testing:	
	branch  1 taken 96%
    11523: 1259:            shuffle(currentPlayer, state);

		--------------------------------------------------------

randomtestcard.c : Testing the Smithy Card

Development of the random tester -
To begin, I start with attempting to specify what the correct domain range would
be for a random tester. As discussed in the lecture, sending completely random
test values is of little use for a function that expects a valid game state. So,
what I began with identifying a valid game state.

For starters, I idenfitied what needed to be randomized prior to initializing the
game state. For me, this was the number of players and the kingdom cards. Since we
were not testing the entire game, but merely a single card, the kingdom cards were 
of less importance for randomization than number of players. So, I randomized the
player number for each game iteration. In order to achieve boundary testing as well
as common numbers, I allowed for the minimum amount of players, two, to the maximum
allowed.

After initializing the game, I randomzed elements within the game state prior to
running the function under test. The elements that I felt were key to randomize were
the decksize, the hand size, and then  and then randomization of the cards. I made a 
completely random deck from all the available cards. Additionally, I wanted to push
boundary testing a bit further, so I allowed for both the deck size and handsize to
be zero in some instances. This created a few odd scenarios where I was "Drawing"
from an empty deck, but the game didn't crash. My oracle in these cases simply
indicated that the deck size at the end was wrong, as it should be negative, but
a quick glance at the hand size, non-crashed game state, and starting input clearly
shows that was a false error.

I then put my function in a loop, initializing new random values for each
of the above mentioned at every iteration. The test state is created inside the
function for ease, based off the game state we created with the random variables.

Improvements in Coverage -
In larger terms, my previous testing scheme assumed a set number of players, set
amount of cards in hand, and an abundent deck. By nature of random testing, I'll 
be testing more scenarios than I previously covered. What happens when you draw
from an empty deck? Will shuffling happen like it's supposed to? Does all tracking
work regardless of hand size? 

Since my previous function had function coverage of 100%, I wanted to really make
sure that I was asking the right questions in my tests. So, I really wanted to
focus in on the boundary cases, dramatic differences between hand and deck size,
and what may occur if a player tries to do something there are not resources to
do. By implementing domain ranges and randomizing the combinations that could occur,
I truly got to dive into that with random testing in a way my previous card tests 
did not do.

Effort to Check the Corectness of the Specification -
There were tests runs that passed with flying colors, and tests where particular
tests failed. When they failed, I made sure that expected output was displayed as well
as the real output. Additionally, I displayed the contents of all the randomized
elements. So, when these tests failed a few times, I could easily see that it was
a problem occuring from my oracle, which stated that expected a negative number. In
the game, that's not realisitc. So, truly what that failed test showed, was that when
unrealistic combinations of possible valid domain inputs occured, the game handled
them gracefully.

In order ot make sure my tests were correct I also ran it against the dominion.c that
was not refactored, and made sure the results were consistent. I didn't want any errors
in logic or specification to sneak in because of a fault I may have introduced in a bug.


General Coverage Comments -

Entire Dominion Coverage:
Lines executed:23.78% of 576
Branches executed:24.70% of 417
Taken at least once:16.79% of 417
Calls executed:12.63% of 95

Previous Dominion Coverage:
Lines executed:20.31% of 576
Branches executed:23.26% of 417
Taken at least once:14.63% of 417
Calls executed:11.58% of 95

Function Specific Coverage:
Lines executed:100.00% of 5
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 2

Previous Function Specific Coverage:
Lines executed:100.00% of 5
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 2

Discussion of Improvements on Coverage: The above results show an overall dominion coverage
increase, even though the function coverage remains 100%. This is a great illustration
of why total coverage is important to look at! The increase in my test domain and the focus
on making sure I was pushing for all combinations and hitting empty and full boundaries
caused code to be called that otherwise was not used.


		--------------------------------------------
Combined Coverage -
Lines executed:26.74% of 576
Branches executed:27.58% of 417
Taken at least once:20.14% of 417
Calls executed:15.79% of 95

Please note, this is less than the 30.90% coverage from the previous tests, but the
previous tests had four cards and four unit tests! These two card tests alone now nearly
achieve that level of coverage. With the additional increase in both functions reach on
the total amount of dominion.c code, as well as the improved coverage seen in the
adventurer card function, it's becoming apparent why random testing is hepful. 

For future improvements, I would like to continue improving my oracle to better handle
invalid game state combinations that may occur, so the failed notification is thrown
less often. Additionally, adding in a few specific control tests would be lovely, though
it was not done in this assignment in an attempt to strictly follow what was being 
requested of us.

Bugs: Found error in amount being returned by coins in adventurer, adventurer also not adding
adventurer card to played pile after use. Smithy is pulling an extra card from the deck,
seen in two different tests.