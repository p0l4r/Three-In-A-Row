///StarGame With AI
///Developed by team- AlephNull
///CSE365-Artificial Intelligence Project
///Team Members: Razwan Ahmed Tanvir (2015-1-60-111),
///              Shantanu Kumar Rahut (2015-1-60-114),
///              Sharfi Rahman (2015-1-60-134)

///========================================================================================================================================
///========================================================================================================================================





#include<iostream>
#include<bits/stdc++.h>
#include<windows.h>
#include <unistd.h>
#include "windows.h"
#include <mmsystem.h>


using namespace std ;

 HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
char box[15][15]; ///={'*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*','*'} ;
int inputColumn;
int column[10] ;
int recentInputColumn,recent_input_row,k ;
int PL2Input();///takes input of player 1
int PL1Input();///takes input player 2
bool PL1Win(int x);///checks if player 1 wins in recent input
bool PL2Win(int x);///checks if player 2 wins in recent input
bool win1 =false;
bool win2=false ;
int sequenceArray[26];
int Array_For_Saving_Moves_With_Utility[500000][26]={0};
int PossibleMoves[26],MovesCounter=0;///collect moves
int XX=0 , YY; /// row and column counter for Array_For_Saving_Moves_With_Utility
int U_Counter; ///counter needed for increasing utility of a set
int RecenInputPL1 , RecenInputPL2;
int turn=0;
string username;
int NumberOfMoves = 0 ;
int MUSIC_FLAG=0;
FILE * sequenceFile ;
int getMoveForPL1();
int getMoveForPL2();
void playMoveSound();
void Newgame();
void StoreValue();
int Check_Utility_Of_Moves_for_player_1();
int Check_Utility_Of_Moves_for_player_2();
int BlockTheWinningMovePL1();
int BlockTheWinningMovePL2();
int PL1WinningMove();
int PL2WinningMove();
void initializeSequencwArray();
void color (unsigned short v);
void print();
void settings();
int EasyPlay_PL1();
int EasyPlay_PL2();
int HardPlay_PL1();
int HardPlay_PL2();

void playMoveSoundSettings();


int who_will_play_first=0;
int GameMode=3;

///main function starts from here
int main(){

    int choice;
    initializeSequencwArray();
cout<<endl<<"\t\t\tPlease Enter Your User Name: ";
            getline(cin,username);
            cout<<endl<<endl;
    do{

        color(7);

        StoreValue(); ///stores moves from file to Array_For_Saving_Moves_With_Utility array
        U_Counter=-1;

        cout<<"\t\t\t1.Newgame\n\n\t\t\t2.How to play\n\n\t\t\t3.Game Mode\n\n\t\t\t4.Settings\n\n\t\t\t5.Exit\n\n\n";

        cout<<"\t\t\tEnter Your Choice: ";
        cin>>choice;
        if(choice==1){
         cout<<endl<<endl;
            for(int j=0;j<5;j++){
                for(int l=0;l<5;l++){
                    box[j][l]='*';
                }
            } ///initializing the board again for a new game
        cout<<"\n\t\t\tSo, You want to play with me Human ?\n\n\t\t\tIf want to make the first move Press 1\n\n\t\t\tOr else Press 0 : ";
        cin>>who_will_play_first;
        if(who_will_play_first==1){
            turn=1;
        }
        else{
            turn=0;
        }
            cout<<endl;
            turn++;
            if(MUSIC_FLAG==0){
             PlaySound(TEXT("background.wav"), NULL, SND_FILENAME | SND_ASYNC);
            }

            Newgame();

        }
        else if(choice==5){
                cout<<endl<<endl;
            break;
            cout<<"\t\t\tInvalid Input!"<<endl;
        }
        else if(choice==3){
            cout<<endl<<endl;
            cout<<"\t\t\tChoose Game Mode ( Default Set To AI )\n";
            cout<<"\t\t\t1) EASY mode (press 1)\n";
            cout<<"\t\t\t2) HARD mode (press 2)\n";
            cout<<"\t\t\t3) AI mode  (press 3)\n";
            cout<<"\t\t\tEnter Your Choice: ";
            cin>>GameMode;
            if(GameMode==1){
                cout<<"\t\t\tGame Mode has been set to EASY.\n\n";
            }
            else if(GameMode==2){
                cout<<"\t\t\tGame Mode has been set to HARD.\n\n";
            }
            else if(GameMode==3){
                cout<<"\t\t\tGame Mode has been set to AI.\n\n";
            }
            else{
                cout<<"\t\t\tInvalid Input Given.\n\n";
                cout<<"\t\t\tGame Mode has been set to AI by Default.\n\n";
                GameMode=3;
            }
        }
        else if(choice==4){

            settings();

        }
        else if(choice==2){
                cout<<endl<<endl;
                ///stating the game rules
            cout<<"\t\t\tPLAYER INPUT:Choose your column(1 to 5)to place\n\t\t\t your sign.\n\t\t\tTry that 3 signs remain together vertically\n\t\t\t , horizontally or diagonally.\n\t\t\tVery first input of each column would be\n\t\t\t placed at the bottom and\n\t\t\tthen each input will be stacked\n\t\t\t upon existing input.\n"<<endl<<endl;
             for(int j=0;j<10;j++){
                for(int l=0;l<10;l++){
                    box[j][l]='*';
                }
            }
            box[5][0]='A';
            box[4][1]='A';box[3][2]='A';box[2][3]='A';
            print();
            cout<<"\t\t\tThis is a sample winning combination (diagonally)\n\t\t\t for player 1 !"<<endl<<endl<<endl;
        }
        else{
            cout<<endl<<endl<<"\t\t\tInvalid Input !!!"<<endl<<endl<<endl;
        }

}while(choice!=5);
}
///main function ends here





