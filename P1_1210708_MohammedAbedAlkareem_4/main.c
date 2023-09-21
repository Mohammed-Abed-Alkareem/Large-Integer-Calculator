/*
*Name: Mohammed Abed Alkareem
*ID:1210708
*section: 4
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct digit Digit;

struct digit
{
    int Data;
    Digit* Next;
    Digit* Pre;

};

typedef struct results Queue;
typedef struct results QueueResults;
typedef struct results QueueMultiply;
typedef struct results QueueRemainder;

struct results
{
    Digit* res;
    QueueResults* Next;
    QueueResults* Pre;
};

////////////////// list
Digit* MakeEmpty(Digit* );
void DisposeList(Digit*);
int IsEmpty (Digit* );
int IsLast (Digit*,Digit* );
Digit* FindLast( Digit* );
void InsertLast (int,Digit*L);
void InsertFirst (int,Digit*);
void DeleteList(Digit* );
void PrintList(Digit* );
int Size(Digit* );
Digit* Duplicate(Digit*);
void PrintListToFile(FILE*, Digit* );
///////////// read
int numberCount();
Digit** readFile();
void DisposeArray(Digit**,int);
void PrintNumbers(Digit**,int);
///////////////////// calculator
void mainMenu();
void AddTwoNumbers(Digit*,Digit*,QueueResults*);
int Compare(Digit*,Digit*);
void MultiplyTwoNumbers(Digit*,Digit*,QueueResults*);
void SubtractTwoNumbers(Digit*,Digit*,QueueResults*);
Digit* Subtract(Digit*,Digit*);
Digit* AddNumbers(Digit*,Digit*);
void DivideTwoNumbers(Digit*,Digit*,QueueResults*,QueueRemainder*);
void RemoveZeros(Digit* );
////////// Queue
Queue* MakeEmptyQueue(Queue* );
void DisposeQueue(Queue*);
int IsEmptyQueue (Queue* );
void Enqueue (Digit*,Queue* );
Digit* Dequeue (Queue* );
void DeleteQueue(Queue* );
int IsLastQueue(Queue*,Queue*);
QueueResults* FindLastQueue(Queue*);
void PrintQueue(QueueResults*,QueueRemainder*);

int main()
{
    printf("\nWelcome To My Large Integer Calculator ^_^\n\n");

    // Get the number of digits for the input numbers
    int nums=0 ;

    // Allocate memory for the input numbers and the results queue
    Digit **numbers = NULL;

    //Make Empty Queue to store the results
    QueueResults *Results = NULL;
    Results = MakeEmptyQueue(Results);

    //Make Empty Queue to store the remainders
    QueueResults *Remainders = NULL;
    Remainders = MakeEmptyQueue(Remainders);

    int x;
    int y;

    while (1) //always ask the user for the choice
    {
        int choice;

        // Display the main menu
        mainMenu();

        printf("What do you want to do: ");
        scanf("%d", &choice);
        printf("\n");

        switch (choice)
        {
        case 1:
             if (numbers != NULL) //if it was allocated before free it
                DisposeArray(numbers,nums);

            nums = numberCount();

            // Read the input numbers from file
            printf("Reading numbers......\n");
            numbers = readFile();

            if (numbers != NULL)
                printf("The numbers have been read\n");


            //to check if there is empty number and delete it
            for (int i = 0; i < nums ; i++)
            {
                if (numbers[i]->Next == NULL || (numbers[i]->Next->Data == 1 && numbers[i]->Next->Next == NULL))
                {
                    for (int j = i; j < nums - 1; j++)
                    {
                        numbers[j] = numbers[j + 1];
                    }
                    nums--; // Decrement the number of elements in the array
                    i--;
                }
                RemoveZeros(numbers[i]);
            }

            if (nums < 2) // Check that there are at least two numbers
            {
                printf("\nThis file must have at least two numbers\n");
                exit(0);
            }
            break;

        case 2:
            // Check that input numbers have been read first
            if (numbers == NULL)
            {
                printf("\nYou should read the numbers first *_*\n");
                break;
            }

            // Get the indices of the numbers to add
            printf("Which numbers do you want to add (1, 2, ...)?\n");

            //print the numbers to the user to choose
            PrintNumbers(numbers,nums);

            printf("First number: ");
            scanf("%d", &x);

            while(x>nums||x<0)//to check if the first number is exists if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n",nums);
                printf("First number: ");
                scanf("%d", &x);
            }
            printf("Second number: ");
            scanf("%d", &y);

            while(y>nums||y<0)//to check if the second number is exists if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n",nums);
                printf("Second number: ");
                scanf("%d", &y);
            }

            // Add the numbers and store the result in the results queue
            AddTwoNumbers(numbers[--x], numbers[--y], Results);
            Enqueue(NULL,Remainders);

            break;

        case 3:
            // Check that input numbers have been read first
            if (numbers == NULL)
            {
                printf("\nYou should read the numbers first *_*\n");
                break;
            }

            // Get the indices of the numbers to add

            printf("Which numbers do you want to subtract (1, 2, ...)?\n");

            //print the numbers to the user to choose
            PrintNumbers(numbers,nums);

            printf("First number: ");
            scanf("%d", &x);

            while(x>nums||x<0)//to check if the first number is exists if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n",nums);
                printf("First number: ");
                scanf("%d", &x);
            }

            printf("Second number: ");
            scanf("%d", &y);

            while(y>nums||y<0)//to check if the second number is exists if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n",nums);
                printf("Second number: ");
                scanf("%d", &y);
            }
            // Add the numbers and store the result in the results queue
            SubtractTwoNumbers(numbers[--x], numbers[--y], Results);
            Enqueue(NULL,Remainders);

            break;

        case 4:
            // Check that input numbers have been read first
            if (numbers == NULL)
            {
                printf("\nYou should read the numbers first *_*\n");
                break;
            }

            // Get the indices of the numbers to multiply
            printf("Which numbers do you want to multiply (1, 2, ...)?\n");

            //print the numbers to the user to choose
            PrintNumbers(numbers,nums);

            printf("First number: ");
            scanf("%d", &x);

            while(x>nums||x<0)//to check if the first number is exists if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n",nums);
                printf("First number: ");
                scanf("%d", &x);
            }

            printf("Second number: ");
            scanf("%d", &y);

            while(y>nums||y<0)//to check if the first number is exists if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n",nums);
                printf("Second number: ");
                scanf("%d", &y);
            }

            // Multiply the numbers and store the result in the results queue
            MultiplyTwoNumbers(numbers[--x], numbers[--y], Results);
            Enqueue(NULL,Remainders);

            break;

        case 5:
            // Check that input numbers have been read first
            if (numbers == NULL)
            {
                printf("\nYou should read the numbers first *_*\n");
                break;
            }

            // Get the indices of the numbers to Divide

            printf("Which numbers do you want to Divide (1, 2, ...)?\n");

            //print the numbers to the user to choose
            PrintNumbers(numbers,nums);

            printf("First number: ");
            scanf("%d", &x);

            while(x>nums||x<0)//to check if the first number is exists if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n",nums);
                printf("First number: ");
                scanf("%d", &x);
            }

            printf("Second number: ");
            scanf("%d", &y);

            while(y>nums||y<0)//to check if the first number is exists if not ask the user to enter it again
            {
                printf("Enter a number between 1 and %d\n",nums);
                printf("Second number: ");
                scanf("%d", &y);
            }

            // Divide the numbers and store the result in the results queue
            DivideTwoNumbers(numbers[--x], numbers[--y], Results,Remainders);

            break;

        case 6:

            // Print the results queue
            PrintQueue(Results,Remainders);

            printf("\nThe Results Have been Printed On the output File ^_^\n");

            break;

        case 7:

            // Free the memory allocated for the input numbers and the results queue
            if (numbers != NULL)
            {
                printf("....Disposing Lists\n");
                DisposeArray(numbers,nums);
                DisposeQueue(Results);
            }

            printf("Thanks for using My Large Integer Calculator ^_^\n");
            exit(0);

            break;

        default:
            printf("Enter a choice between 1 and 7\n");
        }
    }

    return 0;
}


/*
*to make Empty Doubly Linked List to store
*each digit in its nodes
*/
Digit* MakeEmpty(Digit* L)
{
    if (L != NULL)
        DeleteList(L);

    L = (Digit*) malloc(sizeof(Digit));

    if (L == NULL)
        printf("Out Of Memory *_*");

    L->Next = NULL;
    L->Pre = NULL;
    return L;
}

