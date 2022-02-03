#include<stdio.h>
#include<stdlib.h>
#include<math.h>


int size;   //global variables for size and subgrid check
int temp;

// This function is used to find empty cell in sudoku and modify value in row and col and return 1 if exits 
// otherwise it return 0 to show that no empty block now present in sudoku
int findemptycell(int arr[][size],int* row,int* col){
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(arr[i][j]==0){       //found empty cell and update row and col pass by address and return 1
                *row=i;*col=j;
                return 1;
            }
        }
    }
    return 0;                      //no empty cell present return 0
}



//if in our sudoku poossible to have subgrids then it also check in that particular subgrid and return 1 if
// that value is present in that subgrid alse return 0
// if subgrid is not possible in our system then it simply return 0

int presentinsubgrid(int row,int col,int number,int arr[][size]){
    if(temp*temp!=size)                //if subgrid not possible then return simply 0
      return 0;
    int startrow,startcol;
    for(int i=temp;i<=size;i+=temp){   //finding appropriate subgrid starting index for row
         if(row<i){
             startrow=i-temp;
             break;
         }
    }
    for(int l=temp;l<=size;l+=temp){   //finding appropriate subgrid starting index for col
         if(col<l){
             startcol=l-temp;
             break;
         }
    }
   
    for(int j=0;j<temp;j++){          //check for number present in that grid
        for(int k=0;k<temp;k++){
            if(arr[j+startrow][k+startcol]==number)
              return 1;                // if presetn return 1
        }
    }
    return 0;                          //if not found return 0
}



//It accept our sudoku to solve with row and column backtracking arrays

int sudokusolver(int arr[][size],int** rowbacktracking,int** colbacktracking){
      int row,col;
      int flag=0;
      int temp=findemptycell(arr,&row,&col);   //calling findemptycell function to findemptycell
      if(temp==0)                              //if no empty cell present then our sudoku is solve and return 1
        return 1;
      for(int i=1;i<=size;i++){

          //check if value i is present in that particular row and that particular column and particulat grid
          //if it presnt then try for another value of i to solve sudoku
          if(rowbacktracking[row][i-1] || colbacktracking[col][i-1] || presentinsubgrid(row,col,i,arr)) 
            continue; 
          
          arr[row][col]=i;                //assign that particular empty block value i 
          rowbacktracking[row][i-1]=1;    //update row backtracking
          colbacktracking[col][i-1]=1;    //update col backtracking

           //call recursively for arr again with now new one cell is filled
          flag=sudokusolver(arr,rowbacktracking,colbacktracking); 

          // if our function return 1 it means that our value works hence return 1
          if(flag==1)
            return 1;

           // if our function return 0 it means that we choose wrong value hence make arr[row][col]=0 again
           // and also update row backtracking and col backtracking respectively and try for another value of i
          else{
            arr[row][col]=0;
            rowbacktracking[row][i-1]=0;
            colbacktracking[col][i-1]=0;
            continue;
          }
      }
      // if no value of i works it means that we can not solve given soduku 
      //  and no solution exits for previous assume value of i hence return 0
    return 0;
}



// This function whick is call by our main function it initialize required array for backtracking 
// and call sudokusolver which is going to solve our sudoku in recursive form with the help of backtracking
// It also check for correctness of our sudoku. If our sudoku is not correct then it return 0 to indicate that 
// no solution is possible for given sudoku

int LetsSolveSudoku(int arr[][size]){
    //allocating memory for backtracking
    int ** rowbacktracking=(int**)malloc(sizeof(int*)*size); 
    int ** colbacktracking=(int**)malloc(sizeof(int*)*size);
    for(int i=0;i<size;i++){
        rowbacktracking[i]=(int*)malloc(sizeof(int)*size);
        colbacktracking[i]=(int*)malloc(sizeof(int)*size);
        for(int j=0;j<size;j++){
            rowbacktracking[i][j]=0;
            colbacktracking[i][j]=0;
        }
    }
    //storing value in column and row backtracking arrays
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(arr[i][j]>size)
              return -1;
            if(arr[i][j]!=0){
                 if(rowbacktracking[i][arr[i][j]-1]==0)
                    rowbacktracking[i][arr[i][j]-1]=1;
                else
                  return 0;
            }
        }
    }
    for(int i=0;i<size;i++){
        for(int j=0;j<size;j++){
            if(arr[i][j]>size)
              return -1;
            if(arr[i][j]!=0){
                if(colbacktracking[j][arr[i][j]-1]==0)
                  colbacktracking[j][arr[i][j]-1]=1;
                else
                  return 0;
            }
        }
    }      
           //calling for sudoku sovlver function with row and col backtracking 
    return sudokusolver(arr,rowbacktracking,colbacktracking);
}
int lenofint(int a){
    int count=0;
    while(a!=0){
        a/=10;
        count++;
    }
    return count;
}

void accurateprint(int a){
    int len=lenofint(a);
    int lenofsize=lenofint(size);
    for(int i=0;i<lenofsize-len;i++){
        printf(" ");
    }
    printf(" %d ",a);
}


int main(){
    printf("\n!!!Welcome to Sudoku Solver Programme!!!\n");
    while(1){
        printf("\nEnter size of sudoku in integer format (enter -1 to exit)\n");
        scanf("%d",&size);
        if(size==-1)
          break;
        else if(size<=0){
            printf("Enter correct size\n");
            continue;
        }
        temp=sqrt(size);
        int grid[size][size];
        printf("Enter Sudoku Grid\n");          //taking grid input from user
        for(int i=0;i<size;i++){
            for(int j=0;j<size;j++){
                scanf("%d",&grid[i][j]);
            }
        }
        int ans=LetsSolveSudoku(grid);          // calling function for solve sudoku
        
        if(ans==1){          
            printf("\nBingo!!! The ans is\n\n") ;   //if ans exists then printing grid
            int var=(lenofint(size)+2)*size+(int)ceil(sqrt(size))+1;
            for(int i=0;i<size;i++){
                if(i==0 || i%(int)ceil(sqrt(size))==0){
                    for(int k=0;k<var;k++)
                       printf("-");
                    printf("\n");
                }
                for(int j=0;j<size;j++){
                    if(j==0 || j%(int)ceil(sqrt(size))==0)
                      printf("|");
                    // printf(" %d ",grid[i][j]);
                    accurateprint(grid[i][j]);
                }
                printf("|");
                printf("\n");
            }
            for(int k=0;k<var;k++)
                printf("-");
            printf("\n");
        }
        else if(ans==-1)
            printf("\nEnter correct values in Sudoku.\n");            //error in values
        else                                     
            printf("Sorry No solution exits for given Suduku.\n");  //else printing no solution exists

        char c;
        printf("\nWant to continue. Press y for yes n for no\n");
        scanf("\n%c",&c);
        if(c=='n')
          break;
    }
    

    return 0;
}