/**************************************************************************
Description of bugs found by test suite
***************************************************************************/

/*

TEST: SMITHY

Test 1: Play Smithy and gain 3 cards: Failed
Expected deck size of 7 (start size of 5, -1 smithy = 4, + 3 draws = 7), received final deck size of 8.
Determination: Player gained an additional card when the smithy was played.

Test 3: Player is drawing cocrrect amount from own pile: Failed
Expected deck size of 2, final deck size was one.
Determination: This can be explained by the extra card being drawn from the deck when the smithy was played. In 
this case, due to the previous error, it's obvious the extra card was going to the current player.

------------------------------------------------------------------------------------------

TEST: ADVENTURER

Test1b: Gained cards, coin amount unchanged till use: Failed
Expected that the cards drawn, a silver and a copper, would amount to the correct coin amount of 3. In this case 
the final count amount was different from expected. 
Determination: Since Test1a showed that the player correctly drew only two treasure cards, this means that the amount 
of coins attributed to the cards is incorrect.

Test 5: Adventurer card added to played pile after use: Failed
This test failed in the unaltered game state as well. With other cards, discardCard() is called at the end of the turn 
to discard the played card.
Determination: For some reason, adventurer doesn't have discardCard called to disard the adventurer card at the end of
playing the card. This means that the played pile is at 0 instead of one. Though this could be intended, it's inconsistent
with the other cards.

---------------------------------------------------------------------------------------------

TEST: STEWARD

Test5b: Discard count should not be incremented if trashed: Failed
In steward, when choice1 is not 1 or 0, the player is choosing to discard two cards. When the card is discarded, the discard 
count is increased. When the trash flag is set to trash, however, this does not happen. 
Determination: The incrementing discard count illustrates that the trash flag was incorrectly set, and the cards were not 
properly sent to the trash portion of the code.

-----------------------------------------------------------------------------------------------

TEST: VILLAGE

Passed. This was the unaltered card, so this was expected behavior.

------------------------------------------------------------------------------------------------

UNIT TESTS: gainCard, updateCoins, isGameOver, discardCard

Passed.

*/