/*
*returns 0 if the Linked List is not Empty
*/
int IsEmpty(Digit* L)
{
    return L->Next == NULL; // returns 1 if the list is empty
}

/*
*returns 0 if this node in the Linked List is not the last node
*/
int IsLast(Digit* P, Digit* L)
{
    return P->Next == NULL;
}

/*
*frees all nodes in the list
*/
void DeleteList(Digit* L)
{
    Digit *P, *temp;

    P = L->Next;
    L->Next = NULL;

    while (P != NULL)
    {
        temp = P->Next;
        free(P);
        P = temp;
    }
}

/*
*prints the data of all nodes from the in the list
*if the node after the head is 1 it prints negative sign then continue to the next
*if it was 0 it just continue to the next
*/
void PrintList(Digit* L)
{
    Digit* P = L->Next;

    if (IsEmpty(L))
    {
        printf("\nThe List Is Empty *_*\n");
    }
    else
    {


        if (P->Data == 1)
        {
            printf("-");
        }

        do
        {
            P = P->Next;
            printf("%d", P->Data);
        }
        while (!IsLast(P, L));


    }
}

/*
* to insert node with data = X in the last of the list
*/
void InsertLast (int X,Digit*L )
{
    Digit* temp;
    temp = (Digit*)malloc(sizeof(Digit));
    temp->Data = X;
    if(!IsEmpty(L))
    {
        Digit*P = FindLast(L);

        temp->Next=P->Next;
        P->Next = temp;
        temp->Pre=P;
    }
    else
    {
        temp->Pre=L;
        temp->Next=NULL;
        L->Next = temp;
    }
}