///other functions start from here

void initialize_box(){  ///initializes box for a new game  , box means a 2-D array
    for(int i=0;i<15;i++){
        for(int j =0;j<15;j++){
            box[i][j]='*';
        }
    }
}


void initialize_Column(){ ///initializes column of the box for a new game , box means a 2-D array
    for(int i=0;i<5;i++){
        column[i] = 5 ;
    }
}


void initializeSequencwArray(){ /// initializes sequence array that will keep the moves of a current ongoing game
    for(int i=0;i<25;i++)
        sequenceArray[i]=-1;
}


void PrintGameSequenceArray (){   /// saves the sequence array in the file
    for(int i = 0 ; sequenceArray[i]!=-1 ;i++ ){
        fprintf(sequenceFile,"%d ",sequenceArray[i]);
    }

}


void PrintPossibleMovesArray(){  ///prints possible moves from the array
    cout<<endl<<"Possible Moves Array:";
    for(int i=0;i<MovesCounter;i++)
        cout<<PossibleMoves[i]<<" ";
        cout<<endl;
}


void color (unsigned short v) {   /// color function
    HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hcon, v);
}


void playMoveSound(){  ///makes beep sound for every move
    Beep (500,200);
}



void print(){ ///prints the board(box)
        color(14);
        cout<<endl;
        cout<<"\t\t\t1   2   3   4   5  "<<endl;
        cout<<"\t\t\t"<<char(25)<<"   "<<char(25)<<"   "<<char(25)<<"   "<<char(25)<<"   "<<char(25)<<"   "<<endl;//displaying arrow key
        cout<<"\t\t\t------------------"<<endl;
        SetConsoleTextAttribute(hConsole, 11);
        for(int i=0;i<5;i++){
            cout<<"\t\t\t";

            for(int j=0;j<5;j++){

                if(box[i][j]=='B'){
                    SetConsoleTextAttribute(hConsole, 11);
                }
                else if(box[i][j]=='A'){
                    SetConsoleTextAttribute(hConsole, 9);
                }
                else{
                    SetConsoleTextAttribute(hConsole, 14);
                }

                cout<<box[i][j]<<"   ";
        }
            cout<<endl<<endl;
    }
}



