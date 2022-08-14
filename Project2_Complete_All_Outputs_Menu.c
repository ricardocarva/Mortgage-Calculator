#include <stdio.h>
#include <math.h> //POW function
#include <stdlib.h> //Getchar function
#include <windows.h> // Sleep Function before clear screen

#define HUNDRED 100.00 //For the percentage
#define MONTHS 12.00 //Total months

int menu(); // Function with the menu
void output_short_format(double loan_amount, double interest_rate, double term_years); //Function to print output / Part of the Output#1
double montly_payments(double L, double interest_rate, double term_years); //Function to get montly payments / Part of the Output#1
double total_interest(double fixed_montly_payment, double L, double term_years, double interest_rate); //Function to get total interest / Part of the Output#1

void output_extra_monthy(double loan_amount,double interest_rate,double term_years,double extra_monthy); // Function to print output / Part of the Output#3
void output_extra_yearly(double loan_amount,double interest_rate,double term_years,double extra_yearly); //print amortized schedule with extra yearly payments

void output_amortized(double loan_amount, double interest_rate, double term_years); //Amortized schedule shows the amounts that go towards interest and principal for each month /Part of the Output2

int main()
{
	double loan_amount, interest_rate, term_years, total_interest, total_amount_paid, extra_monthy, yearly_extra;
	int schedule_type, i; //Type of loan simulation: Cost Estimate, Standard loan, loan with montly amortization, loan with yearly amortization. I is the shutting down counter
	char new_simulation = 'y'; //sentinel to restart program
	while(new_simulation=='y'){
	
		schedule_type = menu();
		
	printf("----------------------------------\n");
	printf("\t  ******************\n");
	printf("\t   LOAN TERMS INPUT\n");
	printf("\t  ******************\n");
	printf("----------------------------------\n");
		printf("Loan Amount: ");
		scanf("%lf", &loan_amount);
		printf("Yearly Interest Rate: ");
		scanf("%lf", &interest_rate);
		printf("Loan Lenght in Years: ");
		scanf("%lf", &term_years);
	printf("----------------------------------\n");
		
		if(schedule_type==1)
		{
			system("cls");
			output_short_format(loan_amount, interest_rate,term_years); //Function that prints the output and call other functions for the Output#1
		}
		
		else if(schedule_type == 2)
		{
			system("cls");
			output_amortized(loan_amount, interest_rate, term_years); //Function that prints the output and call other functions for the Output #2
		}
		
		else if(schedule_type==3)
		{
			printf("Monthly Extra Payments Towards Loan: ");
			scanf("%lf", &extra_monthy);
			system("cls");
			output_extra_monthy(loan_amount, interest_rate, term_years, extra_monthy); //Function that prints the output and call other functions for the Output #3
		}
	
		else if(schedule_type==4)
		{
			printf("Yearly Extra Payments Towards Loan Every December: ");
			scanf("%lf", &yearly_extra);
			system("cls");
			output_extra_yearly(loan_amount, interest_rate, term_years, yearly_extra);//Function that prints the output and call other functions for the Output #4
		}

	
	printf("\n\nTry a Different Simulation?(y/n): ");//if user inputs 'y', the loop continues. If they press anything else, it clears the screen and breaks the loop immediately
	scanf(" %c", &new_simulation);
	if(new_simulation!='y') //If new_simulation is different than 'y', we'll greet, count from 3 to 1, and break the loop
	{
		printf("\nThank you for using MYLoan Simulator 1.0!\nShutting Down in "); 
		
		for(i=3;i>=1;i--){ 
			printf("%d... ", i); //count seconds before clearing the screen
			Sleep(1000); // Hold the code for i seconds
		}
		printf("\nGood bye!"); 

		break; 
	} 
	system("cls");
	
	}
	
	return 0;
}

