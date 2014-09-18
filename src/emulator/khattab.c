#include "khattab.h"


void Load(Memory* p, int r, int m)
/*
 * This function loads the register with a value from memory:
 * Reg[R] <- Mem[M+PC]
 * Note that the addressing is direct and relative to the PC
 * opcode 1. 
*/
{
    p->gpr[r] = p->mem[m+p->pc];
    
}

void Store(Memory*p, int r, int m)
/*
 * This function fetches a value from a register and stores it in memory:
 * Mem[M+PC] <- Reg[R]
 * Note that the addressing is direct and relative to the PC
 * opcode 2. 
*/
{
    p->mem[m+p->pc] = p->gpr[r];
    
    
}

void Read(Memory*p, int r)
/*
 * This function reads a value from the standard input and puts it
 * in register r: Reg[R] <- Stdin
 * opcode 3. 
*/

{
    
    
    //printf("Please enter integer value:\n");
    
    
    scanf("%d", &p->gpr[r]);
   
    
    
    
}

void Write(Memory* p, int r)
/*
 * This functon prints the value from register r on the standard output
 * opcode 4. 
*/

{
    
    printf("%d\n", p->gpr[r]);
    
    
    
}

void Copy(Memory* p, int r1, int r2)

/*
 * This function copies the value from r2 into r1:
 * Reg[R1] <- Reg[R2]
 * (opcode 5). 
*/

{
    p->gpr[r1] = p->gpr[r2];
    
}

void OP(Memory* p, int r1, int r2, char op)
/*
 * This function performs an operation between r1 and r2 and stores it in r1
 * Reg[R1] <- Reg[R1] OP Reg[R2]
 * It also sets the PSW in the following fashion:
 * If Result = 0, then PSW = 1
 * If Result < 0 , then PSW = 2
 * PSW = 0 otherwise
 * (opcode 6 to 11). 
*/
{
    
    int result;
    
    switch (op)
    {
        case (6): //ADD
        {
            result = p->gpr[r1] + p->gpr[r2];
            break;
        }
        case (7): //SUB
        {
            result = p->gpr[r1] - p->gpr[r2];
            break;
        }
        case (8): //AND
        {
            result = p->gpr[r1] & p->gpr[r2];
            break;
        }
        case (9): //OR
        {
            result = p->gpr[r1] | p->gpr[r2];
            break;
        }
        case (10): //XOR
        {
            result = p->gpr[r1] ^ p->gpr[r2];
            break;
        }
        case (11): //NOT (R2 IS A DON'T CARE!)
        {
            result = ~p->gpr[r1];
            break;
        }
            
            
    }
    
    
    
    if (result==0) p->psw = 1;
    else 
        if (result<0)
        {
            p->psw = 2;
        }
        else
        {
            p->psw = 0;
        }
    
    p->gpr[r1] = result;
    
}

void Jump(Memory* p, int m, char op)
/*
 * This function executes jump instructions according to op (opcode 12 to 16).
*/

{
    switch (op)
    {
        case (12): //JMP: unconditional jump 
        {
            p->pc += m;
            break;
        }
        case (13): //JZ: branches if psw = 1 (if previous OP resulted in 0)
        {
            if ((p->psw)==1) p->pc += m; 
            
            break;
        }
        case (14): //JNZ: branches if psw != 1 (if previous OP resulted in non zero)
        {
            if ((p->psw)!=1) p->pc += m;
            
            break;
        }
        case (15): //JN: branches if psw = 2 (if previous OP resulted in negative)
        {
            if ((p->psw)==2) p->pc += m;
            
            break;
        }
        case (16): //JP: branches if psw = 0 (if previous OP resulted in positive)
        {
            if ((p->psw)==0) p->pc += m;
            
            break;
        }
    }
    
}

void Push (Memory* p, int r)
/*
 * Pushes the value from r into the stack (opcode 17).
 * 
*/

{
    p->sp--;
    p->mem[p->sp] = p->gpr[r];
   
}

void Pop (Memory* p, int r)
/*
 * Pop a value from the stack into the register (opcode = 18). PC is incremented
 * by 2
*/
{
    p->gpr[r] = p->mem[p->sp];
    (p->sp)++;
    
}

void Call (Memory* p, int m)
/*
 * Call a subroutine (opcode = 19).
*/
{
    (p->sp)--;
    p->mem[p->sp] = p->pc;
    (p->pc) += m;
}

void Ret(Memory *p)
/*
 * Return from a subroutine (opcode = 20)
*/
{
    p->pc = p->mem[p->sp];
    p->sp++;
}

void Halt(Memory *p)
/*
 * Stops the Machine
*/

{
    p->halt = true;
}