void settings(){
if(MUSIC_FLAG==0){
    cout<<"\t\t\tMusic is On.\n\n\t\t\tPress 1 to Off:";
    cin>>MUSIC_FLAG;
    cout<<"\n\n";
    if(MUSIC_FLAG==1){
          PlaySound(TEXT("beep-08b.wav"), NULL, SND_FILENAME | SND_ASYNC);
        cout<<"\t\t\tMusic is Off.\n\n";
    }
    else if(MUSIC_FLAG==0){
        cout<<"\t\t\tNo change was made.\n\n";
    }
    else{
        cout<<"\t\t\tInvalid Input.\n\n";
        MUSIC_FLAG=0;
        cout<<"\t\t\tMusic is On By Default.\n\n";
    }
}
else if(MUSIC_FLAG==1){
    cout<<"\t\t\tMusic is Off.\n\n\t\t\tPress 0 to On:";
        cin>>MUSIC_FLAG;
        cout<<"\n\n";
    if(MUSIC_FLAG==0){
        cout<<"\t\t\tMusic is On.\n\n";
    }
    else if(MUSIC_FLAG==1){
        cout<<"\t\t\tNo change was made.\n\n";
    }
    else{
        cout<<"\t\t\tInvalid Input.\n\n";
        MUSIC_FLAG=1;
        cout<<"\t\t\tMusic is Off By Default.\n\n";
    }
}
else{
        cout<<"\t\t\tInvalid Input.\n\n";
        MUSIC_FLAG=0;
        cout<<"\t\t\tMusic is On By Default.\n\n";
}

}


int PL1Input(){  /// player 1 (A) input
         SetConsoleTextAttribute(hConsole, 10);
         cout<<"\t\t\tPlayer 1 choice column:";



            if(turn%2!=0){
            Sleep(1000);
              if(GameMode==3){
                 inputColumn= getMoveForPL1() ;
              }
              else if(GameMode==2){
                inputColumn=HardPlay_PL1();
              }
              else if(GameMode==1){
                inputColumn=EasyPlay_PL1();
              }
            }
            else{
                cin>>inputColumn;
            }

            playMoveSound();

            if(inputColumn<1 || inputColumn>5 || column[inputColumn-1]<=0){ ///checking the over flow of player's input
                cout<<"\t\t\tInvalid Input.Input Correctly!"<<endl;
                return -1;
            }

            sequenceArray[NumberOfMoves++] = inputColumn ;

            inputColumn = inputColumn-1;
            box[column[inputColumn]-1][inputColumn]='A' ; ///inserting the input into the board
            column[inputColumn]--; /// decrementing the input column value i.e. decrementing top value of a column
            PossibleMoves[MovesCounter++]= inputColumn+1;
            print();

            return inputColumn ;

}



int PL2Input(){ /// player 2 (B) input
            SetConsoleTextAttribute(hConsole, 10);
            cout<<"\t\t\tPlayer 2 choice column:";

            if(turn%2==0){
             Sleep(1000);
              if(GameMode==3){
                 inputColumn= getMoveForPL2() ;
              }
              else if(GameMode==2){
                inputColumn=HardPlay_PL2();
              }
              else if(GameMode==1){
                inputColumn=EasyPlay_PL2();
              }
            }
            else{
                cin>>inputColumn;
            }
            playMoveSound();


            if(inputColumn<1 || inputColumn>5 || column[inputColumn-1]<=0){
                cout<<"\t\t\tInvalid Input!Input correctly"<<endl;
                return -1;
            }

            sequenceArray[NumberOfMoves++] = inputColumn ;

            inputColumn = inputColumn-1 ;///col starts from 0

            box[column[inputColumn]-1][inputColumn] = 'B'; ///inserting P2 input in board
            column[inputColumn]-- ; /// decrementing the input column value i.e. decrementing top value of a column
            PossibleMoves[MovesCounter++]=inputColumn+1 ;

            print();
            return inputColumn;

}


