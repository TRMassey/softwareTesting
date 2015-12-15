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


  printf("---     TESTING FUNCTION: isGameOver    ---\n\n");
  
  for(i = 0; i < numTests; i++){
    
    // set hand basics for each game so the function can be called
    pos = -1;
    p = 0;
    p2 = 1;


    // testing if pile is empty
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.supplyCount[province] = 0;  
    result = isGameOver(&testState);   
    printf("Test 1: Province is empty, should be game over: \n");
    if(result == 1)
      printf("Passed. Expected %d    Returned %d\n", 1, result);
    else
      printf("FAILED. Expected %d    Returned %d\n", 1, result);


    // testing if three supply piles are at 0 game ends
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.supplyCount[silver] = 0;  
    testState.supplyCount[duchy] = 0;
    testState.supplyCount[estate] = 0;
    result = isGameOver(&testState);
    printf("\nTest 2: Three empty supply decks end game: \n");
    if(result == 1)
      printf("Passed. Expected %d    Returned %d\n", 1, result);
    else
      printf("FAILED. Expected %d    Returned %d\n", 1, result);

    // test to make sure game does not end early at lesser counts
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.supplyCount[duchy] = 0;
    testState.supplyCount[estate] = 0;
    result = isGameOver(&testState);
    printf("\nTest 3: Two empty supply decks should not end game: \n");
    if(result == 0)
      printf("Passed. Expected %d    Returned %d\n", 0, result);
    else
      printf("FAILED. Expected %d    Returned %d\n", 0, result);

    // test to make sure game does not end with cards still on pile
    initializeGame(numPlayers, k, 1000, &g);
    memcpy(&testState, &g, sizeof(struct gameState));
    testState.supplyCount[silver] = 1;  
    testState.supplyCount[duchy] = 1;
    testState.supplyCount[estate] = 1;
    result = isGameOver(&testState);
    printf("\nTest 4: Three empty supply decks end game: \n");
    if(result == 0)
      printf("Passed. Expected %d    Returned %d\n", 0, result);
    else
      printf("FAILED. Expected %d    Returned %d\n", 0, result);


    // test for changes in money supply that shouldn't have been activated, will test for money being given to players
    printf("\nTest 5: Test supply counts for treasure that should have been distributed: \n");
    if(g.supplyCount[copper] != testState.supplyCount[copper])
      printf("FAILED. Copper Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[copper], testState.supplyCount[copper]);
    if(1 != testState.supplyCount[silver])
      printf("FAILED. Silver Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[silver], testState.supplyCount[silver]);
    if(g.supplyCount[gold] != testState.supplyCount[gold])
      printf("FAILED. Gold Count Mismatch. Expected: %d  Received: %d\n", g.supplyCount[gold], testState.supplyCount[gold]);
    else
      printf("Passed. Supply counts for treasure cards are the same\n");

  }
  return 0;
}