/*
* to insert node with data = X in the first of the list
*if the list only contains the head this Data = X is the sign Digit
*if the sign digit exists it insert the node with Data = X after the sign node
*/
void InsertFirst (int X,Digit*L )
{
    Digit* temp;

    temp = (Digit*)malloc(sizeof(Digit));
    temp->Data = X;
    if(!IsEmpty(L))
    {
        Digit* SignNode = L->Next;
        if(!IsEmpty(SignNode))
        {
            SignNode->Next->Pre=temp;
            temp->Pre=SignNode;
            temp->Next=SignNode->Next;
            SignNode->Next=temp;
        }
        else
        {
            temp->Pre=SignNode;
            SignNode->Next=temp;
            temp->Next=NULL;

        }
    }
    else
    {

        temp->Pre=L;
        L->Next=temp;
        temp->Next=NULL;

    }

}


/*
* returns the number of the digits without the sign one
*/
int Size(Digit* L)
{
    int count =0;
    Digit* P = L;

    while(P->Next != NULL)
    {
        count++;
        P = P->Next;
    }
    return --count;
}

/*
* this return the last node in the Doubly Linked List
*/
Digit* FindLast( Digit* L)
{

    Digit* P = L;

    while(P->Next!=NULL)
        P=P->Next;

    return P;


}

/*
*Dispose the Doubly Linked List
*/
void DisposeList(Digit*L)
{
    DeleteList(L);
    free(L);
}