void output_short_format(double loan_amount, double interest_rate, double term_years) // Part of the Output#1
{
	double fixed_montly_payment, interest_paid; //m_rate is the monthly rate. months is the total of months in a loan.


	printf("----------------------------------\n");
	printf("\t  ************\n");
	printf("\t   LOAN TERMS\n");
	printf("\t  ************\n");
	printf("----------------------------------\n");	
	printf("Loan Amount:%22.lf\n",loan_amount);
	printf("Interest Rate: %18.2lf%%\n",interest_rate);

	printf("Term: %22.lf years\n",term_years);
	printf("----------------------------------\n\n");	
	
	fixed_montly_payment = montly_payments(loan_amount, interest_rate,term_years); //Call the function that gets the monthly payments
	
	printf("Montly Payment is: %15.2lf\n",fixed_montly_payment); //Prints the results of function that gets the monthly payments
	
	interest_paid = total_interest(fixed_montly_payment, loan_amount, term_years, interest_rate); //Call the function that gets the total interest

	printf("Total interest is: %15.2lf\n",interest_paid); //Prints the results of function that gets the total interest
	
	printf("Total amount paid is: %12.2lf", interest_paid+loan_amount); //Prints the results of function that gets the total interest and the loan amount

	return;
}

double montly_payments(double L, double interest_rate, double term_years) //Function to get the montly payments / Part of the Output#1
{
	double months, m_rate;
	months = term_years*MONTHS; 
	m_rate = interest_rate/(MONTHS*HUNDRED);
	return L * m_rate * (pow(1.00+m_rate, months)) /((pow(1.00+m_rate, months))-1.00);
}

double total_interest(double fixed_montly_payment, double L, double term_years, double interest_rate) //Function to get total interest paid / Part of the Output#1
{
	int i; //counter
	double interest, payment_towards_loan, total_interest=0.00;
	double months, m_rate;
	months = term_years*MONTHS; //Gets the total of months of all terms
	m_rate = interest_rate/(MONTHS*HUNDRED); //montly interest rate

	for(i=1;i<=months;i++)
	{
	interest = L*m_rate; //Gets the interest rate montly
	total_interest +=interest; //adds the montly interest to the total_interest
	payment_towards_loan=fixed_montly_payment-interest; //Gets the payments towards the loan subtracting interest
	L-=payment_towards_loan; // loan total amount subtracting payments towards loan
	}
	return total_interest;
}

void output_amortized(double loan_amount, double interest_rate, double term_years) //print amortized schedule
{
		double fixed_montly_payment;
		fixed_montly_payment = montly_payments(loan_amount, interest_rate, term_years); //Call the function that gets the monthly payments
		
		int i, j, k=1; //counter 
		double interest=0.00, payment_towards_loan=0.00, total_interest=0.00, total_payment_towards_loan=0.00;
		double months, m_rate;
		months = term_years*MONTHS; //Gets the total of months of all terms
		m_rate = interest_rate/(MONTHS*HUNDRED); //montly interest rate
		for(j=1;j<=term_years;j++)
		{
			printf("\n-----------------------------------------------------------------------\n");
			printf("\nYear   Month   Interest   Principal   Balance |    INTEREST   PRINCIPAL\n");
			printf("-----------------------------------------------------------------------\n");
		
			for(i=1;i<=MONTHS;i++)
			{
			interest = loan_amount*m_rate; //Gets the interest rate montly
			total_interest +=interest; //Cumulative Interest: adds the montly interest to the total_interest
			payment_towards_loan=fixed_montly_payment-interest; //Principal: Gets the payments towards the loan subtracting interest
			total_payment_towards_loan+=payment_towards_loan; //Cumulative Principal paid
			loan_amount-=payment_towards_loan; // Balance: loan total amount subtracting payments towards loan
					

			if(i==1) printf("\n%4d%8d%11.lf%12.lf%10.lf |%12.lf%12.lf\n",j, k,interest,payment_towards_loan, loan_amount, total_interest,total_payment_towards_loan); //If it's the first month, it prints the year like the sample output#2
			else printf("\n%12d%11.lf%12.lf%10.lf |%12.lf%12.lf\n",k,interest,payment_towards_loan, loan_amount, total_interest,total_payment_towards_loan);
			k++;//sums 1 to months up to date
			}
		}
}