bool PL1Win(int recentInputColumn){  ///conditions where player 1 will win
            recent_input_row = column[recentInputColumn] ; /// here recentInputColumn is the recent input column and recent_input_row is the recent input row
           if(k>1){
           if((box[recent_input_row][recentInputColumn]=='A'&& box[recent_input_row+1][recentInputColumn]=='A' && box[recent_input_row+2][recentInputColumn]=='A')
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn]=='A' && box[recent_input_row-2][recentInputColumn]=='A')
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row][recentInputColumn+1]=='A' && box[recent_input_row][recentInputColumn+2]=='A' )
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn+1]=='A' && box[recent_input_row-2][recentInputColumn+2]=='A')
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row+1][recentInputColumn-1]=='A' && box[recent_input_row+2][recentInputColumn-2]=='A')
              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row][recentInputColumn-1]=='A' && box[recent_input_row][recentInputColumn-2]=='A')
              || (box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn-1]=='A' && box[recent_input_row-2][recentInputColumn-2]=='A')
              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row+1][recentInputColumn-1]=='A' && box[recent_input_row+2][recentInputColumn-2]=='A')

              ///------newly added

              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn+1]=='A' && box[recent_input_row+1][recentInputColumn-1]=='A')
              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row-1][recentInputColumn-1]=='A' && box[recent_input_row+1][recentInputColumn+1]=='A')
              ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row][recentInputColumn-1]=='A' && box[recent_input_row][recentInputColumn+1]=='A')
                         ||(box[recent_input_row][recentInputColumn]=='A' && box[recent_input_row+1][recentInputColumn+1]=='A' && box[recent_input_row+2][recentInputColumn+2]=='A')
              ){///checking that vertical recent_input_row or horizontalrecent_input_row win or not
                return true;
           }
            else{
                return false ;
            }
        }
        return false ;
}



bool PL2Win(int recentInputColumn){   ///conditions where player 2 will win
           recent_input_row = column[recentInputColumn];
           if(k>2){
                ///checking the winning conditions for everrecent_input_row single input . an input has 8 possible combination to check up,down,left,right,upright diagonal,upleft diagonal,downright diagonal , downleft diagonal
           if((box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row+1][recentInputColumn]=='B' && box[recent_input_row+2][recentInputColumn]=='B' )
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn]=='B' && box[recent_input_row-2][recentInputColumn]=='B')
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row][recentInputColumn+1]=='B' && box[recent_input_row][recentInputColumn+2]=='B' )
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn+1]=='B' && box[recent_input_row-2][recentInputColumn+2]=='B')
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row+1][recentInputColumn-1]=='B' && box[recent_input_row+2][recentInputColumn-2]=='B')
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row][recentInputColumn-1]=='B' && box[recent_input_row][recentInputColumn-2]=='B')
              || (box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn-1]=='B' && box[recent_input_row-2][recentInputColumn-2]=='B')
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row+1][recentInputColumn-1]=='B' && box[recent_input_row+2][recentInputColumn-2]=='B')

              ///---newly added

              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn+1]=='B' && box[recent_input_row+1][recentInputColumn-1]=='B')
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row-1][recentInputColumn-1]=='B' && box[recent_input_row+1][recentInputColumn+1]=='B')
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row][recentInputColumn-1]=='B' && box[recent_input_row][recentInputColumn+1]=='B')
              ||(box[recent_input_row][recentInputColumn]=='B' && box[recent_input_row+1][recentInputColumn+1]=='B' && box[recent_input_row+2][recentInputColumn+2]=='B')

              ){///checking that verticallrecent_input_row or horizontallrecent_input_row win or not

                return true;
           }
           else{
            return false ;
           }
           }
           return false ;
}


