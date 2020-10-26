///**************************************************///
///         >>  PIC18F2XXX/4XXX  PROGRAMMER  <<      /// 
///           created by : ASSAOUS OUSSAMA           ///
///               buffer configuration               ///
///**************************************************///
//------------------------------------------------------> erase device memory <----------------------------------------------------------------
//                                                     4-Bit command  |  Data Payload  | Core Instruction 
char   EraseBufer[16][3] = {{0x0E , 0x3C , 0x00 } , //      0000      |      0E 3C     |  MOVLW 3Ch
                            {0x6E , 0xF8 , 0x00 } , //      0000      |      6E F8     |  MOVWF TBLPTRU
                            {0x0E , 0x00 , 0x00 } , //      0000      |      0E 00     |  MOVLW 00h
                            {0x6E , 0xF7 , 0x00 } , //      0000      |      6E F7     |  MOVWF TBLPTRH    
                            {0x0E , 0x05 , 0x00 } , //      0000      |      0E 05     |  MOVLW 05h
                            {0x6E , 0xF6 , 0x00 } , //      0000      |      6E F6     |  MOVWF TBLPTRL
                            {0x3F , 0x3F , 0x0C } , //      1100      |      3F 3F     |  Write 3F3Fh to 3C0005h
                            {0x0E , 0x3C , 0x00 } , //      0000      |      0E 3C     |  MOVLW 3Ch
                            {0x6E , 0xF8 , 0x00 } , //      0000      |      6E F8     |  MOVWF TBLPTRU
                            {0x0E , 0x00 , 0x00 } , //      0000      |      0E 00     |  MOVLW 00h
                            {0x6E , 0xF7 , 0x00 } , //      0000      |      6E E7     |  MOVWF TBLPTRH
                            {0x0E , 0x04 , 0x00 } , //      0000      |      0E 04     |  MOVLW 04h
                            {0x6E , 0xF6 , 0x00 } , //      0000      |      6E F6     |  MOVWF TBLPTRL
                            {0x8F , 0x8F , 0x0C } , //      1100      |      8F 8F     |  Write 8F8Fh TO 3C0004h to erase entire device.
                            {0x00 , 0x00 , 0x00 } , //      0000      |      00 00     |  NOP
                            {0x00 , 0x00 , 0x00 } } ;//     0000      |      00 00     |  Hold PGD low until erase completes
//---------------------------------------------------------------------------------------------------------------------------------------------  

//---------------------------------------------------------> program memory <------------------------------------------------------------------
//                                                      4-Bit command  |  Data Payload        | Core Instruction 
char ProgramBuffer[26][3] = {{0x8E , 0xA6 , 0x00 } , //      0000      |     8E A6            | BSF EECON1, EEPGD 
                             {0x9C , 0xA6 , 0x00 } , //      0000      |     9C A6            | BCF EECON1, CFGS
                             {0x84 , 0xA6 , 0x00 } , //      0000      |     84 A6            | BSF EECON1, WREN
                             {0x0E , 0x00 , 0x00 } , //      0000      |     0E <Addr[21:16]> | MOVLW <Addr[21:16]>
                             {0x6E , 0xF8 , 0x00 } , //      0000      |     6E F8            | MOVWF TBLPTRU
                             {0x0E , 0x00 , 0x00 } , //      0000      |     0E <Addr[15:8]>  | MOVLW <Addr[15:8]>
                             {0x6E , 0xF7 , 0x00 } , //      0000      |     6E F7            | MOVWF TBLPTRH
                             {0x0E , 0x00 , 0x00 } , //      0000      |     0E <Addr[7:0]>   | MOVLW <Addr[7:0]>
                             {0x6E , 0xF6 , 0x00 } , //      0000      |     6E F6            | MOVWF TBLPTRL
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.
                             {0x00 , 0x00 , 0x0D } , //      1101      |     <MSB><LSB>       | Write 2 bytes and post-increment address by 2.                            
                             {0x00 , 0x00 , 0x0F } , //      1111      |     <MSB><LSB>       | Write 2 bytes and start programming.
                             {0x00 , 0x00 , 0x00 } } ; //    0000      |     00 00            | NOP - hold PGC high for time P9 and low for time P10.
//---------------------------------------------------------------------------------------------------------------------------------------------------