int menu()
{
	int i; //Gets the schedule option selected
	char schedule_option;
	int result=1;
	printf("----------------------------------------------------\n");
	printf("\t   Welcome to MYLoan Simulator 1.0!\n");
	printf("\nCompatible with Windows OS\n"); //Compatibility with Linux Not Tested
		printf("----------------------------------------------------\n");
	printf("Press any key to continue...\n");
	getch();    //Getch will help us getting a character without saving it solely with the purpose of continuing the function. No need to press enter
	system("cls"); //clear screen for windows

	do //Do-While structure ensure the input is valid and we get at least 1 input from the User.
	{
	
	printf("----------------------------------------------------\n");
	printf("\t    ***************************\n");
	printf("\t     Loan Simulation Selection\n");
	printf("\t    ***************************\n");
	
	printf("|Press ENTER to Select     |\n|Use the arrows to navigate|\n");

	printf("----------------------------------------------------\n\n");

	switch  (result)
	{
		case 1:	printf("\t >Cost Estimate<\n\t Amortization Schedule\n\t Early Payments: Monthly\n\t Early Payments: Yearly\n\n"); break;
		case 2:	printf("\t Cost Estimate\n\t >Amortization Schedule<\n\t Early Payments: Monthly\n\t Early Payments: Yearly\n\n"); break;
		case 3:	printf("\t Cost Estimate\n\t Amortization Schedule\n\t >Early Payments: Monthly<\n\t Early Payments: Yearly\n\n"); break;
		default: printf("\t Cost Estimate\n\t Amortization Schedule\n\t Early Payments: Monthly\n\t >Early Payments: Yearly<\n\n");

	}

	printf("----------------------------------------------------\n");
	
	schedule_option = getch(); //getting the arrow keys 

	if(schedule_option == 72 || schedule_option==80) //up (ASCII 80) and down (ASCII 72) arrows 
	{
		if(schedule_option==80&& result<4) //Arrow down. It cant go down the case "4"
		{
			result++;
		}
		else if(schedule_option==72&& result>1) result--; //arrow up. It cant go up the case "1"

	}
	
	system("cls"); //clear screen for windows
	}while(schedule_option!=13);//While the user doesn't input return (ASCII 13), continue looping


	return result; //return valid input
}

void output_extra_monthy(double loan_amount,double interest_rate,double term_years,double extra_monthy) //print amortized schedule with extra montly payments
{
		double fixed_montly_payment, interest_paid;
		fixed_montly_payment = montly_payments(loan_amount, interest_rate, term_years); //Call the function that gets the monthly payments
		interest_paid = total_interest(fixed_montly_payment, loan_amount, term_years, interest_rate); //Call the function that gets the total interest

		int i, j, months, k=1; //counter
		double interest=0.00, payment_towards_loan=0.00, total_interest=0.00, total_payment_towards_loan=0.00;
		double m_rate;
		months = term_years*MONTHS; //Gets the total of months of all terms
		m_rate = interest_rate/(MONTHS*HUNDRED); //montly interest rate
		for(j=1;j<=term_years;j++)
		{
			printf("\n-------------------------------------------------------------------------------\n");
			printf("\nYear   Month   Interest   Principal   Balance |    INTEREST   PRINCIPAL   EXTRA\n");
			printf("-------------------------------------------------------------------------------\n");
		
			for(i=1;i<=MONTHS;i++)
			{
				interest = loan_amount*m_rate; //Gets the interest rate montly
				total_interest +=interest; //Cumulative Interest: adds the montly interest to the total_interest
				payment_towards_loan=fixed_montly_payment-interest; //Principal: Gets the payments towards the loan subtracting interest
				total_payment_towards_loan=total_payment_towards_loan + payment_towards_loan + extra_monthy; //Cumulative Principal paid
				loan_amount=loan_amount - (payment_towards_loan+extra_monthy); // Balance: loan total amount subtracting payments towards loan
	
				if(i==1) printf("\n%4d%8d%11.lf%12.lf%10.lf |%12.lf%12.lf%8.lf\n",j, k,interest,payment_towards_loan, loan_amount, total_interest,total_payment_towards_loan,extra_monthy); //If it's the first month, it prints the year like the sample output#2
				else printf("\n%12d%11.lf%12.lf%10.lf |%12.lf%12.lf%8.lf\n",k,interest,payment_towards_loan, loan_amount, total_interest,total_payment_towards_loan,extra_monthy);
				
				if(loan_amount<=0) //When loan is due, it prints how early we paid and the savings
				{

					printf("\nThe payments are finished months %d (%.1lf years) earlier!", months-k, (float)((months-k)/MONTHS)); //casting to float as months is a float
					printf("\nThe interest saving is %.2lf", interest_paid - total_interest); //Total interest that was predicted to be paid - total interest actually paid
					return;
				}
				k++;//sums 1 to months up to date

				
			}
			
		}
	return;
}