void PrintStatus(Memory* p, int opcode)
/*
 * This function prints on the screen the current values of all registers,
*/
{
    
    

    //The below trick takes the value of the PSW register and transforms it
    //into a string... either "00" (positive result), "10" (zero) or "01" (negative)
    char pswValue[3];
    pswValue[2] = '\0';
    if (p->psw==0)
    {
      pswValue[0] = '0';
      pswValue[1] = '0';
    }
    else
        if(p->psw==1)
        {
            pswValue[0] = '1';
            pswValue[1] = '0';
        }
        else
        {
            pswValue[0] = '0';
            pswValue[1] = '1';

        }

    printf("[PC=%d, SP=%d, PSW=%s, OPCODE=%d]\n", p->pc, p->sp, pswValue, opcode );
   
    
    // printf("\nPC = %d\t\t\t\tSP = %d\n", p->pc, p->sp);
    // if (p->psw==0)
    // {
    //     printf("PSW Zero Flag = 0\t\tPSW Negative Flag = 0\n");
    // }
    // else
    //     if (p->psw==1)
    //     {
    //         printf("PSW Zero Flag = 1\t\tPSW Negative Flag = 0\n");
    //     }
    //     else
    //     {
    //        printf("PSW Zero Flag = 0\t\tPSW Negative Flag = 1\n"); 
    //     }
    
    // for (ii=0;ii<8;ii++)
    // {
    //     printf("R%d = %d\n", ii, p->gpr[ii] );
    // }
    
    
    // printf("\nPress enter to continue...\n");
    
    
    // fflush(stdin);
    // getchar();
    
    
    
    
    
    
}

void LoadProgram(Memory* p, FILE* f)
/*
 * FILE f must be open in the rb mode. This function writes the file into the memory
*/
{
    int ii = 0; //aux variable used for filling the memory
    bool error = false; //aux variable used to check if it is a valid file
    
    //The below 5 lines check to see if the first two bytes of the file
    //correspond to the characters 'M' and 'K'. The program only executes if
    //this conditions holds
    char ver = '\0';
    fread(&ver, 1, 1, f); //reads one byte to ver
    if (ver!='M')
        error = true;  
    fread(&ver, 1, 1, f); //reads one byte to ver
    if (ver!='K') 
        error = true;
    
    if (error)
    {
        printf("Error 503: Invalid file type.\n");
        p->halt = true;
        return;
    }
    
    
    p->halt = false; //If control made it here, then we have a valid file
    
    fread(&p->pc, 1, 4, f); //The first four bytes correspond to the value of PC
    fread(&p->sp, 1, 4, f); //The second four bytes correspond to the value of SP
    

    
    //Now, the other bytes correspond to the memory
    
/*
 It reads the file until its end is reached, putting each 4 bytes into correspon
 * ding fields of the mem vector. Note that the address of each memory cell
 * corresponds to the index of the vector
 * 
*/
    while (!feof(f))
    {
        fread(&p->mem[ii], 4, 1, f);
        ii++;
    }
    
    
    
}

void RunMachine(Memory* p, bool verbose)
/*
 * This function hus the purpose of running the core of the simulator. It 
 * starts executing at the address pointed by PC. The function LoadProgram
 * MUST be executed first. Another important detail is that the value of PC
 * is always updated after an instruction, depending on the size of the instruction
 * and if it is a branch
*/

