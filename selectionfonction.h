//--------------------------------------------------------------------------
void selection(char test[]){
//selection fonction
    switch (test[1]){
        case '0':
             fonctionax(test);
            //code
            break;
        case 115:
            //code
            break;
        case 109:
            //code
            break;
        case 104: 
            //code
            break;
        case 106:
            //code
            break;
        case 108:
            //code
             break;
        case 97:
            //code
            break;
    }
}
//--------------------------------------------------------------------------
void fonctionax(char test[]){
//selection fonction
pc.putc(check());
    if (check()==bufferreception[15]){
                   
        switch (test[5]){
            case '0':
                pc.putc(0x00);
                envoieTrame();
                
                //code
                break;
            case '1':
                pc.putc(0x01);
                //code
                envoieTrame2();
                break;
            case '2':
                envoieTrame3();
                //code
                break;
        }
          
    }
}
