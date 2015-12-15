/********************************************************************************
Author: Tara Massey
OSUID: masseyta
Class: Software Engineering II
Term: Fall 2015

Assignment: Assignment 2
Title: documentation.c
Date: 10.09.2015

Purpose: This file contains documentation for the Smithy and Adventurer cards in the
implementation of the game Dominion. In addition, this file contains the documentation
for the discardCard() and updateCoins() functions.

This documentation is provided as a c file, per class instruction.
***********************************************************************************


Smithy Card:
Player draws an additional three cards and adds the cards to their current hand, regardless
of the current amount of cards already in the player's hand. The cards are drawn with
drawCard(). At the end of the player's turn, all cards are discarded with discardCard().

--------------------------------------------------------------------------------------

Adenturer Card:
Player draws additional cards in a loop using drawCard() until two treasure cards are drawn.
Treasure is monitored via the drawntreasure variable, incrementing when treasure is found. The
treasure cards are kept in the player's hand, and the other drawn cards kept in a  temporary
pile. When drawntreasure reaches 2, the temporary hand is discarded with state->discard.

-----------------------------------------------------------------------------------------------------

discardCard():
Function removes the cards from the players hand based on the trashFlag setting. Based on
the trashFlag integer, the cards can be trashed or placed back into the playedCards array.
The trashFlag being set to 1 indicates the card will be trashed.

------------------------------------------------------------------------------------------------------

updateCoins():
Function tracks and calculates the amount of coins available to the player for each round.
Each round the player starts with 0 coins. In a loop, coins are added for each treasure card in the
player's hand, based on type of coin. Copper adds 1, Silver adds 2, Gold adds 3. Additionally, the
function checks for a bonus to coin amount given by state->coins prior to ending.

*/