//-------------------------------------------------------> write EEPROM memory <----------------------------------------------------------------------
//                                                        4-Bit command  |  Data Payload        | Core Instruction 
char eeprombuffer[15][3] =      {{0x9E , 0xA6 , 0x00} ,//     0000       |     9E A6            | BCF EECON1, EEPGD  
                                 {0x9C , 0xA6 , 0x00} ,//     0000       |     9C A6            | BCF EECON1, CFGS
                                 {0x0E , 0x00 , 0x00} ,//     0000       |     0E <Addr>        | MOVLW <Addr>
                                 {0x6E , 0xA9 , 0x00} ,//     0000       |     6E A9            | MOVWF EEADR
                                 {0x0E , 0x00 , 0x00} ,//     0000       |     OE <AddrH>       | MOVLW <AddrH>
                                 {0x6E , 0xAA , 0x00} ,//     0000       |     6E AA            | MOVWF EEADRH
                                 {0x0E , 0x00 , 0x00} ,//     0000       |     0E <Data>        | MOVLW <Data>
                                 {0x6E , 0xA8 , 0x00} ,//     0000       |     6E A8            | MOVWF EEDATA
                                 {0x84 , 0xA6 , 0x00} ,//     0000       |     84 A6            | BSF EECON1, WREN
                                 {0x82 , 0xA6 , 0x00} ,//     0000       |     82 A6            | BSF EECON1, WR
                                 {0x50 , 0xA6 , 0x00} ,//     0000       |     50 A6            | MOVF EECON1, W, 0
                                 {0x6E , 0xF5 , 0x00} ,//     0000       |     6E F5            | MOVWF TABLAT
                                 {0x00 , 0x00 , 0x00} ,//     0000       |     00 00            | NOP
                                 {0x00 , 0x00 , 0x02} ,//     0010       |    <MSB><LSB>        | Shift out data
                                 {0x94 , 0xA6 , 0x00} };//    0000       |     94 A6            | BCF EECON1, WREN

//---------------------------------------------------------------------------------------------------------------------------------------------------

//---------------------------------------------------> ID Location Programming <---------------------------------------------------------------------
//                                               4-Bit command  |  Data Payload        | Core Instruction 
char idBuffer[13][3] = {{0x8E , 0xA6 , 0x00} ,//     0000       |      8E A6           | BSF EECON1, EEPGD
                        {0x9C , 0xA6 , 0x00} ,//     0000       |      9C A6           | BCF EECON1, CFGS
                        {0x0E , 0x20 , 0x00} ,//     0000       |      0E 20           | MOVLW 20h
                        {0x6E , 0xF8 , 0x00} ,//     0000       |      6E F8           | MOVWF TBLPTRU
                        {0x0E , 0x00 , 0x00} ,//     0000       |      0E 00           | MOVLW 00h
                        {0x6E , 0xF7 , 0x00} ,//     0000       |      6E F7           | MOVWF TBLPTRH
                        {0x0E , 0x00 , 0x00} ,//     0000       |      0E 00           | MOVLW 00h
                        {0x6E , 0xF6 , 0x00} ,//     0000       |      6E F6           | MOVWF TBLPTRL
                        {0x00 , 0x00 , 0x0D} ,//     1101       |    <MSB><LSB>        | Write 2 bytes and post-increment address by 2.
                        {0x00 , 0x00 , 0x0D} ,//     1101       |    <MSB><LSB>        | Write 2 bytes and post-increment address by 2.
                        {0x00 , 0x00 , 0x0D} ,//     1101       |    <MSB><LSB>        | Write 2 bytes and post-increment address by 2.
                        {0x00 , 0x00 , 0x0F} ,//     1111       |    <MSB><LSB>        | Write 2 bytes and start programming.
                        {0x00 , 0x00 , 0x00} };//    0000       |      00 00           | NOP - hold PGC high for time P9 and low for time P10.

//---------------------------------------------------------------------------------------------------------------------------------------------------

//-----------------------------------------------------> program configuration <---------------------------------------------------------------------
//                                                   4-Bit command  |  Data Payload        | Core Instruction 
char configbuffer[14][3] = {{0x8E , 0xA6 , 0x00} ,//      0000      |      8E A6           | BSF EECON1, EEPGD
                            {0x8C , 0xA6 , 0x00} ,//      0000      |      8C A6           | BSF EECON1, CFGS
                            {0x0E , 0x30 , 0x00} ,//      0000      |      0E 30           | MOVLW 30h
                            {0x6E , 0xF8 , 0x00} ,//      0000      |      6E F8           | MOVWF TBLPTRU
                            {0x0E , 0x00 , 0x00} ,//      0000      |      0E 00           | MOVLW 00h
                            {0x6E , 0xF7 , 0x00} ,//      0000      |      6E F7           | MOVWF TBLPRTH
                            {0x0E , 0x00 , 0x00} ,//      0000      |      0E 00           | MOVLW 00h
                            {0x6E , 0xF6 , 0x00} ,//      0000      |      6E F6           | MOVWF TBLPTRL
                            {0x00 , 0x00 , 0x0F} ,//      1111      |  <MSB ignored><LSB>  | Load 2 bytes and start programming.
                            {0x00 , 0x00 , 0x00} ,//      0000      |      00 00           | NOP - hold PGC high for time P9 and low for time P10.
                            {0x0E , 0x01 , 0x00} ,//      0000      |      0E 01           | MOVLW 01h
                            {0x6E , 0xF6 , 0x00} ,//      0000      |      6E F6           | MOVWF TBLPTRL
                            {0x00 , 0x00 , 0x0F} ,//      1111      |  <MSB><LSB ignored>  | Load 2 bytes and start programming.
                            {0x00 , 0x00 , 0x00} };//     0000      |      00 00           | NOP - hold PGC high for time P9 and low for time P10.
                                                       
//---------------------------------------------------------------------------------------------------------------------------------------------------
