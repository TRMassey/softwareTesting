/******************************************************************
Author: Tara Massey
File: coverage1.c
Purpose: Discuss coverage for four unit tests, four card tests, and
overall coverage of dominion.c.
Method: Makefile made all eight tests, executed all eight test in a
test bundle, and then ran gcov on dominion.c

Note:
Function Results show the percentage covered in that function. So, if
I was testing updateCoins(), how much of updateCoins() was tested in
dominion.c.
Entire Dominion Results show the percentage vs. every line in
dominion.c. This was found by running gcov -b dominion.c after each
unit test was made.
The amount of the given function is what I focused on for my individual
test analysis. The overall results (vs every line in dominion) was
looked at for my overall test suite analysis.
********************************************************************/
/*

COVERAGE, TOTAL AMOUNT OF DOMINION.C
File 'dominion.c'
Lines executed:30.90% of 576
Branches executed:30.46% of 417
Taken at least once:23.26% of 417
Calls executed:24.21% of 95

Analysis: At first glance 30.90% of line coverage and 30.46% of branch coverage doesn't appear
to be great. I then need to take into account that there were numerous functions that my tests
were not asked to cover. In all, we were asked to perform tests for only four cards and four
functions. With that taken into consideration, the coverage in the 30% range begins to indicate
that, though not enough to test the game, the tests that I did create were producing decent 
coverage. Additionally, te fact that the line coverage and the branch coverage were similar shows 
that, When I was testing, I was doing a good job of making sure that all user choices were covered.

Looking at the overall coverage amounts, it also occurs to me that I may have received more coverage
if I had picked other, more critical, functions. An example would be drawCard(), as it is used
very frequently. In SE2 we learned that coverage for the sake of coverage is not the goal, however, 
and that leads me to look at the functions I did choose and how they may make me view the above
data. Additionally, I may also want to consider putting more thought into boundary testing in future
test suites, as merely achieving coverage does not necessarily indicate that I am testing all areas
that require attention.

Most of the tests I ran achieved 100% line coverage and 100% branch coverage of their particular
functions in dominion.c, and achieved overall dominion.c coverage in the 20% range. The two tests that
did not were still in the 90% range for both line and branch coverage. In general, I think this
indicates that if this quality of test were to continue past the scope of the assignment, my
overall dominion.c coverage would continue to improve. Additionally, I think it reinforces that
the 30% total coverage achieved is quite thorough, as each test took into account player choice,
flags, hand count, deck count, other player hand and deck count, input, output, and valid game
supply counts.


-------------------------------------------------------------------------------------------
UNIT TEST COVERAGE, FOUR UNIT TESTS:

Function 'updateCoins'
Function Results:
Lines executed:100.00% of 11
Branches executed:100.00% of 8
Taken at least once:100.00% of 8

Entire Dominion Results:
Lines executed:20.31% of 576
Branches executed:19.18% of 417
Taken at least once:16.79% of 417
Calls executed:8.42% of 95

Analysis: To facilitate testing updateCoins I walked through each line of code in the
function and attempted to create a test that tested the purpose of the statement, as 
well as took into account what would happen if there was incorrect input. By doing this
I achieved 100% line covereage, and 100% branch coverage. Overall, though coverage for 
the sake of coverage is not desired, this indicates a thorough spread of tests. If I 
were to go back and improve upon the tests, I would look more in depth at boundary testing,
perhaps stressing the bonus section. For the purpose of my tests, I kept all input within
the expected domain.


				----------------------------

Function 'isGameOver'
Function Results:
Lines executed:100.00% of 10
Branches executed:100.00% of 8
Taken at least once:100.00% of 8

Entire Dominion results:
Lines executed:17.36% of 576
Branches executed:17.75% of 417
Taken at least once:14.87% of 417
Calls executed:7.37% of 95

Analysis: I sought to test what a valid and invalid game state would look like in testing.
First, by simply going through the code and ensuring that the intent of each statement matched
its' output I managed to create 100% statement coverage. There were very limited branches to take,
so I made sure that I took each branch at least once. This resulted in 100% branch coverage. I
also decided to test the impact of the function on supply counts that were not supposed to be
impacted, to ensure that they were not changed unintentionally. I also made sure that the game did 
not prematurely end at a lower card count or with a lesser amount of piles empty. More thorough
coverage could, perhaps, have been achieved by testing each pile individually, ensuring that their
decreasing count had no unintended impacts on the game, and that the intended impacts were the 
achieved. Boundary testing had very little importance in this function, as it was merely testing
supply counts against 0.


				-------------------------------

Function 'discardCard'
Function Results:
Lines executed:92.31% of 13
Branches executed:100.00% of 6
Taken at least once:83.33% of 6

Entire Dominion Results:
Lines executed:22.40% of 576
Branches executed:20.62% of 417
Taken at least once:17.99% of 417
Calls executed:8.42% of 95

Analysis: This is the test I didn't get 100% coverage in, and the why is still a bit puzzling. I
still achieved a high level of coverage, 100% of branches and 92.31% of lines, but if you look at the 
code analysis below, you'll see that I missed specifically checking if the hand count was decremented.
This suprised me, as I did check it, but then I realized I checked it in a strange way. I specifically
discarded the Province card, and then checked that the Province card was removed from the hand. This did 
not specifically check the hand count, but served the same purpose :

        -: 1138:  //remove card from player's hand
       12: 1139:  if ( handPos == (state->handCount[currentPlayer] - 1) )       //last card in hand array is played
        -: 1140:    {
        -: 1141:      //reduce number of cards in hand
    #####: 1142:      state->handCount[currentPlayer]--;
        -: 1143:    }
       12: 1144:  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
       12: 1159:  return 0;
Additionally, I checked for all valid states the player could be in in an attempt to do boundary
testing within a valid domain. I did full deck as well as 1 card, lowest possible to have this function
called. All in all, I think the testing was very good, even if it did not quite hit 100%.

				---------------------------------

Function 'gainCard'
Function Results:
Lines executed:100.00% of 13
Branches executed:100.00% of 6
Taken at least once:100.00% of 6
Calls executed:100.00% of 1

Entire Dominion Results:
Lines executed:19.97% of 576
Branches executed:19.18% of 417
Taken at least once:16.31% of 417
Calls executed:8.42% of 95

Analysis: I achieved 100% line and branch coverage. While this alone is not an indicator of a good
test suite, I believe I covered logical bases as well as boundary cases. I tested for a player attempting
to gain a card that was at supply count 0, a player attempting to gain a card that was not in the game, 
and a valid card. I then tested each available flag in the valid domain, and made sure that gaining the
card resulted in no unintended effects for player two or for the game state supplies. I then took the
location of the card into account, making sure it made it to its' intended flagged location: hand, deck, 
or discard.


----------------------------------------------------------------------

CARD TEST COVERAGE, FOUR CARDS:

Function 'stewardRef'
Function Results:
Lines executed:100.00% of 10
Branches executed:100.00% of 4
Taken at least once:100.00% of 4
Calls executed:100.00% of 5

Entire Dominion Results:
Lines executed:23.26% of 576
Branches executed:24.22% of 417
Taken at least once:16.07% of 417
Calls executed:21.05% of 95


Analysis: I achieved 100% line and 100% branch coverage, and I believe that in this case the coverage
tool is a good indicator of the test suite. I tested all three available options for the choice1 flag,
and for each of the options I made sure that the stated impact occured, and that no gains were made to the
other player or the valid world state.  Additionally, I made sure that no unintended gains or losses occured
for the player during these choices. When I tested the "else" for choice1, I also made sure that the trash
flag was tested, so it wasn't simply reducing the handCount and not being appropriately trashed. Due to
this I believe that I had a good test suite  and coverage, though more work could perhaps go into boundary
testing. An example would be what would happen if the player had less than two cards in their deck and
opted for the choice to discard.

					----------------------------------

Function 'villageRef'
Function Results:
Lines executed:100.00% of 5
No branches
Calls executed:100.00% of 2

Entire Dominion Results:
Lines executed:21.35% of 576
Branches executed:23.26% of 417
Taken at least once:14.87% of 417
Calls executed:14.74% of 95


Analysis: The village card was very straight forward with no branches. I merely needed to test that the
intended consequences of playing the card occured, and that no unexpected losses or gains were made to
either the player, other player, or valid world state. I tested gaining the appropriate amount of cards
and the appropriate amount of actions, and made sure no other changes occured. I made sure the played
card was put back into the appropriate pile after use. I did not have much, if anything, in the way
of boundary cases, as the card seemed to lend itself more to gaining a stated number of consequences. In 
future testing, this may be an area to give more consideration to.

					------------------------------------

Function 'smithyRef'
Function Results:
Lines executed:100.00% of 5
Branches executed:100.00% of 2
Taken at least once:100.00% of 2
Calls executed:100.00% of 2

Entire Dominion Results:
Lines executed:20.31% of 576
Branches executed:23.26% of 417
Taken at least once:14.63% of 417
Calls executed:11.58% of 95


Analysis: Smithy was another straight forward test case. I achieved 100% line coverage and 100% branch
coverage. For such a small and clear function, I believe this shows rather good results. The main areas
I needed to make sure were logically covered were the number of cards the player received, and if the
played card was discarded from the hand at the end. I tested these things, as well as for unintended
consequences to the other player and valid world state. As this function merely calls for gaining cards,
there was very little I could do in the way of boundary testing. It is, perhaps, an area for future
improvement.
					-----------------------------------

Function 'adventurerRef'
Function Results:
Lines executed:93.75% of 16
Branches executed:100.00% of 12
Taken at least once:91.67% of 12
Calls executed:50.00% of 2

Entire Dominion Results:
Lines executed:20.31% of 576
Branches executed:23.26% of 417
Taken at least once:14.63% of 417
Calls executed:11.58% of 95



Analysis: While I achieved 100% branch coverage, I failed to achieve 100% line coverage. Upon insepction
of dominion.c.gcov, the answer was immediately apparent. I tested each line that I could clearly find a
result for, or have a variable represent the correct state, but I ignored the function that was called
within the adventurer function. Namely, I didn't test to see if the deck would be shuffled:

       26: 1257:    while(drawntreasure<2){
       14: 1258:        if (state->deckCount[currentPlayer] <1){//if the deck is empty we need to shuffle discard and add to deck
    #####: 1259:            shuffle(currentPlayer, state);
        -: 1260:        }
In looking at these results, I'm still fairly happy with  my overall test suite. The lines within the
adventurer card that stated an output or expected an input were tested, as well as any unintended player or
valid game state consequences. Shuffle is another function, and I'm not entirely sure how I'd go about
testing that it was called. Perhaps in the future I would look at the current cards in the deck, then call
the adventurer function, then look at the deck cards to see if they appear in a different order. All in
all, it indicates an area for test suite improvement, as an empty deck would indicate a boundary case I
needed to account for.


---------------------------------------------------------------------------
COVERAGE OF INDIVIDUAL FUNCTIONS, NON-PICKED FUNCTIONS:

Function 'supplyCount'
Lines executed:100.00% of 2
No branches
No calls

Function 'fullDeckCount'
Lines executed:0.00% of 9
Branches executed:0.00% of 12
Taken at least once:0.00% of 12
No calls

Function 'whoseTurn'
Lines executed:100.00% of 2
No branches
No calls

Function 'handCard'
Lines executed:0.00% of 3
No branches
Calls executed:0.00% of 1

Function 'numHandCards'
Lines executed:0.00% of 2
No branches
Calls executed:0.00% of 1

Function 'isGameOver'
Lines executed:0.00% of 10
Branches executed:0.00% of 8
Taken at least once:0.00% of 8
No calls

Function 'scoreFor'
Lines executed:0.00% of 24
Branches executed:0.00% of 42
Taken at least once:0.00% of 42
Calls executed:0.00% of 3

Function 'getWinners'
Lines executed:0.00% of 24
Branches executed:0.00% of 22
Taken at least once:0.00% of 22
Calls executed:0.00% of 2

Function 'getCost'
Lines executed:0.00% of 30
Branches executed:0.00% of 28
Taken at least once:0.00% of 28
No calls

Function 'buyCard'
Lines executed:0.00% of 18
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
Calls executed:0.00% of 4

Function 'baronRef'
Lines executed:0.00% of 30
Branches executed:0.00% of 18
Taken at least once:0.00% of 18
Calls executed:0.00% of 8

Function 'shuffle'
Lines executed:93.75% of 16
Branches executed:100.00% of 8
Taken at least once:87.50% of 8
Calls executed:100.00% of 2

Function 'drawCard'
Lines executed:36.00% of 25
Branches executed:33.33% of 6
Taken at least once:16.67% of 6
Calls executed:0.00% of 1

Function 'endTurn'
Lines executed:0.00% of 20
Branches executed:0.00% of 6
Taken at least once:0.00% of 6
Calls executed:0.00% of 3

Function 'cardEffect'
Lines executed:6.32% of 190
Branches executed:14.11% of 163
Taken at least once:3.07% of 163
Calls executed:10.00% of 50

Function 'playCard'
Lines executed:0.00% of 14
Branches executed:0.00% of 10
Taken at least once:0.00% of 10
Calls executed:0.00% of 3

Function 'initializeGame'
Lines executed:83.87% of 62
Branches executed:95.65% of 46
Taken at least once:80.43% of 46
Calls executed:100.00% of 5

Function 'kingdomCards'
Lines executed:0.00% of 13
No branches
No calls

Function 'newGame'
Lines executed:0.00% of 3
No branches
No calls

*/