/*
*returns the the number of the numbers in the file
*By counting the new Line Char '\n'
*/
int numberCount()
{
    FILE* fin = fopen("input.txt","r");
    char ch;
    int lines = 0;
    if (fin == NULL)
    {
        printf("Failed to open file: \n");
        return 1;
    }
    while ((ch = fgetc(fin)) != EOF)
    {
        // If we find a newline character, increment the line counter
        if (ch == '\n')
        {
            lines++;
        }
    }
    fclose(fin);
    return lines;
}

/*
* this function Allocate an array of pointers to the Doubly linked List
*with size of the number of the numbers in the file
*reads char by char
*the first char in each line if it as - it insert the sign node with data = 1
*otherwise insert the sign node with data = 0
*Iterates until it reads End Of File
*/
Digit** readFile()
{
    int numcount = numberCount();
    Digit** numbers= (Digit**)malloc(sizeof(Digit*)*numcount);

    for(int i=0; i<numcount; i++)
    {
        numbers[i]=MakeEmpty(NULL);
    }

    FILE* fin = fopen("input.txt","r");
    if (fin == NULL)
    {
        printf("Failed to open file: \n");
        exit(1);
    }

    char c=fgetc(fin);
    int i=0, flagNewNum=1;
    while(c!=EOF)
    {
        if(c=='\n')
        {
            i++;
            flagNewNum=1;
        }
        else
        {
            if(flagNewNum==1&&c=='-')
                InsertFirst(1,numbers[i]);
            else if (flagNewNum==1)
                InsertFirst(0,numbers[i]);

            flagNewNum=0;
            int dig = c-48;
            if(dig>=0 && dig<=9)
                InsertLast(dig,numbers[i]);
        }
        c=fgetc(fin);
    }
    fclose(fin);

    return numbers;
}

/*
* print the list of digits with number for the order of the numbers
*/
void PrintNumbers(Digit** Numbers,int length)
{

    for (int i = 0; i < length; i++)
    {

        printf("number %d): ",i+1);

        PrintList(Numbers[i]);
        printf("\n");
    }
}

/*
*returns a copy of the linked List
*/
Digit* Duplicate(Digit*L)
{
    Digit* t=NULL,*P ;
    P=L;
    t= MakeEmpty(t);

    while(P->Next!=NULL)
    {
        InsertLast(P->Next->Data,t);
        P=P->Next;
    }
    return t;
}

/*
*Dispose the array allocated with the numbers that the pointers of them are stored in it
*/
void DisposeArray(Digit**arr,int length)
{

    for (int i = 0; i < length; i++)
    {

        DisposeList(arr[i]);
    }
    free(arr);


}

