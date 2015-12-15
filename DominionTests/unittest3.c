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
  int amount = 0; // update coins sets coins to 0

  printf("---     TESTING FUNCTION: updateCoins     ---\n\n");
  
  for(i = 0; i < numTests; i++){
    
    // set hand basics for each game so the function can be called
    pos = -1;
    p = 0;
    p2 = 1;


    // testing copper
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = copper;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 0);
    printf("Test 1: Copper increases coins by 1: \n");
    if(testState.coins == amount + 1)
      printf("Passed. Expected %d    Returned %d\n", amount +1, testState.coins);
    else
      printf("FAILED.  Expected %d    Returned %d\n", amount +1, testState.coins);

    // test to make sure no impact on other player
    printf("\nTest 1b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == g.deckCount[p2])
      printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);

	   // testing silver
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = silver;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 0);
    printf("Test 2: Silver increases coins by 2: \n");
    if(testState.coins == amount +2)
      printf("Passed. Expected %d    Returned %d\n", amount +2, testState.coins);
    else
      printf("FAILED.  Expected %d    Returned %d\n", amount +2, testState.coins);

    // test to make sure no impact on other player
    printf("\nTest 2b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == g.deckCount[p2])
      printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);


    // testing gold
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = gold;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 0);
    printf("Test 3: Gold increases coins by 3: \n");
    if(testState.coins == amount +3)
      printf("Passed. Expected %d    Returned %d\n", amount +3, testState.coins);
    else
      printf("FAILED.  Expected %d    Returned %d\n", amount +3, testState.coins);

    // test to make sure no impact on other player
    printf("\nTest 2b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == g.deckCount[p2])
      printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);


    // testing bonus
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = gold;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 1);
    printf("Test 4: Bonus produces incease equivalent to input (coins + 1): \n");
    if(testState.coins == amount +4)   // bonus + gold
      printf("Passed. Expected %d    Returned %d\n", amount +4, testState.coins);
    else
      printf("FAILED.  Expected %d    Returned %d\n", amount +4, testState.coins);

    // test to make sure no impact on other player
    printf("\nTest 4b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == g.deckCount[p2])
      printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);


    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.hand[p][0] = feast;
    testState.hand[p][1] = gardens;
    testState.hand[p][2] = embargo;
    testState.hand[p][3] = gold;
    testState.hand[p][4] = mine;
    updateCoins(p, &testState, 3);
    printf("Test 5: Bonus produces increase equivalent to input (coins + 3): \n");
    if(testState.coins == amount +6)
      printf("Passed. Expected %d    Returned %d\n", amount +6, testState.coins);
    else
      printf("FAILED.  Expected %d    Returned %d\n", amount +6, testState.coins);

    // test to make sure no impact on other player
    printf("\nTest 5b: Other player gained nothing to deck: \n");
    if(testState.deckCount[p2] == g.deckCount[p2])
      printf("Passed. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);
    else
      printf("FAILED. Expected other user's deck to remain %d   It's now: %d\n", g.deckCount[p2], testState.deckCount[p2]);


    //test for world state changes, will indicate if any victory cards have been given out inappropriately
    printf("\nTest 6: : Test supply counts for points and curses that should not have been distributed: \n ");
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
    printf("\nTest 7: Test supply counts for treasure that should have been distributed: \n");
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