void output_extra_yearly(double loan_amount,double interest_rate,double term_years,double extra_yearly) //print amortized schedule with extra montly payments
{
		double fixed_montly_payment, interest_paid;
		fixed_montly_payment = montly_payments(loan_amount, interest_rate, term_years); //Call the function that gets the monthly payments
		interest_paid = total_interest(fixed_montly_payment, loan_amount, term_years, interest_rate); //Call the function that gets the total interest

		int i, j, months, k=1; //counter
		double interest=0.00, payment_towards_loan=0.00, total_interest=0.00, total_payment_towards_loan=0.00;
		double m_rate;
		months = term_years*MONTHS; //Gets the total of months of all terms
		m_rate = interest_rate/(MONTHS*HUNDRED); //montly interest rate

		for(j=1;j<=term_years;j++)
		{
			printf("\n-------------------------------------------------------------------------------\n");
			printf("\nYear   Month   Interest   Principal   Balance |    INTEREST   PRINCIPAL   EXTRA\n");
			printf("-------------------------------------------------------------------------------\n");
		
			for(i=1;i<=MONTHS;i++)
			{
				interest = loan_amount*m_rate; //Gets the interest rate montly
				total_interest +=interest; //Cumulative Interest: adds the montly interest to the total_interest
				payment_towards_loan=fixed_montly_payment-interest; //Principal: Gets the payments towards the loan subtracting interest
				
				if(i==12)
				{
					total_payment_towards_loan=total_payment_towards_loan + payment_towards_loan + extra_yearly; //Cumulative Principal paid
					loan_amount=loan_amount - (payment_towards_loan+extra_yearly); // Balance: loan total amount subtracting payments towards loan
					
				}
				else
				{
					total_payment_towards_loan=total_payment_towards_loan + payment_towards_loan; //Cumulative Principal paid
					loan_amount=loan_amount - (payment_towards_loan); // Balance: loan total amount subtracting payments towards loan
				}
				
				if(i==1) printf("\n%4d%8d%11.lf%12.lf%10.lf |%12.lf%12.lf\n",j, k,interest,payment_towards_loan, loan_amount, total_interest,total_payment_towards_loan); //If it's the first month, it prints the year like the sample output#2
				else if (i==12)	printf("\n%12d%11.lf%12.lf%10.lf |%12.lf%12.lf%8.lf\n",k,interest,payment_towards_loan, loan_amount, total_interest,total_payment_towards_loan,extra_yearly); //If it's december, it prints the extra payment like the sample output#4

				else printf("\n%12d%11.lf%12.lf%10.lf |%12.lf%12.lf\n",k,interest,payment_towards_loan, loan_amount, total_interest,total_payment_towards_loan);
				
				if(loan_amount<=0) //When loan is due, it prints how early we paid and the savings
				{

					printf("\nThe payments are finished %d months (%.1lf years) earlier!", months-k, (float)((months-k)/MONTHS)); //casting to float as months is a float
					printf("\nThe interest saving is %.2lf", interest_paid - total_interest); //Total interest that was predicted to be paid - total interest actually paid
					return;
				}
				k++; //sums 1 to months up to date

				
			}
			
		}
	return;
}