/*
*Prints the Main Menu
*/
void mainMenu()
{
    printf("\nChoose from the below operations:\n\n");
    printf("1. Read the numbers from File\n");
    printf("2. Add Numbers\n");
    printf("3. Subtract Numbers\n");
    printf("4. Multiply Numbers\n");
    printf("5. Divide Numbers\n");
    printf("6. print the results to	an output file\n");
    printf("7. Exit\n");
}
/*
*this function take two numbers and adds the numbers from the least significant digit
*if the result of the addition is greater than 10 then there is carry to the next digit
*return a linked list that contains the result of the addition
*/
Digit* AddNumbers(Digit*FirstNum,Digit*SecondNum)
{
    Digit* result = MakeEmpty(NULL);
    InsertFirst(0,result);
    Digit*num1=FindLast(FirstNum);
    Digit*num2=FindLast(SecondNum);
    int res;
    int Cin=0;//carry in

    while (num1 != FirstNum->Next && num2!=SecondNum->Next ) //iterates until reaching sign node in first number or the second
    {

        res = num1->Data + num2->Data+Cin;
        if(res<10)
        {
            InsertFirst(res,result);
            Cin=0;
        }

        else
        {
            res-=10;
            InsertFirst(res,result);
            Cin=1;
        }
        num1 =num1->Pre;
        num2 =num2->Pre;

    }

    //if it reach the sign node in the first number but not in the second i it iterates until reaching the sign node in the second number
    while (num1 == FirstNum->Next && num2!=SecondNum->Next )
    {
        res =num2->Data+Cin;
        if(res<10)
        {
            InsertFirst(res,result);
            Cin=0;
        }

        else
        {
            res-=10;
            InsertFirst(res,result);
            Cin=1;
        }

        num2 =num2->Pre;


    }
    //if it reach the sign node in the second number but not in the second i it iterates until reaching the sign node in the first number
    while (num1 != FirstNum->Next && num2==SecondNum->Next )
    {
        res =num1->Data+Cin;
        if(res<10)
        {
            InsertFirst(res,result);
            Cin=0;
        }

        else
        {
            res-=10;
            InsertFirst(res,result);
            Cin=1;
        }
        num1 =num1->Pre;
    }

    //if there was carry after finishing the digits just insert it after the sign node
    if(Cin!=0)
        InsertFirst(Cin,result);
    else
        result->Next->Data=0;


    return result;


}
/*
*takes the two numbers that the user chose
*then decide the right operation based on their sign and value
*then Enqueue the result for the addition in the result queue
*/
void AddTwoNumbers(Digit*FirstNum,Digit*SecondNum,QueueResults* Results)
{

    Digit* result = MakeEmpty(NULL);

    if(FirstNum->Next->Data==0&&SecondNum->Next->Data==0)
    {
        result=AddNumbers(FirstNum,SecondNum);

    }
    else if(FirstNum->Next->Data==1&&SecondNum->Next->Data==1)
    {
        result=AddNumbers(FirstNum,SecondNum);
        result->Next->Data=1;
    }
    else if(FirstNum->Next->Data==0&&SecondNum->Next->Data==1)
    {
        if(Compare(FirstNum,SecondNum)>0)
            result= Subtract(FirstNum,SecondNum);
        else if (Compare(FirstNum,SecondNum)<0)
        {
            result=  Subtract(SecondNum,FirstNum);
            result->Next->Data=1;

        }
        else
        {
            InsertFirst(0,result);
            InsertFirst(0,result);
        }
    }
    else
    {
        if(Compare(FirstNum,SecondNum)>0)
        {
            result=  Subtract(FirstNum,SecondNum);
            result->Next->Data=1;
        }

        else if (Compare(FirstNum,SecondNum)<0)
            result=  Subtract(SecondNum,FirstNum);

        else
        {
            InsertFirst(0,result);
            InsertFirst(0,result);
        }
    }

    RemoveZeros(result);

    printf("\n");
    printf("The Result = ");
    PrintList(result);
    printf("\n");


    Enqueue(result,Results) ;


}

