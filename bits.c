/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  /*
  * Computes the negated version of the number using the 2's complement method by inverting the bits
  * and then adding 1.
  *                  negatedX = ~x + 1;
  */

  //Declare variables according to dlc style

  int negatedX = 0; //value to be returned initialized to 0

  negatedX = (~x) + 1;

  return negatedX;
}

/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  /*
  * Shifts n to the left 3 to multiply it by 8.
  * This tells us how how many bits we need to shift c - 0 || 8 || 16 || 24
  * Uses a variable Y initialized to 0xFF then shifted left by (n*3) bits
  * Y is then inverted and then bitwise ANDED with x in order to copy the surrounding bits were keeping
  * Lastly this final value is bitwise OR'd with C in order to fill in the missing byte
  */

  int bitsToShiftBy = 0;
  int y = 0;
  int modifiedX = 0; //value to be returned

  bitsToShiftBy = (n << 3); //bitsToShiftBy = n * 8
  c = c << bitsToShiftBy; //putting byte in proper place
  y = 0xFF;
  y = y << bitsToShiftBy;
  y = ~y; //inverting y to turn surrounding bits to 1
  modifiedX = y & x; //copying surrounding bits from x into modifiedX

  //Lastly or modifiedX with c in order to replace the missing byte
  modifiedX = modifiedX | c;

  return modifiedX;
}

/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
  /*
  * Copies each byte that needs to be swapped from x and hold them into separate variables
  * Then moves the byte into the new correct position still inside the temp variables
  * Then 0s out both bytes that are being swapped from X. Then ORs all 3 together to return the new
  * correct value.
  */
    int modifiedX = 0; //value to be returned
    int b2sbyN = 0; //bits to shift by to extract n
    int b2sbyM = 0; //bits to shift by to extract m
    int helper = 0; //helper variable
    int helper2 = 0;
    int nPlacer = 0; //variable to hold the Nth byte in its correct location
    int mPlacer = 0; //variable to hold the Mth byte in its correct location

    b2sbyN = (n << 3);
    b2sbyM = (m << 3);

    helper = 0xFF;
    helper = helper << b2sbyN; //helper is now in the correct location to copy nth byte

    //set up nPlacer
    nPlacer = x & helper; //nPlacer now contains nth byte in its place

    //move nth byte in nPlacer to the location of the Mth byte
    nPlacer = nPlacer >> b2sbyN;
    nPlacer = nPlacer & 0xFF;
    nPlacer = nPlacer << b2sbyM; //nPlacer is ready to go!

    helper2 = 0xFF;
    helper2 = helper2 << b2sbyM; //helper2 is now in the correct location to copy mth byte

    //set up mPlacer
    mPlacer = x & helper2; //mPlacer now contains mth byte in its place

    //move mth byte in mPlacer to the location of the Nth byte
    mPlacer = mPlacer >> b2sbyM;
    mPlacer = mPlacer & 0xFF;
    mPlacer = mPlacer << b2sbyN; //mPlacer is ready to go!

    helper = helper | helper2; //helper can now extract nth and mth byte
    helper = ~helper; //helper can now extract everything that is not being swapped

    modifiedX = helper & x; //modifiedX now contains everything but the swapped bytes

    //Lastly bitwise or modifiedX with nPlacer and mPlacer in order to place in the missing bytes
    modifiedX = modifiedX | nPlacer | mPlacer;

    return modifiedX;
}
/*
 * isNotEqual - return 0 if x == y, and 1 otherwise
 *   Examples: isNotEqual(5,5) = 0, isNotEqual(4,5) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 6
 *   Rating: 2
 */
