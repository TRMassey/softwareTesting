/************************************************************
Author: Tara Massey
OSUID: masseyta
Class: Software Engineering II
Term: Fall 2015

Assignment: Assignment 2
Title: documentation.c
Date: 10.10.2015

Description: Document of changes made to the dominion.c file.
Changes include refactoring of the listed functions, and
introducing bugs.
*************************************************************

Smithy Card Refactoring:
In the loop I deleted the changed the iterations to be more than 3, instead
of less than 3. This minor change will alter the total amount of
cards the player is allowed to draw by one.

Error Code:
	int i;
      //+3 Cards
      for (i = 0; i <= 3; i++)
	{
	  drawCard(currentPlayer, state);
	}

----------------------------------------------------------------------

Adventurer Card Refactoring:
In addition to incrementing the drawn treasure amount, the Adventurer card
now also increments the coin amount of the player by 1.

Error Code:
        if (cardDrawn == copper || cardDrawn == silver || cardDrawn == gold){
            drawntreasure++;
            state->coins = state->coins++;
        }else{

------------------------------------------------------------------------

Steward Card Refactoring:
In the final steps of the Steward Card, the play can trash two cards. I
have altered the flag indicating that the cards should no longer be trashed,
but instead discarded.

Steward Error Code:
    else
    {
        //trash 2 cards in hand
        discardCard(choice2, currentPlayer, state, 0);
        discardCard(choice3, currentPlayer, state, 0);
    }


-------------------------------------------------------------------------

Baron Card Refactoring:
The code has been altered so the player gains a duchy instead of an estate.
To avoid any problems with attempting to pull from an empty pile, the game will
also end if the player takes the last duchy while using this card.

Baron Error Code:
    else{
        if (supplyCount(duchy, state) > 0){
            gainCard(duchy, state, 0, currentPlayer);//Gain an estate
            state->supplyCount[duchy]--;//Decrement Estates
            if (supplyCount(duchy, state) == 0){
                isGameOver(state);
            }
        }

--------------------------------------------------------------------------

Village Card Refactoring:
No errors introduced. Card effect code refactored.


-------------------------------------------------------------------------*/