void Newgame(){
    int UtilityValue;
    initialize_Column();
    initialize_box();
    NumberOfMoves = 0 ;
    MovesCounter = 0;
    sequenceFile = fopen ("GameSequence.txt","a");
    print();
    for(k=0; ;k++){
        if(k%2==0){
                for( ; ; ){
                    recentInputColumn=PL1Input();
                    if(recentInputColumn==-1){
                        continue;
                    }
                    else{
                        break;
                    }
                }

           win1 = PL1Win(recentInputColumn) ; /// checks if player 1 wins for the recent input
           if(win1==true){
            UtilityValue=50;
            color(10);

           if(turn%2!=0){
            PlaySound(TEXT("mock.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout<<"\t\t\t================"<<endl;
            cout<<"\t\t\t|COMPUTER Wins!|"<<endl;
            cout<<"\t\t\t================"<<endl<<endl<<endl;
           }
           else{
            cout<<"\t\t\t================"<<endl;
            cout<<"\t\t\t|"<<username<<" Wins!|"<<endl;
            cout<<"\t\t\t================"<<endl<<endl<<endl;
           }
            PrintGameSequenceArray();
            fprintf(sequenceFile,"%d",UtilityValue); /// winning utility for player 1 is 50 and player 2 is 100
            fprintf(sequenceFile,"\n");
            fclose(sequenceFile);
            break;
           }
        } ///end of taking input from player 1111111111

        if(k%2==1){
                   for( ; ; ){
                    recentInputColumn=PL2Input();
                    if(recentInputColumn==-1){
                        continue;
                    }
                    else{
                        break;
                    }
                }
            win2 = PL2Win(recentInputColumn) ; /// checks if player 2 wins for the recent input
            if(win2==true){
                UtilityValue = 100;
                color(11);
            if(turn%2==0){
            PlaySound(TEXT("mock.wav"), NULL, SND_FILENAME | SND_ASYNC);
            cout<<"\t\t\t================"<<endl;
            cout<<"\t\t\t|COMPUTER Wins!|"<<endl;
            cout<<"\t\t\t================"<<endl<<endl<<endl;
           }
           else{
            cout<<"\t\t\t================"<<endl;
            cout<<"\t\t\t|"<<username<<" Wins!|"<<endl;
            cout<<"\t\t\t================"<<endl<<endl<<endl;
           }
                PrintGameSequenceArray();
                fprintf(sequenceFile,"%d",UtilityValue); /// winning utility for player 2 is 100
                fprintf(sequenceFile,"\n");
                fclose(sequenceFile);
                break;
            }
        }///end of taking input player 2

    }


}



void StoreValue(){  ///stores value from file in a array for checking and matching previous learned moves with new moves
sequenceFile = fopen ("GameSequence.txt","a");
int ValueFromFile;
int Counter_For_Utility_Space ;
ifstream SequenceValue("GameSequence.txt");
while(!SequenceValue.eof()){
YY=0;
Counter_For_Utility_Space=XX;
    for( ; ; ){
    SequenceValue>>ValueFromFile;
        if((ValueFromFile != 50) && (ValueFromFile != 100)){
            Array_For_Saving_Moves_With_Utility[XX][YY]=ValueFromFile;
            YY++;
        }
        else if(ValueFromFile==50 || ValueFromFile==100){
            Array_For_Saving_Moves_With_Utility[Counter_For_Utility_Space][25]=ValueFromFile;
            break;
        }
    }
XX++;
}
}



int Check_Utility_Of_Moves_for_player_1(){    /// find moves for computer when computer is  first player

    for(int FileRow=0;FileRow<18;FileRow++){
            int Possible_Moves_Array_Position=0 ;
        if(Array_For_Saving_Moves_With_Utility[FileRow][25]==50){
        for(int FileColumn=0;FileColumn<=MovesCounter;FileColumn++,Possible_Moves_Array_Position++){
            if(Array_For_Saving_Moves_With_Utility[FileRow][FileColumn]==PossibleMoves[Possible_Moves_Array_Position]) {
                if(Possible_Moves_Array_Position==MovesCounter-1){
                    int ComputerMoveDecided=  Array_For_Saving_Moves_With_Utility[FileRow][FileColumn+1];
                    return ComputerMoveDecided ;
                }
            }
            else
                break ;

        }
        }///inner loop ends
        else{
                continue;

        }
    }///outer loop ends
    int RandomMove = rand()%5+1 ;
    return RandomMove ;
}


int Check_Utility_Of_Moves_for_player_2(){  /// find moves for computer when computer is  second player

for(int FileRow=0;FileRow<18;FileRow++){
            int Possible_Moves_Array_Position=0 ;
        if(Array_For_Saving_Moves_With_Utility[FileRow][25]==100){
        for(int FileColumn=0;FileColumn<=MovesCounter;FileColumn++,Possible_Moves_Array_Position++){
            if(Array_For_Saving_Moves_With_Utility[FileRow][FileColumn]==PossibleMoves[Possible_Moves_Array_Position]) {
                if(Possible_Moves_Array_Position==MovesCounter-1){
                    int ComputerMoveDecided=  Array_For_Saving_Moves_With_Utility[FileRow][FileColumn+1];
                    return ComputerMoveDecided ;
                }
            }
            else
                break ;

        }
        }///inner loop ends
        else{
                continue;

        }
    }///outer loop ends
    int RandomMove = rand()%5+1 ;
    return RandomMove ;
}




int BlockTheWinningMovePL1(){  ///block winning move of player 2 for player 1
    for(int startColumn=0;startColumn<5;startColumn++){
       if(column[startColumn]>0){
        if(box[column[startColumn]-1][startColumn+1]=='B' && box[column[startColumn]-1][startColumn+2]=='B'){ ///1st *   B   B

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-1-1][startColumn+1]=='B' && box[column[startColumn]-2-1][startColumn+2]=='B'){/// 2nd   B

            return startColumn+1 ;                                                                                  ///    B
        }                                                                                                         /// *

        else if(box[column[startColumn]+1-1][startColumn]=='B' && box[column[startColumn]+2-1][startColumn]=='B'){ ///   *  3rd

            return startColumn+1 ;                                                                               ///   B
        }                                                                                                      ///   B

        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn-2]=='B'){///         4th

            return startColumn+1 ;                                                                              ///   B  B  *
        }                                                                                                     ///

        else if(box[column[startColumn]+1-1][startColumn-1]=='B' && box[column[startColumn]+2-1][startColumn-2]=='B'){///         *    5th

            return startColumn+1 ;                                                                                  ///      B
        }                                                                                                         ///   B

        else if(box[column[startColumn]+1-1][startColumn-1]=='B' && box[column[startColumn]-1-1][startColumn+1]=='B'){///       B    6th

            return startColumn+1 ;                                                                              ///        *
        }                                                                                                     ///     B

        else if(box[column[startColumn]-1-1][startColumn-1]=='B' && box[column[startColumn]+1-1][startColumn+1]=='B'){///   B       7th

            return startColumn+1 ;                                                                                  ///     *
        }                                                                                                           ///     B

        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn+1]=='B'){ ///1st    B    *    B

            return startColumn+1 ;
        }
        }





    }
    return -1 ;
}




