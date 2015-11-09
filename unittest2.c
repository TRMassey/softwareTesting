#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>

int main(){

  int i;            // counter
  int p, p2;          // indicating which player
  int pos;          // position
  int numPlayers = 2;     // players for valid gamestate
  int numTests = 1;     // large testing spread
  struct gameState g;     // gamestate, original
  struct gameState testState;   // gamestate under test
  int k[10] = {feast, gardens, embargo, remodel, tribute, mine, cutpurse, ambassador, great_hall, village};
  int result;         // return test


  printf("---     TESTING FUNCTION: gainCard     ---\n\n");
  
  for(i = 0; i < numTests; i++){
    
    // set hand basics for each game so the function can be called
    pos = -1;
    p = 0;
    p2 = 1;


    // testing if pile is empty
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.supplyCount[feast] = 0;  // say that feast has no suppl
    result = gainCard(feast, &testState, 0, p);   // gain feast in teststate, disard set for current player
    printf("Test 1: Cannot gain a card which is out of stock: \n");
    if(result == -1)
      printf("Passed. Expected %d    Returned %d\n", -1, result);
    else
      printf("FAILED. Expected %d    Returned %d\n", -1, result);


    // testing if card is not in game
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    result = gainCard(sea_hag, &testState, 0, p);   // not in game
    printf("\nTest 2: Cannot gain a card which is not in game: \n");
    if(result == -1)
      printf("Passed. Expected %d    Returned %d\n", -1, result);
    else
      printf("FAILED. Expected %d    Returned %d\n", -1, result);

	
    // testing if added to deck
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    result = gainCard(feast, &testState, 1, p);   // gain feast in teststate
    printf("\nTest 3: Flag One, Card is added to players deck: \n");
    if(testState.deckCount[p] == g.deckCount[p] +1)
      printf("Passed. Expected %d    Returned %d\n", g.deckCount[p] +1, testState.deckCount[p]);
    else
      printf("FAILED. Expected %d    Returned %d\n", g.deckCount[p] +1, testState.deckCount[p]);

    // part b, make sure it didn't go to the other user's deck
    if(testState.deckCount[p2] != g.deckCount[p2])
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);

    // make sure it's added to hand
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    result = gainCard(feast, &testState, 2, p);   // gain feast in teststate, disard set for current player
    printf("\nTest 4: Flag Two, Card is added to players hand: \n");
    if(testState.handCount[p] == g.handCount[p] +1)
      printf("Passed. Expected %d    Returned %d\n", g.handCount[p] +1, testState.handCount[p]);
    else
      printf("FAILED. Expected %d    Returned %d\n", g.handCount[p] +1, testState.handCount[p]);

    // part b, make sure it didn't go to the other user's deck
    if(testState.handCount[p2] != g.handCount[p2])
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.handCount[p2], testState.handCount[p2]);

   // make sure it's discarded
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    result = gainCard(feast, &testState, 0, p);   // gain feast in teststate, disard set for current player
    printf("\nTest 5: Flag zero, Card is discarded: \n");
    if(testState.discardCount[p] == g.discardCount[p] +1)
      printf("Passed. Expected %d    Returned %d\n", g.discardCount[p] +1, testState.discardCount[p]);
    else
      printf("FAILED. Expected %d    Returned %d\n", g.discardCount[p] +1, testState.discardCount[p]);

    // part b, make sure it didn't go to the other user's deck
    if(testState.discardCount[p2] != g.discardCount[p2])
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.discardCount[p2], testState.discardCount[p2]);


   // make supply count decreases
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    result = gainCard(feast, &testState, 0, p);   // gain feast in teststate, disard set for current player
    printf("\nTest 6: Supply count is decreased: \n");
    if(testState.supplyCount[feast] == g.supplyCount[feast] -1)
      printf("Passed. Expected %d    Returned %d\n", g.supplyCount[feast] -1, testState.supplyCount[feast]);
    else
      printf("FAILED. Expected %d    Returned %d\n", g.supplyCount[feast] -1, testState.supplyCount[feast]);
	
    //test for world state changes, will indicate if any victory cards have been given out inappropriately
    printf("\nTest 7: : Test supply counts for points and curses that should not have been distributed: \n ");
    if(g.supplyCount[estate] != testState.supplyCount[estate])
      printf("FAILED. Estate Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[estate], testState.supplyCount[estate]);
    if(g.supplyCount[duchy] != testState.supplyCount[duchy])
      printf("FAILED. Duchy Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[duchy], testState.supplyCount[duchy]);
    if(g.supplyCount[province] != testState.supplyCount[province])
      printf("FAILED. Province Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[province], testState.supplyCount[province]);
    if(g.supplyCount[curse] != testState.supplyCount[curse])
      printf("FAILED. Province Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[curse], testState.supplyCount[curse]);
    else
      printf("Passed. Supply counts for curses and victory cards are the same\n");

    // test for changes in money supply that shouldn't have been activated, will test for money being given to players
    printf("\nTest 8: Test supply counts for treasure that should have been distributed: \n");
    if(g.supplyCount[copper] != testState.supplyCount[copper])
      printf("FAILED. Copper Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[copper], testState.supplyCount[copper]);
    if(g.supplyCount[silver] != testState.supplyCount[silver])
      printf("FAILED. Silver Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[silver], testState.supplyCount[silver]);
    if(g.supplyCount[gold] != testState.supplyCount[gold])
      printf("FAILED. Gold Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[gold], testState.supplyCount[gold]);
    else
      printf("Passed. Supply counts for treasure cards are the same\n");

  }
  return 0;
}