/*
*takes two numbers and compare them
*number 1 is bigger then returns 1
*number 1 is smaller then returns -1
*if they are equal it returns 0
*/
int Compare(Digit*FirstNum,Digit*SecondNum)  //num1 bigger return 1 , smaller return -1 , equal return 0
{
    //we can decide which number is bigger based on number of digits in each already zeros at the beginning were deleted
    if(Size(FirstNum)>Size(SecondNum))
        return 1;

    else if(Size(FirstNum)<Size(SecondNum))
        return -1;

    //if numbers of digits are equal it iterates to compare digit by digit from the most significant digit
    else
    {
        Digit*num1=FirstNum->Next->Next;
        Digit*num2=SecondNum->Next->Next;

        while (num1 != NULL && num2!=NULL )
        {
            if (num1->Data >num2->Data)
                return 1;

            else if (num1->Data <num2->Data)
                return -1;

            num1 = num1->Next;
            num2=num2->Next;

        }

        return 0;
    }
}
/*
* this takes two numbers and multiply the first number with each digit in the second number
*then add the results of multiplying correctly
*and store the result in a pointer that points to the result list
*/
void MultiplyNumbers(Digit*FirstNum,Digit*SecondNum,Digit** result)
{
    int i=0;

    Digit*PrevResult = NULL;

    Digit* CurrResult=MakeEmpty(NULL);
    InsertFirst(0,CurrResult);
    InsertFirst(0,CurrResult);

    Digit*num1;
    Digit*num2=FindLast(SecondNum);

    while(num2!=SecondNum->Next)
    {
        PrevResult=MakeEmpty(PrevResult);
        InsertFirst(0,PrevResult);

        num1=FindLast(FirstNum);
        int Cin=0;
        while(num1!=FirstNum->Next)
        {

            int noderesult=num1->Data * num2->Data;

            noderesult+=Cin;
            Cin=noderesult/10;
            noderesult %=10;
            InsertFirst(noderesult,PrevResult );
            num1 = num1->Pre;
        }

        if(Cin != 0)
            InsertFirst(Cin,PrevResult);

        if(i>0) //adding zeros to the last of the multiplication result (multiplying by 10 based on the number of the digit)
        {
            for(int z=0 ; z<i ; z++)
                InsertLast(0,PrevResult);
        }

        CurrResult=AddNumbers(CurrResult,PrevResult);

        i++;

        num2=num2->Pre;
    }

    *result=Duplicate(CurrResult) ;

    DisposeList(PrevResult);
    DisposeList(CurrResult);


}
/*
*takes the two numbers from the user
*send the numbers to the multiplication function
*decide the sign of the result
*enqueue the result in the results queue
*/
void MultiplyTwoNumbers(Digit*FirstNum,Digit*SecondNum,QueueResults* Results)
{

    Digit* result ;

    MultiplyNumbers(FirstNum,SecondNum,&result);

    if(FirstNum->Next->Data ==SecondNum->Next->Data)
    {
        result->Next->Data=0;
    }

    else
    {
        result->Next->Data=1;
    }

    RemoveZeros(result);

    printf("\n");
    printf("The Result = ");
    PrintList(result);
    printf("\n");

    Enqueue(result,Results);
}

/*
*Subtract two numbers when calling it we send the bigger number as first number
*while the smaller as Second number
*it subtract each digit from the first number with the corresponding digit in the second one
*from the least significant digit
*/
Digit* Subtract(Digit*FirstNum,Digit*SecondNum)
{

    Digit*num1=FindLast(FirstNum);
    Digit*num2=FindLast(SecondNum);

    Digit* result = NULL;
    result=MakeEmpty(result);

    int Borrow=0;
    int res;
    InsertFirst(0,result);

    while (num1 != FirstNum->Next && num2!=SecondNum->Next )
    {
        res = num1->Data - num2->Data-Borrow;

        //if the result of the subtraction was negative then here we want a borrow from the next digit
        if(res>=0)
        {
            InsertFirst(res,result);
            Borrow=0;
        }

        else
        {
            res+=10;
            InsertFirst(res,result);
            Borrow=1;
        }
        num1 =num1->Pre;
        num2 =num2->Pre;

    }
    //because the first number in bigger either they have the same number of digits or the first has more
    while (num1 != FirstNum->Next && num2==SecondNum->Next )
    {
        res =num1->Data-Borrow;
        if(res>=0)
        {
            InsertFirst(res,result);
            Borrow=0;
        }

        else
        {
            res+=10;
            InsertFirst(res,result);
            Borrow=1;
        }
        num1 =num1->Pre;
    }

    RemoveZeros(result);
    return result;
}