int PL1WinningMove(){  ///winning move for player 1 when player 1 has two in a row

   for(int startColumn=0;startColumn<5;startColumn++){

        if(box[column[startColumn]-1][startColumn+1]=='A' && box[column[startColumn]-1][startColumn+2]=='A'){ ///1st *   A   A

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-1-1][startColumn+1]=='A' && box[column[startColumn]-2-1][startColumn+2]=='A'){/// 2nd   A

            return startColumn+1 ;                                                                                  ///    A
        }                                                                                                         /// *

        else if(box[column[startColumn]+1-1][startColumn]=='A' && box[column[startColumn]+2-1][startColumn]=='A'){ ///     *  3rd

            return startColumn+1 ;                                                                               ///   A
        }                                                                                                      ///   A

        else if(box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn-2]=='A'){///         4th

            return startColumn+1 ;                                                                              ///   A  A  *
        }                                                                                                     ///

        else if(box[column[startColumn]+1-1][startColumn-1]=='A' && box[column[startColumn]+2-1][startColumn-2]=='A'){///         *    5th

            return startColumn+1 ;                                                                                  ///      A
        }                                                                                                         ///   A

        else if(box[column[startColumn]+1-1][startColumn-1]=='A' && box[column[startColumn]-1-1][startColumn+1]=='A'){///       A    6th

            return startColumn+1 ;                                                                              ///        *
        }                                                                                                     ///     A

        else if(box[column[startColumn]-1-1][startColumn-1]=='A' && box[column[startColumn]+1-1][startColumn+1]=='A'){///  A       7th

            return startColumn+1 ;                                                                                  ///     *
        }                                                                                                        ///         A


    }
    return -1 ;
}



