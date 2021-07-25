#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main()
{
    char ch;
    int line=1;         //line
    int intlength=0;    //intlength
    int wordorkey=0;    //Keyword? true or false
    int wordlength=0;   //woedlength

    char integer[10];
    char word[20];
    char keywords[9][8]= {"int","move","to","loop","times","out","newline","add","sub"};
    char string[500];

    FILE*fileR;// File Read
    FILE*fileW;// File Write
    fileR=fopen("C:/Users/Ali/*****/myscript.ba","r"); //file to read whit .ba
    fileW=fopen("C:/Users/Ali/*****/myscript.lx","w");// file to write whit .lx

    ch=fgetc(fileR);// get firt char

    if(fileR != NULL)//File check
    {

        while(!feof(fileR) ) //continues unless error or end of file
        {
            int control=1; // control for unrecognized character

            if(ch ==' '|| ch=='\n' || ch=='\t')//space, tab, line break check
            {
                if(ch=='\n') //line counter
                    line++;

                ch=fgetc(fileR);// get char
                while(ch ==' '|| ch=='\n' || ch=='\t')
                {
                    if(ch=='\n') //line counter
                    line++;
                    ch=fgetc(fileR);
                }
            }


            if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')//integer check
            {
                integer[intlength]=ch;
                ch=fgetc(fileR);
                if(ch =='.'|| ch==',')
                {
                    printf("\tERROR : Decimal point should not be displayed .\n ");
                    printf("Line:%d",line);
                }

                while(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9') // integer after integer check
                {
                    intlength++;
                    integer[intlength]=ch;
                    ch=fgetc(fileR);
                }
                integer[intlength+1]='\0'; //final string assignment
                if(intlength>10) //int length error check
                {
                    printf("\tERROR : Maximum integer size is 10 digits .\n ");
                    printf("Line:%d",line);
                    return 0;
                }
                else
                {
                    fputs("IntConstant ",fileW); //puts operation to .lx file
                    fputs(integer, fileW);
                    fputs("\n",fileW);
                }
                memset(integer, 0, sizeof(integer)); //clearing array from ram
                intlength=0; //reset the counter
                continue;
                control=0;
            }
            if(ch=='-') //negative int check
            {
                integer[intlength]=ch;
                intlength++;
                ch=fgetc(fileR);
                if(ch==' ')//No spaces after '-'
                {   // I thing here is interpreter but we want show this error
                    printf("\tERROR :There should be no blank between the minus sign and the first digit.\n ");
                    printf("Line:%d",line);
                    return 0;
                }
                else if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')//same as integer check
                {
                    integer[intlength]=ch;
                    ch=fgetc(fileR);
                    while(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')
                    {
                        intlength++;
                        integer[intlength]=ch;
                        ch=fgetc(fileR);
                    }
                    integer[intlength+1]='\0';
                    if(intlength>10)
                    {
                        printf("\tERROR : Maximum integer size is 10 digits .\n ");
                        printf("Line:%d",line);
                        return 0;
                    }
                    else
                    {
                        fputs("IntConstant ",fileW); //puts operation to .lx file
                        fputs(integer, fileW);
                        fputs("\n",fileW);
                    }
                    memset(integer, 0, sizeof(integer));//clearing array from ram
                    intlength=0;
                    continue;
                    control=0;
                }
                else// I thing here is interpreter but we want show this error
                {
                    printf("\tERROR :The number must come after the minus.\n ");
                    printf("Line:%d",line);
                    return 0;
                }
            }

            if(ch=='.')//End Of Line
            {
                fputs("EndofLine\n",fileW);
                control=0;

            }
            if(ch==',')//Separator
            {
                fputs("Separator\n", fileW);
                control=0;

            }
            if(ch=='{'||ch=='}' || ch=='['||ch==']')//brackets check
            {
                if(ch=='{') //open comment
                {

                    ch=fgetc(fileR);

                    while(ch!=EOF && ch!='}')  //pass comment's char
                    {
                        ch=fgetc(fileR);
                    }
                    if(ch=='}')// close comment
                    {
                        ch=getc(fileR);
                        continue;
                    }
                    else if(ch==EOF)//file ending before comment ends
                    {
                        printf("ERROR :A big lexeme is just left open (a Comment or a string constant that starts but does not terminate before the end of file)");
                        printf("Line:%d",line);
                        return 0;
                    }

                }
                if(ch=='[')
                {
                    fputs("OpenBlock\n", fileW);//puts operation to .lx file
                }
                if(ch==']')
                {
                    fputs("CloseBlock\n", fileW);
                }
                control=0;

            }

            if(ch=='"')//strings check //open string
            {
                int counter=0;
                string[counter]=ch;
                counter++;

                ch=fgetc(fileR);

                while(ch!= '"' ) // pass string's char // close string
                {
                    string[counter]=ch;
                    counter++;
                    ch=fgetc(fileR);
                    if(ch==EOF) //file ending before string ends error
                    {
                        printf("ERROR :A big lexeme is just left open (a comment or a String constant that starts but does not terminate before the end of file)");
                        printf("Line:%d",line);
                        return 0;
                    }
                }
                string[counter]=ch;

                string[counter+1]='\0'; //final string assignment
                fputs("String Constants ",fileW ); //puts operation to .lx file
                fputs(string,fileW);
                fputs("\n",fileW);
                control=0;
            }

            if(('a' <= ch && ch <='z') || ('A' <= ch && ch <= 'Z'))//identifier and keywords check
            {

                wordorkey=0;
                wordlength=0;
                while(('a' <= ch && ch <='z')|| ('A' <= ch && ch <= 'Z') || (ch=='_')) //alphabetical char control
                {
                    if(wordlength>20) //max size check
                    {
                        printf("\tERROR : Maximum identifier size is 20 characters.  \n");
                        printf("Line:%d",line);
                        return 1;
                    }
                    word[wordlength]=ch;
                    wordlength++;
                    ch=fgetc(fileR);

                    if(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')//Check for integer after alphabetic value
                    {
                        word[wordlength]=ch;
                        wordlength++;
                        ch=fgetc(fileR);
                        while(ch=='0'||ch=='1'||ch=='2'||ch=='3'||ch=='4'||ch=='5'||ch=='6'||ch=='7'||ch=='8'||ch=='9')
                        {

                            word[wordlength]=ch;
                            wordlength++;
                            ch=fgetc(fileR);
                        }
                    }
                }
                word[wordlength]='\0';
                //KEYWORDS OR IDENIFIRE
                for(int x=0; x<9; x++)
                {
                    if(strcmp(word,keywords[x]) == 0 ) //If the word is keyword it enters this if and the wordorkey variable is 1.
                    {
                        fputs("Keyword ",fileW);
                        fputs(word,fileW);
                        fputs("\n",fileW);
                        wordorkey=1;
                        break;
                    }
                }

                if(wordorkey == 0 )// wordorkey = 1 => string is keyword
                {
                    fputs("Identifier ",fileW);
                    fputs(word,fileW);
                    fputs("\n",fileW);
                }
                memset(word, 0, sizeof(word));//clearing array from ram
                wordlength=0;
                control=0;
                continue;
            }


            if(control==1 && ch!=EOF) //unrecognized character check
            {
                printf("\tERROR : An unrecognized character is detected in code");
                printf("Line:%d",line);
                return 0;
            }
            ch=getc(fileR);
        }//while
    }//if
    return 0;
}//main