{
    
    p->psw = 0;
    int opcode;
    //It gets the opcode from the address contained in PC
    int r1, r2, m; //possible operands 
/*    if (verbose)
    {
        printf("Initial Status:\n");
        
        PrintStatus(p);
        
    }*/
    
    while (!p->halt)
    {
        opcode = p->mem[p->pc];
        
        
        switch (opcode)
        {
            default: 
            {
                printf("\nError 505: Invalid memory access. Your program"
                        " screwed me up! =/\n");
                printf("Error detail: Invalid opcode: %d\n", opcode);
                printf("Machine status when happened:\n");
                PrintStatus(p, opcode);
                printf("\nHalt will be set. All data will be lost.\n");
                p->halt = true;
                break;
            }
            case (1): //LOAD
            {
            	if (verbose)
            	                {
            	                    //printf("Status after LOAD R%d, %d:\n", r1, m);
            	                    PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                m = p->mem[(p->pc)];
                (p->pc)++;
                Load(p, r1,m);

                break;
            }
            
            case (2): //STORE
            {
            	if (verbose)
            	                {
            	                    //printf("Status after STORE: R%d, %d\n", r1, m);
            	                    PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                m = p->mem[(p->pc)];
                (p->pc)++;
                Store(p, r1,m);

                break;
            }
            
            case (3): //READ
            {
            	if (verbose)
            	                {
            	                    //printf("Status after READ R%d:\n", r1);

            	                    PrintStatus(p,opcode);

            	                }
                (p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                Read(p, r1);
                

                break;
            }
            
            case (4): //WRITE
            {
            	if (verbose)
            	                {
            	                    //printf("Status after WRITE R%d:\n", r1);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                Write(p, r1);

                break;
            }
            
            case (5): //COPY
            {
            	 if (verbose)
            	                {
            	                    //printf("Status after COPY R%d R%d:\n", r1, r2);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                r2 = p->mem[(p->pc)];
                (p->pc)++;
                Copy(p, r1,r2);

                break;
            }
            
            case (6): //ADD
            {
            	if (verbose)
            	                {
            	                    //printf("Status after ADD R%d R%d:\n", r1, r2);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                r2 = p->mem[(p->pc)];
                (p->pc)++;
                OP(p, r1, r2, opcode);

                break;    
            }
            case (7): //SUB
            {
            	if (verbose)
            	                {
            	                    //printf("Status after SUB R%d R%d:\n", r1, r2);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                r2 = p->mem[(p->pc)];
                (p->pc)++;
                OP(p, r1, r2, opcode);

                break;    
            }
            case (8): //AND
            {
            	if (verbose)
            	                {
            	                    //printf("Status after AND R%d R%d:\n", r1, r2);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                r2 = p->mem[(p->pc)];
                (p->pc)++;
                OP(p, r1, r2, opcode);

                break; 
            }
            case (9): //OR
            {
            	if (verbose)
            	                {
            	                    //printf("Status after OR R%d R%d:\n", r1, r2);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                r2 = p->mem[(p->pc)];
                (p->pc)++;
                OP(p, r1, r2, opcode);

                break; 
            }
            case (10): //XOR
            {
            	if (verbose)
            	                {
            	                    //printf("Status after XOR R%d R%d:\n", r1, r2);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                r2 = p->mem[(p->pc)];
                (p->pc)++;
                OP(p, r1, r2, opcode);

                break; 
            }
            case (11): //NOT
            {
            	if (verbose)
            	                {
            	                    //printf("Status after NOT R%d:\n", r1);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                OP(p, r1, r2, opcode);

                break; 
            }
            case (12): //JMP
            {
            	if (verbose)
            	                {
            	                    //printf("Status after JMP %d:\n", m);
            	                    PrintStatus(p, opcode);
            	                }
            	(p->pc)++;
                m = p->mem[(p->pc)];
                (p->pc)++;
                Jump(p, m, opcode);

                break;
            }
            case (13): //JZ
            {
            	if (verbose)
            	                {
            	                    //printf("Status after JZ %d:\n", m);
            	                    PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                m = p->mem[(p->pc)];
                (p->pc)++;
                Jump(p, m, opcode);

                break;
            }
            case (14): //JNZ
            {
            	if (verbose)
            	                {
            	                    //printf("Status after JNZ %d:\n", m);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                m = p->mem[(p->pc)];
                (p->pc)++;
                Jump(p, m, opcode);

                break;
            }
            case (15): //JN
            {
            	if (verbose)
            	                {
            	                    //printf("Status after JN %d:\n", m);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                m = p->mem[(p->pc)];
                (p->pc)++;
                Jump(p, m, opcode);

                break;
            }
            case (16): //JP
            {
            	if (verbose)
            	                {
            	                    //printf("Status after JP %d:\n", m);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                m = p->mem[(p->pc)];
                (p->pc)++;
                Jump(p, m, opcode);

                break;
            }
            case (17): //PUSH
            {
            	if (verbose)
            	                {
            	                    //printf("Status after PUSH %d:\n", r1);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                Push(p, r1);

                break;
            }
            case (18): //POP
            {
            	if (verbose)
            	                {
            	                    //printf("Status after POP %d:\n", r1);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                r1 = p->mem[(p->pc)];
                (p->pc)++;
                Pop(p, r1);

                break;
            }
            case (19): //Call
            {
            	if (verbose)
            	                {
            	                    //printf("Status after CALL %d:\n", m);
            	                	PrintStatus(p,opcode);
            	                }
            	(p->pc)++;
                m = p->mem[(p->pc)];
                (p->pc)++;
                Call(p, m);

                break;
            }
            case (20): //Ret
            {
            	if (verbose)
            	                {
            	                    //printf("Status after RET:\n");
            	                	PrintStatus(p,opcode);
            	                }
            	Ret(p);

                break;
            }
            case (21): //Halt
            {
            	if (verbose)
            	                {
            	                    //printf("Status after HALT:\n");
            	                	PrintStatus(p,opcode);
            	                }
            	Halt(p);

                
                break;
            }
        }
    }
    
}