int BlockTheWinningMovePL2(){    ///block winning move of player 1 for player 2

    for(int startColumn=0;startColumn<5;startColumn++){

       if(column[startColumn]>0){
        if(box[column[startColumn]-1][startColumn+1]=='A' && box[column[startColumn]-1][startColumn+2]=='A'){ ///1st *   A   A

            return startColumn+1 ;
        }
        else if(box[column[startColumn]-1-1][startColumn+1]=='A' && box[column[startColumn]-2-1][startColumn+2]=='A'){/// 2nd   A

            return startColumn+1 ;                                                                                  ///    A
        }                                                                                                         /// *

        else if(box[column[startColumn]+1-1][startColumn]=='A' && box[column[startColumn]+2-1][startColumn]=='A'){ ///   *  3rd

            return startColumn+1 ;                                                                               ///   A
        }                                                                                                      ///   A

        else if(box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn-2]=='A'){///         4th

            return startColumn+1 ;                                                                              ///   A  A  *
        }                                                                                                     ///

        else if(box[column[startColumn]+1-1][startColumn-1]=='A' && box[column[startColumn]+2-1][startColumn-2]=='A'){///         *    5th

            return startColumn+1 ;                                                                                  ///      A
        }                                                                                                         ///   A

        else if(box[column[startColumn]+1-1][startColumn-1]=='A' && box[column[startColumn]-1-1][startColumn+1]=='A'){///       A    6th

            return startColumn+1 ;                                                                              ///        *
        }                                                                                                     ///     A

        else if(box[column[startColumn]-1-1][startColumn-1]=='A' && box[column[startColumn]+1-1][startColumn+1]=='A'){///  A       7th

            return startColumn+1 ;                                                                                  ///     *
        }
                                                                                                                     ///    A

        else if(box[column[startColumn]-1][startColumn-1]=='A' && box[column[startColumn]-1][startColumn+1]=='A'){ ///1st    A    *    A  8th

            return startColumn+1 ;
        }

        }



    }
    return -1 ;
}




int PL2WinningMove(){   ///winning move for player 2 when player 2 has two in a row

   for(int startColumn=0;startColumn<5;startColumn++){
            //cout<<endl<<"In loop = ("<<column[startColumn]<<","<<startColumn<<")"<<endl;
        if(box[column[startColumn]-1][startColumn+1]=='B' && box[column[startColumn]-1][startColumn+2]=='B'){ ///1st *   B   B
            //cout<<endl<<"In 1st Condition"<<endl;
            return startColumn+1 ;
        }
        else if(box[column[startColumn]-1-1][startColumn+1]=='B' && box[column[startColumn]-2-1][startColumn+2]=='B'){/// 2nd   B
            //cout<<endl<<"In 2nd Condition"<<endl;
            return startColumn+1 ;                                                                                  ///    B
        }                                                                                                         /// *

        else if(box[column[startColumn]+1-1][startColumn]=='B' && box[column[startColumn]+2-1][startColumn]=='B'){ ///   *  3rd
            //cout<<endl<<"In 3rd Condition"<<endl;
            return startColumn+1 ;                                                                               ///   B
        }                                                                                                      ///   B

        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn-2]=='B'){///         4th
            //cout<<endl<<"In 4th Condition"<<endl;
            return startColumn+1 ;                                                                              ///   B  B  *
        }                                                                                                     ///

        else if(box[column[startColumn]+1-1][startColumn-1]=='B' && box[column[startColumn]+2-1][startColumn-2]=='B'){///         *    5th
            //cout<<endl<<"In 5th Condition"<<endl;
            return startColumn+1 ;                                                                                  ///      B
        }                                                                                                         ///   B

        else if(box[column[startColumn]+1-1][startColumn-1]=='B' && box[column[startColumn]-1-1][startColumn+1]=='B'){///       B    6th
            //cout<<endl<<"In 6th Condition"<<endl;
            return startColumn+1 ;                                                                              ///        *
        }                                                                                                     ///     B

        else if(box[column[startColumn]-1-1][startColumn-1]=='B' && box[column[startColumn]+1-1][startColumn+1]=='B'){///  B       7th
            //cout<<endl<<"In 7th Condition"<<endl;
            return startColumn+1 ;                                                                                  ///     *
        }                                                                                                        ///         B

        else if(box[column[startColumn]-1][startColumn-1]=='B' && box[column[startColumn]-1][startColumn+1]=='B'){ ///1st    B    *    B  8th

            return startColumn+1 ;
        }


    }
    return -1 ;
}



