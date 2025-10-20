# skrf_tests


mavlink.bin contains more garbage than supposed, from MavlinkV2 only STX and length fields looks valid ;-) 

Not used mavlink standard library on purpose (wanted to understand how things work).
mavlink tools from pymavlink package does not recognize the file as valid one.
I investigated the file using hex editor and manually extracted some fields and based on that information implemented the "parser". I do not have valid file for reference.

Parser prints invalid msgid field value because of invalid data.

if you have valid implementation for this task, I would like to see it, just curious.
Thx!