/*
*takes the two numbers that the user chose
*then decide the right operation based on their sign and value
*then Enqueue the result for the subtraction in the result queue
*/
void SubtractTwoNumbers(Digit*FirstNum,Digit*SecondNum,QueueResults* Results)
{
    Digit* result = NULL;
    result=MakeEmpty(result);

    if(FirstNum->Next->Data ==0 && SecondNum->Next->Data==0 )
    {

        if(Compare(FirstNum,SecondNum)>0)
            result=Subtract(FirstNum,SecondNum);


        else if(Compare(FirstNum,SecondNum)<0)
        {
            result=Subtract(SecondNum,FirstNum);
            result->Next->Data=1;

        }

        else
        {
            InsertFirst(0,result);
            InsertFirst(0,result);

        }
    }

    else if(FirstNum->Next->Data ==0 && SecondNum->Next->Data==1 )
    {
        result= AddNumbers(FirstNum,SecondNum);
    }

    else if(FirstNum->Next->Data ==1 && SecondNum->Next->Data==0 )
    {
        result= AddNumbers(FirstNum,SecondNum);
        result->Next->Data=1;
    }

    else
    {

        if(Compare(FirstNum,SecondNum)>0)
        {
            result=Subtract(FirstNum,SecondNum);
            result->Next->Data=1;
        }

        else if(Compare(FirstNum,SecondNum)<0)
        {
            result=Subtract(SecondNum,FirstNum);
        }

        else
        {
            InsertFirst(0,result);
            InsertFirst(0,result);
        }
    }

    RemoveZeros(result);

    printf("\n");
    printf("The Result = ");
    PrintList(result);
    printf("\n");

    Enqueue(result,Results);
}

/*
*a function that remove the neglectable zeros
*but if the number was zero it keeps only one zero
*/
void RemoveZeros(Digit* L)
{

    Digit* current = L->Next->Next;
    Digit* prev = NULL;

    while(current->Data==0&&current->Next!=NULL)
    {
        prev = current;
        current = current->Next;
        prev->Pre->Next=current;
        current->Pre=prev->Pre;
        free(prev);
    }
}

/*
*takes the two numbers that the user chose
*taking digit from the left side of the number as the division part
*and make a test which is by multiplying the divisor with a counter from 9 to 0
*when the multiplication result become smaller than division part so the result
*for dividing the division part be the counter value is the result
*then subtracting the division part by the multiplication resuly
*then the result is the remainder then we iterate until we add all the digits from the dividend
*one by one at the end of the Dividend the result will be the  quotient for the division
*and the division part is the remainder
*/
void DivideTwoNumbers(Digit* Dividend, Digit* Divisor,QueueResults* Results, QueueRemainder* Remainders)
{
    //if the divisor was zero so that is error
    if(Divisor->Next->Next->Data==0)
    {
        printf("\nCan not divide by 0 *_*\n");
        return;
    }

    Digit* quotient = NULL;
    quotient = MakeEmpty(quotient);
    InsertFirst(0, quotient);

    Digit* divPart = MakeEmpty(NULL);
    InsertFirst(0, divPart);

    Digit* ptrDig = Dividend->Next->Next;

    Digit* test = MakeEmpty(NULL);
    Digit* MulRes = MakeEmpty(NULL);
    Digit* subRes = NULL;

    while (ptrDig != NULL)
    {
        InsertLast(ptrDig->Data, divPart);
        RemoveZeros(divPart);


        for (int i = 9; i >= 0; i--)
        {
            test = MakeEmpty(test);
            MulRes = MakeEmpty(MulRes);

            InsertFirst(0, test);
            InsertFirst(i, test);

            if (i == 0)
            {
                InsertLast(0, quotient);

                continue;
            }

            MultiplyNumbers(Divisor, test, &MulRes);


            if (Compare(MulRes, divPart) > 0)
            {
                continue;
            }

            InsertLast(i, quotient);
            subRes = MakeEmpty(subRes);
            subRes = Subtract(divPart, MulRes);
            divPart = Duplicate(subRes);




            break;
        }

        ptrDig = ptrDig->Next;
    }


    if(Dividend->Next->Data != Divisor->Next->Data)
        quotient->Next->Data=1;

    DisposeList(test);
    DisposeList(subRes);
    DisposeList(MulRes);

    RemoveZeros(quotient);
    RemoveZeros(divPart);

    printf("\n");
    printf("The Result = ");
    PrintList(quotient);
    printf("\tThe Remainder = ");
    PrintList(divPart);
    printf("\n");


    Enqueue(divPart, Remainders);
    Enqueue(quotient, Results);
}