int getMoveForPL1(){   ///Difficulty Level AI: Computer 1st player
       int BlockPosition = BlockTheWinningMovePL1();
       int WinningMove = PL1WinningMove();
       int MoveFromFile = Check_Utility_Of_Moves_for_player_1();

       if(WinningMove!=-1){
            return WinningMove ;
       }
       else if(BlockPosition!=-1){
            return BlockPosition;
       }
       else {
            SetConsoleTextAttribute(hConsole, 15);
            cout<<"COMPUTER is thinking ";
            for(int dot=0;dot<10;dot++){
                cout<<".";
                Sleep(100);
            }
            cout<<endl;
            return MoveFromFile;
       }

}






int getMoveForPL2(){   ///Difficulty Level AI: Computer 2nd player
       int BlockPosition = BlockTheWinningMovePL2();
       int WinningMove = PL2WinningMove();
       int MoveFromFile = Check_Utility_Of_Moves_for_player_2();

       if(WinningMove!=-1){
            return WinningMove ;
       }
       else if(BlockPosition!=-1){
            return BlockPosition;
       }
       else {
            SetConsoleTextAttribute(hConsole, 15);
            cout<<"COMPUTER is thinking ";
            for(int dot=0;dot<10;dot++){
                cout<<".";
                Sleep(100);
            }
            cout<<endl;
            return MoveFromFile;
       }

}





int EasyPlay_PL1(){ ///Difficulty Level Easy: Computer 1st player
int WinningMove = PL1WinningMove();

int randomMove= rand()%5+1;

       if(WinningMove!=-1){
            return WinningMove ;
       }
       else {

            return randomMove;
       }
}


int EasyPlay_PL2(){ ///Difficulty Level Easy: Computer 2nd player
int WinningMove = PL2WinningMove();
int randomMove= rand()%5+1;

       if(WinningMove!=-1){
            return WinningMove ;
       }
       else {

            return randomMove;
       }
}



int HardPlay_PL1(){ ///Difficulty Level Hard: Computer 1st player
int BlockPosition = BlockTheWinningMovePL1();
int WinningMove = PL1WinningMove();
int randomMove= rand()%5+1;

       if(WinningMove!=-1){
            return WinningMove ;
       }
       else if(BlockPosition!=-1){
        return BlockPosition;
       }
       else {

            return randomMove;
       }
}

int HardPlay_PL2(){ ///Difficulty Level Hard: Computer 2nd player
int BlockPosition = BlockTheWinningMovePL2();
int WinningMove = PL2WinningMove();
int randomMove= rand()%5+1;

       if(WinningMove!=-1){
            return WinningMove ;
       }
       else if(BlockPosition!=-1){
        return BlockPosition;
       }
       else {

            return randomMove;
       }
}
