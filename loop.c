
                for (int j = 0; j < 52; j++){
                    if (verbose){ 
                        if(j < 9) 
                            fprintf(stdout, "Card  %d: %d\n", j+1, cards[j]);
                        else      
                            fprintf(stdout, "Card %d: %d\n", j+1, cards[j]);
                    }

                    /* cleaner look, for cards 1-9, the format is Card  #: # */
                    /* (double space)                                        */
                    if(j < 9){
                        sprintf(buff, "Card  %d: %d\n", j+1, cards[j]);
                        send_data(clientConnection, buff, strlen(buff), flags);
                        
                        fflush(stdout);                        
                        
                        if (slowDeal) sleep(1);

                    /* cards 10-52, format is Cards #: # (single space) */
                    }else{
                        sprintf(buff, "Card %d: %d\n", j+1, cards[j]);
                        send_data(clientConnection, buff, strlen(buff), flags);
                        
                        fflush(stdout);

                        if (slowDeal) sleep(1);
                    }
                }
                break;