int isNotEqual(int x, int y) {
  /*
  * Tests if the given numbers are equal by XORing them and then proceeding to use the
  * ! (not) operator on the result twice. This will in turn always return 0 if they are
  *  equal and 1 if they are not.
  */
  int result = 0; //value to be returned

  result = x ^ y;
  result = !result;
  result = !result;
  return result;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  /*
  * The conditional is calculated by making a bit mask by inverting the truth value of x then inverting
  * the result of that adding 1 and inverting the result of that. This mask is then used by ANDing it with
  * the Y and inverting the mask and ANDing it with Z. Finally ORing these results will give the correct
  * return value based off of X's truth value.
  */
  int result = 0;
  int helper = 0;
  int temp1 = 0;
  int temp2 = 0;

  helper = !x; //get the inverted truth value of x
  helper = ~helper;
  helper += 1;
  helper = ~helper; //helper is now all 1s for true and all 0s for false at this point

  temp1 = helper & y; //temp1 is now y for true and 0 for false
  temp2 = ~helper & z; //temp2 is now 0 for true and z for false

  result = temp1 | temp2; //result is now y for true and z for false

  return result;
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  /*
  * This solution works by getting any number other than 0 to eventually be all 0s while 0 will be all 1s
  * I then & this final result with 1 to copy the LSB and return it which will be the inverted truth value
  * of x.
  */
  int result = 0;
  int helper = 0;
  int msbCopy = 0;

  helper = 1;
  helper = 1 << 31;

  //copy MSB of x
  msbCopy = x & helper;
  msbCopy = msbCopy >> 31;

  //get rid of x's MSB
  x = x << 1;
  x = x | msbCopy; //put the MSB back into the LSB position

  result = ~x;
  result = result | helper; //ensure the number is negative
  result += 1;
  result = result >> 31; //result is 0 if x was 0 here or all 1s if x was a number > 0
  result = ~result; //invert the result and & with 1
  result = result & 1;

  return result;
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  /*
  * Calculates if x is greater than y by utilizing 1s complement subtraction to find the difference
  * b/w x and y. Then utilizes the inverted truth value on the MSB of the difference to be ANDed with
  * my inverted helper variable which figures out if the sign bits of x and y are the same or different.
  * The uninverted version of the helper variable is then ANDed with the MSB of x. This is all similar to
  * using a mask to choose a number to return like in the conditional function. The result returned is
  * the result of these two AND operations ORed together. 
  */
  int result = 0;
  int difference = 0;
  int invertedY = 0;
  int msbX = 0;
  int helper = 0;
  int temp1 = 0;
  int temp2 = 0;

  invertedY = ~y;

  difference = x + invertedY; //1s complement subtrcation

  difference = difference >> 31;
  difference = difference & 1;
  difference = !difference; //invert the truth value of the MSB of the difference of x and y

  msbX = y >> 31;
  msbX = msbX & 1;

  helper = x ^ y; //check if the MSB of the two numbers is the same or different
  helper = helper >> 31; //all 1s or all 0s now follow logic from conditional

  temp1 = ~helper & difference; //similar logic from conditional
  temp2 = helper & msbX;

  result = temp1 | temp2;

  return result;
}
/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  /*
  * Computes the Abolute Value of any given integer by first shifting x 31 bits to the right to get all 1s or 0s
  * Then xoring the result of that with x making the MSB 0. Then the 2s complement of the all 0s or all 1s is taken and added to
  * the result to remove it from the result.
  */
  int result = 0;
  int helper = 0;

  helper = x >> 31; //all 0s or all 1s
  result = x ^ helper;

  helper = ~helper + 1;

  result += helper;

  return result;
}
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  /*
  * Detects overflow by taking advantage of the knowledge that overflow occurs only when the MSB of the
  * sum is different than both of the operand's MSBs. This can be calculated by XORing the MSB of the sum
  * with both of the MSBs of the operands. If the result is a 1 we know they are different and if they
  * are different twice an AND operation on them will result in a 1. Therefore we can ! that result and
  * return 0 for overflow.
  */
  int result = 0;
  int msbX = 0;
  int msbY = 0;
  int msbRes = 0;
  int xorX = 0; //helper variables
  int xorY = 0;

  msbX = x >> 31; // get MSB of X
  msbY = y >> 31; //get MSB of Y

  msbX = msbX & 1;
  msbY = msbY & 1;

  msbRes = x + y;
  msbRes = msbRes >> 31;
  msbRes = msbRes & 1; //get MSB of result

  xorX = msbRes ^ msbX; //only 1 if theyre different
  xorY = msbRes ^ msbY; //only 1 if there different
  result = xorX & xorY; //only 1 if the MSB result was different than both therefore overflow

  result = !result; //invert truth value of result and return

  return result;
}
/*
 * bitParity - returns 1 if x contains an odd number of 0's
 *   Examples: bitParity(5) = 0, bitParity(7) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 4
 */
int bitParity(int x) {
  /*
  * Calculates if there are an odd number of 0s by effectively following the idea that XORing each bit
  * in the number together of an even number will result in a 0 for an even number of 0s or 1 for an
  * odd number of 1s. My algorithm accomplishes this by essentially splitting the number into groups of
  * bits and continuing to xor them together until all its have been affectively XORed with 0. Then I
  * return the LSB of the number which will contain the correct answer.
  */

  int result = 0;
  int copyX = 0;
  int helper = 0;

  copyX = x;
  copyX = copyX >> 16; //get left 16 bits of x.

  copyX = copyX ^ x; //XORed last 16 bits of each.
  helper = copyX;

  helper = helper >> 8; //left 8 bits of the 16 most right bits from copyX

  copyX = copyX ^ helper; //XORed last 8 bits of each
  helper = copyX;

  helper = helper >> 4; //left 4 bits of the 8 most right bits from copyX

  copyX = copyX ^ helper; //XORed last 4 bits of each
  helper = copyX;

  helper = helper >> 2; //left 2 bits of the 4 most right bits from copyX

  copyX = copyX ^ helper; //XORed last 2 bits of each
  helper = copyX;

  helper = helper >> 1; //left bit of the last 2 most right bits from copyX;

  copyX = copyX ^ helper; //least most significant bit now contains our answer

  result = copyX & 1;

  return result;
}