/*
*this for making the Queue empty
*/
Queue* MakeEmptyQueue(Queue* Q)
{
    if(Q != NULL)
        DeleteQueue(Q);

    Q = (Queue*)malloc(sizeof(Queue));

    if(Q == NULL)
        printf("Out Of Memory *_*");

    Q->Next = NULL;
    Q->Pre = NULL;
    return Q;

}

/*
*this dispose the queue with the lists that are stored in
*/
void DisposeQueue(Queue*Q)
{
    DeleteQueue(Q);

    free(Q);
}

/*
*returns 0 if the Linked List is not Empty
*/
int IsEmptyQueue (Queue* Q)
{
    return Q->Next==NULL;
}

/*
*Enqueue the list X in the Queue
*/
void Enqueue (Digit* X,Queue*Q )
{

    Queue* temp;
    temp = (Queue*)malloc(sizeof(Queue));
    temp->res = X;

    if(!IsEmptyQueue(Q))
    {
        Queue*P = FindLastQueue(Q);
        temp->Next=P->Next;
        P->Next = temp;
        temp->Pre=P;
    }
    else
    {
        temp->Pre=Q;
        temp->Next=NULL;
        Q->Next = temp;
    }
}

/*
*Dequeue the list X from the Queue
*and returns the list
*/
Digit* Dequeue (Queue*Q )
{
    if (Q->Next == NULL)
    {
        printf("List is empty");
        exit(0);
    }
    Digit* temp;
    temp=Q->Next->res;

    QueueResults *P=Q->Next;
    if(!IsLastQueue(P,Q))
    {
        Q->Next=P->Next;
        P->Next->Pre=Q;
        free(P);

    }
    else
    {
        Q->Next=NULL;
        free(P);
    }
    return temp;
}

/*
*the the queue node that contains the list and Delete the lists in the node
*/
void DeleteQueue(Queue* Q)
{
    QueueResults *P;
    P= Q->Next;

    while(P != NULL)
    {
        Q->Next = P->Next;
        free(P->res);
        free(P);
        P=Q->Next;
    }
    Q->Next=NULL;

}

/*
*returns 0 if this node in the Queue is not the last node
*/
int IsLastQueue(Queue*P,Queue*Q)
{
    return P->Next==NULL;
}

/*
*returns a pointer to the last node in the queue
*/
Queue* FindLastQueue(Queue*Q)
{
    QueueResults* P = Q;

    while(P->Next!=NULL)
        P=P->Next;

    return P;
}

/*
*Print the linked List to the file in appropriate way
*/
void PrintListToFile(FILE* file, Digit* L)
{
    Digit* P = L->Next;

    if (IsEmpty(L))
    {
        fprintf(file, "\nThe List Is Empty *_*\n");
    }
    else
    {
        if (P->Data == 1)
        {
            fprintf(file, "-");
        }

        do
        {
            P = P->Next;
            fprintf(file, "%d", P->Data);
        }
        while (!IsLast(P, L));
    }
}

/*
*Print the Queue to the file in appropriate way

*/
void PrintQueue(QueueResults* Results, QueueRemainder* Remainders)
{
    FILE* fout = fopen("output.txt", "w");
    if (fout == NULL)
    {
        printf("Failed to open file: \n");
        exit(1);
    }

    Digit* rem,*res;
    int counter = 1;

    while (!IsEmptyQueue(Results) && !IsEmptyQueue(Remainders))
    {
        fprintf(fout, "operation %d. = ", counter);
        res = Dequeue(Results);

        PrintListToFile(fout, res);

        rem = Dequeue(Remainders);
        if (rem != NULL)
        {
            fprintf(fout, "\tRemainder  = ");
            PrintListToFile(fout, rem);
        }

        fprintf(fout, "\n");

        counter++;
    }

    fclose(fout);
}
