/*
Write a function that takes a byte, reverses it, bit by bit (like the
example) and returns the result.

Your function must be declared as follows:

unsigned char	reverse_bits(unsigned char octet);
*/
unsigned char   reverse_bits(unsigned char octet)
{
    int i = 0;
    int bit = 0;

    while (i < 8)
    {
        bit = (bit << 1) | (octet & 1);
        octet >>= 1;
        i++;
    }
    return (bit);
}